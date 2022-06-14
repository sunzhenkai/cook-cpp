#include "iostream"
#include "memory"

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
    //    A a = f();
    //    std::string s;
    //    s.append("1").append("2").append("3");
    //    std::cout << s << std::endl;
    {
        std::shared_ptr<A> l = std::shared_ptr<A>(new A());
    }
    std::cout << "done" << std::endl;
    return 0;
}