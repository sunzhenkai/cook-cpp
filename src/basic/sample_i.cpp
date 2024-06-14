#include "iostream"
#include "unordered_map"
#include "basic/sample_structs.h"
#include "utils/utils.h"
#include "memory"

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

void tg() {
    auto r = "6601160d8e989550754ceaax";
    auto s = utils::GetTimestampFromRequestId(r);
    std::cout << s << std::endl;
}

void th() {
    std::shared_ptr<int> i;
    if (i == nullptr) {
        std::cout << "YES" << std::endl;
    }
}

int main() {
    th();
    return 0;
}