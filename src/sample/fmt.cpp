#include <fmt/core.h>
#include "iostream"
#include "utils/utils.h"

int main(int argc, char **argv) {
    fmt::print("hello, fmt!\n");
    std::cout << fmt::format("hello, {name}!", fmt::arg("name", "john")) << std::endl;
    std::cout << fmt::format("bool is {}", true) << std::endl;

    // concat benchmark
    int loop = 1000 * 10000;
    std::string foo = "1080", bar = "1080";
    auto start = utils::now();
    for (int i = 0; i < loop; ++i) {
        std::string r;
        r.append(foo).append("x").append(bar);
    }
    std::cout << "elapsed: " << utils::elapsed(start) << std::endl;

    start = utils::now();
    for (int i = 0; i < loop; ++i) {
        fmt::format("{}x{}", foo, bar);
    }
    std::cout << "elapsed: " << utils::elapsed(start) << std::endl;
    return 0;
}