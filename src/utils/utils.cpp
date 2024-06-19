#include "utils/utils.h"

namespace utils {
    std::chrono::time_point<std::chrono::system_clock> now() {
        return std::chrono::system_clock::now();
    }

    long elapsed(std::chrono::time_point<std::chrono::system_clock> &start) {
        auto e = std::chrono::system_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(e).count();
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

    int64_t GetTimestampFromRequestId(const std::string &rid) {
        return std::stol(rid.substr(0, 8), nullptr, 16);
    }
}
