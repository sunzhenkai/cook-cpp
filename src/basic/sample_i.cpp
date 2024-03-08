#include "iostream"
#include "unordered_map"
#include "basic/sample_structs.h"
#include "utils/utils.h"

void ta() {
    std::unordered_map<std::string, Animal> am;
    am.emplace("dog", Animal());
    std::cout << "---" << std::endl;
    for (auto &[k, v]: am) { // no construction
        std::cout << k << std::endl;
    }
}

void tb() {
    std::exception_ptr ex = std::make_exception_ptr(std::out_of_range("empty result"));
    try {
        std::rethrow_exception(ex);
    } catch (const std::out_of_range &e) {
        std::cout << "out_of_range: " << e.what() << std::endl;
    } catch (...) {
        std::cout << utils::WhatError(ex) << std::endl;
    }
}

void tc() {
    Animal a, b;
    std::cout << "---" << std::endl;
    std::cout << (true ? a : b).value << std::endl;
    std::cout << "---" << std::endl;
}

int main() {
    tc();
    return 0;
}