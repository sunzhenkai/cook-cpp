#include "iostream"
#include "unordered_map"
#include "basic/sample_structs.h"
#include "utils/utils.h"
#include "memory"
#include "cmath"
#include "algorithm"

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

void td() {
    std::shared_ptr<int> si = std::make_shared<int>();
    auto si2 = si;
    std::cout << si2.use_count() << std::endl;
    std::weak_ptr<int> si3 = si;
    std::cout << si2.use_count() << " - " << si3.use_count() << std::endl;
}

void te() {
    std::shared_ptr<int> pa = std::make_shared<int>(1);
    std::cout << pa.get() << std::endl;
    std::shared_ptr<int> pb = pa;
    pa = nullptr;
    std::cout << pb.get() << std::endl;
    std::cout << pa.get() << std::endl;
}

void tf() {
    int a[9];
    auto j = a; // 此时j 为指针为 int* 类型，而不是 int(*)[9] 类型
    std::cout << typeid(j).name() << " " << sizeof(j) << " " << sizeof(a) << std::endl;
}

int solve(const std::string &s) {
    if (s.size() <= 1) return s.size();
    std::vector<int> flag(26, -1);
    int result = 0;
    for (int i = 0, j = 0; i < s.size(); ++j) {
        int pre = flag[s[j] - 'a'];
        if (pre > i) {
            result = std::max(result, j - i);
            i = pre + 1;
        }
        flag[s[j] - 'a'] = j;
    }
    return result;
}

struct AnimalB {
    int value = 0;

    // 默认构造函数
    AnimalB(int value) : value(value) {
        std::cout << "[Animal] " << this << " default constructor" << std::endl;
    };
};

void fg() {
    static AnimalB animal(2);
    std::cout << animal.value << std::endl;
    animal.value = 3;
}

int main() {
    fg();
    fg();
    return 0;
}