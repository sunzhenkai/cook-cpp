#include "iostream"
#include "gtest/gtest.h"

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
}