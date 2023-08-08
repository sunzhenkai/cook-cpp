#include "iostream"
#include "gtest/gtest.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Hello, World) {
    std::cout << "hello" << std::endl;
}