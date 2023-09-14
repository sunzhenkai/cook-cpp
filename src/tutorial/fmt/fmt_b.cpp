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

int main() {
    std::vector<float> data = {0.1, 0.2, 0.3};
    std::cout << ToString(data) << std::endl;

    std::vector<std::vector<float>> data2(1, data);
    std::cout << ToString(data2) << std::endl;
    return 0;
}
