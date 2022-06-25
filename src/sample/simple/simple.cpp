#include <cstdlib>
#include <iostream>
#include <ctime>
#include "memory"
#include "map"
#include "vector"

class A {
public:
    int vi;
    A(int v = 0) : vi(v) {
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
    std::cout << std::to_string(true) << std::endl;
    //    A a;
    //    {
    //        std::map<int, A> ma;
    //        ma[0] = std::move(a);
    //    }

//    {
//        std::vector<A> va;
//        va.reserve(10);
//        va.emplace_back(1);
//        va.emplace_back(2);
//        va.emplace_back(3);
//        std::cout << "before re" << std::endl;
//        va.reserve(2);
//
//        for (auto& v : va) {
//            std::cout << "> " << v.vi << std::endl;
//        }
//    }

    std::cout << "done" << std::endl;
    //    A a = f();
    //    std::string s;
    //    s.append("1").append("2").append("3");
    //    std::cout << s << std::endl;
    //    {
    //        std::shared_ptr<A> l = std::shared_ptr<A>(new A());
    //    }
    //    std::cout << "done" << std::endl;
    //    std::srand(std::time(nullptr));
    //
    //    for (int i = 0; i < 100; ++i) {
    //        std::cout << std::rand() << std::endl;
    //    }
    return 0;
}