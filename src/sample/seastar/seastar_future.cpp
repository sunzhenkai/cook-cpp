#include <seastar/core/app-template.hh>
#include <seastar/core/reactor.hh>
#include "seastar/net/api.hh"
#include <iostream>

class A {
public:
    A() {
        std::cout << "construct A" << std::endl;
    }

    ~A() {
        std::cout << "destroy A" << std::endl;
    }
};

int main(int argc, char **argv) {
    seastar::app_template app;
    return app.run(argc, argv, []() {
        return seastar::futurize_apply([]() {
            A a;
                        throw std::runtime_error("exception occurred");
//            return seastar::make_ready_future<>();
        }).then([]() {
            std::cout << "then" << std::endl;
            //            return seastar::make_ready_future<>();
        }).handle_exception([](std::exception_ptr ep) {
            std::cout << "error" << std::endl;
            //            return seastar::make_exception_future<>(ep);
//            return seastar::make_ready_future<>();
        }).then([]() {
            std::cout << "done" << std::endl;
            //            return seastar::make_ready_future<>();
        }).then_wrapped([](auto &&f) {
            try {
                f.get();
                std::cout << "future get done" << std::endl;
            } catch (const std::exception &ex) {
                std::cout << "get future result failed" << std::endl;
            }
            return seastar::make_ready_future<>();
        });
    });
    //    std::cout << "all done" << std::endl;
    //    sleep(100);
    //    return 0;
}