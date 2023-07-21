#include "iostream"
#include "utils/simple_object_pool.h"
#include "boost/pool/object_pool.hpp"

class Reusable {
    virtual void Reset() = 0;
};

class A {
public:
    A() {
        std::cout << "Construct A" << std::endl;
    }

    ~A() {
        std::cout << "Deconstruct A" << std::endl;
    }
};

class TO : public Reusable {
public:
    void Reset() override {}

    A a;
};

int main() {
    boost::object_pool<TO> to_pool;
    auto t = to_pool.construct();
    std::cout << "---" << std::endl;
    to_pool.destroy(t);

    std::cout << "***" << std::endl;
    // simple object pool
    ObjectPool<TO> to_pool_simple;
    auto t2 = to_pool_simple.Get();
    std::cout << "---" << std::endl;
    to_pool_simple.Release(t2);
    std::cout << "---" << std::endl;
    return 0;
}