#ifndef COOK_CPP_UTILS_H
#define COOK_CPP_UTILS_H

#include "vector"
#include "chrono"
#include "iostream"
#include "fstream"
#include "list"
#include "forward_list"

namespace utils {
    std::chrono::time_point<std::chrono::system_clock> now();
    long elapsed(std::chrono::time_point<std::chrono::system_clock> &start);
    template<typename T>
    void display(const std::vector<T> &v) {
        std::cout << "[";
        for (size_t i = 0; i < v.size(); ++i) {
            if (i != 0) std::cout << ", ";
            std::cout << v[i];
        }
        std::cout << "]" << std::endl;
    }
    template<typename T>
    void display(const std::list<T> &v) {
        std::cout << "[";
        for (auto it = v.begin(); it != v.end(); ++it) {
            if (it != v.begin()) std::cout << ", ";
            std::cout << *it;
        }
        std::cout << "]" << std::endl;
    }
    template<typename T>
    void display(const std::forward_list<T> &v) {
        std::cout << "[";
        for (auto it = v.begin(); it != v.end(); ++it) {
            if (it != v.begin()) std::cout << ", ";
            std::cout << *it;
        }
        std::cout << "]" << std::endl;
    }
    const char *What(std::exception_ptr ep);
    std::vector<std::string> ReadLines(char *fn);
    std::string ReadFile(char *fn);
    std::string WhatError(std::exception_ptr ep);
    int64_t GetTimestampFromRequestId(const std::string &rid);
}

#endif //COOK_CPP_UTILS_H
