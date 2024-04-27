#pragma once

#include "iostream"

struct Animal {
    int value = 0;
    std::string name;

    // 默认构造函数
    Animal() {
        std::cout << "[Animal] " << this << " default constructor" << std::endl;
    };
    // 拷贝构造函数
    Animal(const Animal &other) {
        value = other.value;
        name = other.name;
        std::cout << "[Animal] " << this << " copy constructor" << std::endl;
    }
    // 赋值构造
    Animal &operator=(const Animal &other) {
        value = other.value;
        name = other.name;
        std::cout << "[Animal] " << this << " copy assignment constructor" << std::endl;
        return *this;
    }
    // move 构造
    Animal(Animal &&other) noexcept {
        value = other.value;
        name = std::move(other.name);
        std::cout << "[Animal] " << this << " move constructor" << std::endl;
    }
    // 赋值 move 构造
    Animal &operator=(Animal &&other) noexcept {
        value = other.value;
        name = std::move(other.name);
        std::cout << "[Animal] " << this << " move assignment constructor" << std::endl;
        return *this;
    }

    // 析构函数
    ~Animal() {
        std::cout << "[Animal] " << this << " destructor" << std::endl;
    }
};