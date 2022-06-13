#ifndef COOK_CPP_UTILS_H
#define COOK_CPP_UTILS_H

#include "vector"
#include "chrono"
#include "iostream"

namespace utils {
    static std::chrono::time_point<std::chrono::system_clock> now() {
        return std::chrono::system_clock::now();
    }

    static long elapsed(std::chrono::time_point<std::chrono::system_clock> &start) {
        auto e = std::chrono::system_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(e).count();
    }

    template<typename T>
    static void display(const std::vector<T> &v) {
        std::cout << "[";
        for (size_t i = 0; i < v.size(); ++i) {
            if (i != 0) std::cout << ", ";
            std::cout << v[i];
        }
        std::cout << "]" << std::endl;
    }

    static const char *What(std::exception_ptr ep) {
        try {
            if (ep) std::rethrow_exception(ep);
        } catch (const std::exception &e) {
            return e.what();
        }
    }
}

#endif //COOK_CPP_UTILS_H
