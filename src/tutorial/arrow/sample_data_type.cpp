#include <iostream>
#include "unordered_map"
#include "climits"
#include "random"

class RandomGenerator {
    static int RandomInt() {
        static std::uniform_int_distribution<> dist_(0, INT_MAX);
        return dist_(gen_);
    }

protected:
    static std::random_device rd_;
    static std::mt19937 gen_;
};

std::random_device RandomGenerator::rd_{};
std::mt19937 RandomGenerator::gen_{RandomGenerator::rd_()};

class A {
public:
    explicit A(std::unordered_map<std::string, std::string> &&props) {

    }
};

int main() {
    A a(std::unordered_map<std::string, std::string>{{"a", "b"}});

    std::random_device rd_;
    std::mt19937 gen_{rd_()};

    for (int i = 0; i < 1000; ++i) {
        std::uniform_int_distribution<int> dist(0, 999);
        std::cout << dist(gen_) << std::endl;
    }
    return 0;
}