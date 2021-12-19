#include <fmt/core.h>
#include "iostream"

int main(int argc, char **argv) {
    fmt::print("hello, fmt!\n");
    std::cout << fmt::format("hello, {name}!", fmt::arg("name", "john")) << std::endl;
    return 0;
}