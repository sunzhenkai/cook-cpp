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

class ServerConnection {
public:
    seastar::connected_socket socket_;
    seastar::socket_address addr_;
    seastar::input_stream<char> in_;
    seastar::output_stream<char> out_;
    uint64_t id_;
    seastar::semaphore _write_sem{1};
    bool valid_{true};

    ServerConnection(seastar::connected_socket &&socket,
                     seastar::socket_address addr,
                     uint64_t connection_id) : socket_(std::move(socket)), addr_(addr), in_(socket_.input()),
                                               out_(socket_.output()), id_(connection_id) {}

    bool IsValid() const {
        return valid_;
    }
};

class Server {
    std::atomic<uint64_t> connection_id_;
    seastar::lw_shared_ptr<seastar::http_server> http_server_ = nullptr;
public:
    void Start(uint32_t port, uint32_t http_port) {
        std::cout << "start" << std::endl << std::flush;
        spdlog::info("[Server::Start] start server. [socket_port={}, http_port={}]", port, http_port);

        // http server
        http_server_ = seastar::make_lw_shared<seastar::http_server>("http server");
        seastar::prometheus::config cfg;
        cfg.metric_help = "sample server";
        (void) seastar::prometheus::add_prometheus_routes(*http_server_, cfg)
                .then([http_server_ = http_server_, http_port = http_port]() {
                    auto address = seastar::make_ipv4_address({(uint16_t) http_port});
                    return http_server_->listen(address);
                });

        // socket server
        seastar::listen_options lo;
        lo.reuse_address = true;
        auto address = seastar::make_ipv4_address({(uint16_t) port});
        (void) seastar::do_with(seastar::listen(address, lo), [this](auto &listener) {
            return seastar::keep_doing([this, &listener] {
                return listener.accept().then([this](seastar::accept_result &&ar) mutable {
                    auto &[fd, addr] = ar;
                    auto conn = seastar::make_lw_shared<ServerConnection>(std::move(fd), addr, connection_id_++);
                    return HandleConnection(conn);
                });
            });
        });
    }

    seastar::future<> HandleConnection(seastar::lw_shared_ptr<ServerConnection> conn) {
        return seastar::do_until([conn] { return !conn->IsValid(); }, [this, conn]() mutable {
            return HandleSession(conn);
        }).handle_exception([](std::exception_ptr ep) {
            spdlog::info("handle connection failed. [error={}]", utils::What(ep));
        });
    }

    seastar::future<> HandleSession(seastar::lw_shared_ptr<ServerConnection> conn) {
        return conn->in_.read().then([this, conn](seastar::temporary_buffer<char> &&data) mutable {
            spdlog::info("received data. [size={}]", data.size());
            return seastar::make_ready_future<>();
        });
    }
};

int main(int argc, char **argv) {
    seastar::app_template app;
    seastar::distributed<Server> server;
    char *av[5] = {"--overprovisioned", "-c", "4", "--blocked-reactor-notify-ms", "10"};
    return app.run_deprecated(sizeof av / sizeof *av, av, [&]() {
        spdlog::info("run server");
        return server.invoke_on_all(&Server::Start, 8090u, 8091u);
    });
}