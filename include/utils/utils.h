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

    const char *What(std::exception_ptr ep) {
        try {
            if (ep) std::rethrow_exception(ep);
        } catch (const std::exception &e) {
            return e.what();
        }
    }

    std::vector<std::string> ReadLines(char *fn) {
        std::vector<std::string> result;
        std::ifstream file(fn);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                result.emplace_back(line);
            }
            file.close();
        } else {
            std::cerr << "open file failed. file=" << fn << std::endl;
        }
        return result;
    }

    std::string ReadFile(char *fn) {
        std::string result;
        std::ifstream infile(fn);
        infile.seekg(0, std::ios::end);
        size_t length = infile.tellg();
        infile.seekg(0, std::ios::beg);
        result.resize(length);
        infile.read(result.data(), length + 1);
        return result;
    }

    std::string WhatError(std::exception_ptr ep) {
        try {
            std::rethrow_exception(ep);
        }
        catch (const std::exception &e) {
            return {e.what()};
        }
    }

    template<typename S>
    int64_t HexToInt64(const S &s) {
        int64_t result{0};
        for (size_t i = 0ul; i < s.size(); ++i) {
            result = result << 4;
            if ('0' <= s[i] && s[i] <= '9') result += s[i] - '0';
            else if ('a' <= s[i] && s[i] <= 'f') result += s[i] - 'a' + 10;
            else if ('A' <= s[i] && s[i] <= 'F') result += s[i] - 'A' + 10;
            else break;
        }
        return result;
    }
}

#endif //COOK_CPP_UTILS_H
