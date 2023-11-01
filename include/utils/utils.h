#ifndef COOK_CPP_UTILS_H
#define COOK_CPP_UTILS_H

#include "vector"
#include "chrono"
#include "iostream"
#include "fstream"
#include "list"
#include "forward_list"

namespace utils {
    std::chrono::time_point<std::chrono::system_clock> now() {
        return std::chrono::system_clock::now();
    }

    long elapsed(std::chrono::time_point<std::chrono::system_clock> &start) {
        auto e = std::chrono::system_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(e).count();
    }

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
}

#endif //COOK_CPP_UTILS_H
