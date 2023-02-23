#include "iostream"

namespace std {
    std::string to_string(const std::string &s) {
        return s;
    }
}

//template<typename T>
//std::string ToString(const T &t) {
//    if constexpr (std::is_same<T, std::string>::value) {
//        return static_cast<std::string>(t);
//    } else {
//        return std::to_string(t);
//    }
//}

int main() {
    std::to_string("a");
    return 0;
}