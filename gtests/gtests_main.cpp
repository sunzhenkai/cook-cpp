#include "iostream"
#include "gtest/gtest.h"
#include "cmath"
#include "algorithm"
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Hello, World) {
    std::cout << "hello" << std::endl;

    std::string data = "sport\0030.002";
    auto it = data.find('\003');
    std::cout << std::string(data.c_str(), it)
              << " - "
              << std::stof(data.c_str() + it + 1)
              << std::endl;

    double a = 0.1, b = std::numeric_limits<double>::quiet_NaN();;
    std::cout << (a < b) << std::endl;
    std::cout << (a > b) << std::endl;
    std::cout << (a == b) << std::endl;

    std::vector<double> dv = {0.1, 0.3, std::numeric_limits<double>::quiet_NaN(), 0.2};
    std::sort(dv.begin(), dv.end());
    for (auto v: dv) {
        std::cout << v << ",";
    }
}