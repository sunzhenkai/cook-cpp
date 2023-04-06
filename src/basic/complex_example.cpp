#include "iostream"
#include "basic/complex_example.h"

// 泛型方法的特例化实现
// 以 template<> 开始泛型方法的特例化实现
// 类函数的特例化实现要在源文件中实现
template<>
std::string ComplexObject::ToString<Point>(const Point &v) {
    return ToString(v.x) + ", " + ToString(v.y);
}

int main() {
    ComplexObject co;
    Point pt{1, 2};
    std::cout << co.ToString(pt) << std::endl;
    std::cout << co.ToString<Point>([]() { return Point{2, 3}; }) << std::endl;
    return 0;
}