//#include <seastar/core/app-template.hh>
//#include <seastar/core/reactor.hh>
#include <iostream>
#include "fmt/format.h"

int main(int argc, char** argv) {
    std::cout << fmt::format("{}", "yes") << std::endl;
//    seastar::app_template app;
//    app.run(argc, argv, [] {
//        std::cout << "Hello world\n";
//        return seastar::make_ready_future<>();
//    });
}