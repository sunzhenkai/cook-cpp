#include "iostream"
#include "fmt/format.h"
#include "unordered_map"
#include "vector"

int main() {
    std::cout << "hello" << std::endl;
    std::cout << fmt::format("{} {}", "ok", "", "no") << std::endl;
    std::unordered_map<int, int> m{};
    m.emplace(1, 1);
    m.emplace(2, 1);
    m.emplace(3, 1);
    std::string res;
    for (auto &it: m) {
        if (res.length() > 0) res.append(",");
        res.append(std::to_string(it.first));
    }
    std::cout << res << std::endl;
    std::cout << fmt::format("{a}, {c}", fmt::arg("a", 1), fmt::arg("b", 2), fmt::arg("c", 3)) << std::endl;
    return 0;
}