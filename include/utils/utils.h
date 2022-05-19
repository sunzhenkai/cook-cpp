#ifndef COOK_CPP_UTILS_H
#define COOK_CPP_UTILS_H

#include "chrono"

namespace utils {
    std::chrono::time_point<std::chrono::system_clock> now() {
        return std::chrono::system_clock::now();
    }

    long elapsed(std::chrono::time_point<std::chrono::system_clock> &start) {
        auto e = std::chrono::system_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(e).count();
    }
}

#endif //COOK_CPP_UTILS_H
