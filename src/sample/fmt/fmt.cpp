#include "iostream"
#include "fmt/format.h"
#include "unordered_map"
#include "vector"
#include "spdlog/spdlog.h"

int main() {
    std::string f1 = "hello world";
    f1[5] = '\0';
    std::string result = fmt::format("{}", std::string_view(f1.data(), f1.size()));
    std::string result2 = fmt::format("{}", f1);
    std::cout << f1.size() << " - " << result.size() << " - " << result2.size() << std::endl;
    std::cout << result2 << std::endl;
    std::cout << result2.c_str() << std::endl;

    std::shared_ptr<spdlog::logger> logger = spdlog::rotating_logger_mt<spdlog::async_factory>(#name, "log/"#file
    ".log", (size) * 1024 * 1024, backup); \

    return 0;
    //    std::string f1 = "{{\"status\": {}}}"; // ok
    //    std::string f2 = "{\"status\": {}}";   // not ok
    ////    std::string f3 = "{\"status\": 1}";    // not ok
    //
    //    std::cout << fmt::format(f1, 1) << std::endl;
    ////    std::cout << fmt::format(f2, 2) << std::endl; // error: invalid format string
    ////    std::cout << fmt::format(f3) << std::endl;
    //
    //    std::string f4 = "{{\n\"status\": {}\n}}";
    //    std::cout << "hello" << std::endl;
    //    std::cout << fmt::format("{} {}", "ok", "", "no") << std::endl;
    //    std::unordered_map<int, int> m{};
    //    m.emplace(1, 1);
    //    m.emplace(2, 1);
    //    m.emplace(3, 1);
    //    std::string res;
    //    for (auto &it: m) {
    //        if (res.length() > 0) res.append(",");
    //        res.append(std::to_string(it.first));
    //    }
    //    std::cout << res << std::endl;
    //    std::cout << fmt::format("{a}, {c}", fmt::arg("a", 1), fmt::arg("b", 2), fmt::arg("c", 3)) << std::endl;
    //    return 0;
}