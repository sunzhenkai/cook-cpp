#include "iostream"
#include "seastar/core/app-template.hh"
#include "seastar/core/reactor.hh"
#include "seastar/core/seastar.hh"
#include "seastar/net/api.hh"

using namespace seastar;

future<> handle_connection(connected_socket s) {
    auto in = s.input();
    auto out = s.output();
    s.shutdown_output();
    return do_with(std::move(in), std::move(out), [](auto &in, auto &out) {
        return do_until([&in]() { return in.eof(); },
                        [&in, &out] {
                            return in.read().then([&out](auto buf) {
                                return out.write(std::move(buf)).then([&out]() { return out.close(); });
                            });
                        });
    });
}

future<> echo_server_loop() {
    return do_with(
            server_socket(listen(make_ipv4_address({1234}), listen_options{.reuse_address = true})),
            [](auto &listener) {
                // Connect asynchronously in background.
                (void) connect(make_ipv4_address({"127.0.0.1", 1234})).then([](connected_socket &&socket) {
                    socket.shutdown_output();
                });
                return listener.accept().then(
                        [](accept_result ar) {
                            connected_socket s = std::move(ar.connection);
                            return handle_connection(std::move(s));
                        }).then([l = std::move(listener)]() mutable { return l.abort_accept(); });
            });
}

int main(int ac, char **av) {
    app_template app{};
    app.run(ac, av, [] {
        engine().exit(0);
        return make_ready_future<int>(0);
    });
    return 0;
//    return app_template().run_deprecated(ac, av, [] {
//        return make_ready_future<int>(0).finally([] {
//            engine().exit(0);
//        });
//        return echo_server_loop()
//                .then([] {
//                    std::cout << "done" << std::endl;
//                    return seastar::make_ready_future<int>(0);
//                })
//                .handle_exception([](const std::exception_ptr &e) {
//                    std::cout << "error: " << e << std::endl;
//                    return seastar::make_ready_future<int>(0);
//                })
//                .finally([]() {
//                    engine().exit(0);
//                });
//    });
}