#include "iostream"

class A {
public:
    A() {
        std::cout << "construct A" << std::endl;
    }

    ~A() {
        std::cout << "destroy A" << std::endl;
    }
};

A f() {
    A a;
    return a;
}

int main() {
    A a = f();
    std::string s;
    s.append("1").append("2").append("3");
    std::cout << s << std::endl;
    return 0;
}