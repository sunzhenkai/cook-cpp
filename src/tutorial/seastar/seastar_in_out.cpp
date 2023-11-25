#include <seastar/core/app-template.hh>
#include <seastar/core/reactor.hh>
#include <iostream>
#include "fmt/format.h"
#include "queue"
#include <chrono>

namespace bpo = boost::program_options;

std::queue<int> q;

void Producer() {
    int count = 0;
    while (true) {
        q.push(count++);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void Consumer() {
    while (true) {
        if (!q.empty()) {
            auto v = q.front();
            q.pop();
            std::cout << "consume: " << v << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main(int argc, char **argv) {
    std::cout << fmt::format("{}", "yes") << std::endl;
    seastar::app_template app;

    std::thread td(Producer);

    //--- 添加参数选项, 用于解析命令行参数, 并使用 app.configuration() 获取
    //- add_options: 指定常规的命令行参数选项, 比如 -c -i --smp
    //- add_positional_options: 指定没有 - 和 -- 前缀的参数, 比如 start stop
    //    app.add_options()("name", "service name");
    char *agv[] = {"", "-c", "2"};
    // app.run(argc, argv, [&app] {
    app.run(sizeof(agv) / sizeof(char *), agv, [&app] {
        // auto &cfg = app.configuration();
        std::cout << seastar::smp::count << "\n";
        std::cout << "Hello world\n";
        Consumer();
        return seastar::make_ready_future<>();
    });
}