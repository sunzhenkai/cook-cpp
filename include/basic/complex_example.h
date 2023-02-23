#pragma once

#include "string"

struct Point {
    int x, y;
};

class ComplexObject {
public:
    template<typename V>
    std::string ToString(const V &v) {
        return std::to_string(v);
    }

    // 泛型方法的重载
    template<typename V>
    std::string ToString(const V *v) {
        return ToString(*v);
    }
};