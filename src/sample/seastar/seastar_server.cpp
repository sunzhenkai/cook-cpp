#include <seastar/core/app-template.hh>
#include <seastar/core/reactor.hh>
#include "seastar/net/api.hh"
#include <seastar/http/httpd.hh>
#include "seastar/core/distributed.hh"
#include "seastar/core/prometheus.hh"
#include "seastar/core/timer.hh"
#include "utils/utils.h"
#include "spdlog/spdlog.h"
#include <seastar/core/sleep.hh>
#include "seastar/core/alien.hh"
#include <cstdlib>
#include <iostream>
#include <ctime>

#define CPU_ID seastar::engine().cpu_id()
#define READY seastar::make_ready_future<>()
#define FAIL(e) seastar::make_exception_future<>(e)

class A {
public:
    A() {
        std::cout << "construct A" << std::endl;
    }

    ~A() {
        std::cout << "destroy A" << std::endl;
    }
};

class ContextBase {
public:
    virtual void Done(int status) = 0;
};

template<typename T>
class Context : public ContextBase {
public:
    T cb;

    Context(T &&f) : cb(std::move(f)) {}

    void Done(int status) override {
        cb(status);
    }
};

class ServerConnection {
    seastar::connected_socket socket_;
    seastar::socket_address addr_;
    seastar::input_stream<char> in_;
    seastar::output_stream<char> out_;
    uint64_t id_;
    seastar::semaphore _write_sem{1};
    bool valid_{true};
    std::atomic<bool> closed_{false};

public:
    ServerConnection(seastar::connected_socket &&socket,
                     seastar::socket_address addr,
                     uint64_t connection_id) : socket_(std::move(socket)), addr_(addr), in_(socket_.input()),
                                               out_(socket_.output()), id_(connection_id) {}

    bool IsValid() const {
        return valid_;
    }

    bool SetValid(bool v) {
        valid_ = v;
    }

    seastar::future<> Close() {
        if (!closed_.exchange(true)) {
            try {
                socket_.shutdown_input();
                socket_.shutdown_output();
                return seastar::when_all(in_.close(), out_.close()).discard_result();
            } catch (...) {}
        }
        return seastar::make_ready_future<>();
    }

    uint64_t GetId() {
        return id_;
    }

    seastar::input_stream<char> &In() {
        return in_;
    }
};

class Server {
    std::atomic<uint64_t> connection_id_;
    seastar::lw_shared_ptr<seastar::http_server> http_server_ = nullptr;
public:
    seastar::future<> Start(uint32_t port, uint32_t http_port) {
        spdlog::info("[Server::Start] start server. [socket_port={}, http_port={}]", port, http_port);

        // http server
        http_server_ = seastar::make_lw_shared<seastar::http_server>("http server");
        seastar::prometheus::config cfg;
        cfg.metric_help = "sample server";
        seastar::prometheus::add_prometheus_routes(*http_server_, cfg)
                .then([http_server_ = http_server_, http_port = http_port]() {
                    auto address = seastar::make_ipv4_address({(uint16_t) http_port});
                    return http_server_->listen(address);
                });

        // socket server
        seastar::listen_options lo;
        lo.reuse_address = true;
        auto address = seastar::make_ipv4_address({(uint16_t) port});
        return seastar::do_with(seastar::listen(address, lo), [this](auto &listener) {
            return seastar::keep_doing([this, &listener] {
                return listener.accept().then([this](seastar::accept_result &&ar) mutable {
                    auto &[fd, addr] = ar;
                    auto conn = seastar::make_lw_shared<ServerConnection>(std::move(fd), addr, connection_id_++);
                    spdlog::info("[Server::Start] received connection. [cpu={}, port={}, cid={}]",
                                 CPU_ID, addr.port(), conn->GetId());
                    HandleConnection(conn);
                    return READY;
                });
            });
        });
    }

    seastar::future<> HandleConnection(seastar::lw_shared_ptr<ServerConnection> conn) {
        return seastar::do_until([conn] { return !conn->IsValid(); }, [this, conn]() mutable {
            return HandleSession(conn);
        }).handle_exception([conn](std::exception_ptr ep) {
            spdlog::info("handle connection failed. [cpu={}, error={}]", CPU_ID, utils::What(ep));
            conn->SetValid(false);
        }).finally([conn] {
            conn->Close().finally([conn] {});
            spdlog::info("handle connection closed. [cpu={}, id={}]", CPU_ID, conn->GetId());
        });
    }

    seastar::future<> HandleSession(seastar::lw_shared_ptr<ServerConnection> conn) {
        return conn->In().read().then([this, conn](seastar::temporary_buffer<char> &&data) mutable {
            spdlog::info("received data. [cpu={}, size={}]", CPU_ID, data.size());
            auto p = [this, conn] {
                return Payload().then([conn] {
                    spdlog::info("[Server::HandleSession] process done. [cpu={}, cid={}]", CPU_ID, conn->GetId());
                    return READY;
                });
            };
            return data.size() > 0 ? p() : FAIL(std::runtime_error("empty data"));
        });
    }

    void AsyncPayload(std::unique_ptr<ContextBase> context) {
        auto rd = std::rand();
        spdlog::info("[Server::AsyncPayload] do async payload. [rand={}]", rd);
        //        throw std::runtime_error("e");
        if (rd > 0) context->Done(0);
    }

    seastar::future<> Payload() {
        auto pm = std::make_unique<seastar::promise<int>>();
        auto future = pm->get_future();
        auto cb = [pm = std::move(pm), cid = CPU_ID](int s) mutable {
            spdlog::info("[Server::Payload] payload done. [status={}, cid={}]", s, cid);
            seastar::alien::submit_to(cid, [s, pm = std::move(pm)]() mutable {
                pm->set_value(s);
                return seastar::make_ready_future<int>(0);
            });
        };

        std::unique_ptr<ContextBase> context(new Context<std::decay_t<decltype(cb)>>(std::move(cb)));
        std::thread td(&Server::AsyncPayload, this, std::move(context));
        std::shared_ptr<A> ap = std::make_shared<A>();
        return future.then([ap = ap, td = std::move(td)](int status) {
            return seastar::sleep(std::chrono::seconds(3)).then([] {
                return READY;
            });
        });
    }
};

int main(int argc, char **argv) {
    std::srand(std::time(nullptr));
    seastar::app_template app;
    seastar::distributed<Server> server;
    char *av[5] = {"--overprovisioned", "-c", "1", "--blocked-reactor-notify-ms", "25"};
    return app.run(sizeof av / sizeof *av, av, [&]() {
        spdlog::info("run server");
        return server.start().then([&] {
            return server.invoke_on_all(&Server::Start, 8090u, 8091u);
        }).then([&] {
            return server.stop();
        });
    });
}