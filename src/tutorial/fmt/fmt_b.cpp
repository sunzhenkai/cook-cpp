#include "iostream"
#include "vector"
#include "sstream"
#include "fmt/format.h"

template<typename T>
std::string ToString(const T &data) {
    return fmt::format("{}", data);
}

template<typename T>
std::string ToString(const std::vector<T> &data) {
    std::stringstream buf;
    buf << "[";
    for (auto it = data.begin(); it != data.end();) {
        if (std::is_same_v<T, double> || std::is_same_v<T, float>) {
            buf << fmt::format("{:.16f}", *it);
        } else {
            buf << ToString(*it);
        }
        if (++it != data.end()) buf << ",";
    }
    buf << "]";
    return buf.str();
}

void ta() {
    std::vector<float> data = {0.1, 0.2, 0.3};
    std::cout << ToString(data) << std::endl;

    std::vector<std::vector<float>> data2(1, data);
    //    std::cout << ToString(data2) << std::endl;
}

void tb() {
    float f = 1.0;
    std::cout << std::to_string(f) << std::endl;
    std::cout << fmt::format("{}", f) << std::endl;
}

void tc() {
    std::cout << fmt::format("{:.6g}", 3.14) << std::endl;
    std::cout << fmt::format("{:.6g}", 1.0 / 3.0) << std::endl;
    std::cout << fmt::format("{:.6g}", 10.0 / 3.0) << std::endl;
    std::cout << fmt::format("{:.6g}", 100.0 / 3.0) << std::endl;
}

int main() {
    tc();
    return 0;
}
