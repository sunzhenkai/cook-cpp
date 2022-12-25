#include "basic/sample_a.h"
#include "iostream"
#include "unordered_map"
#include "memory"

#include "utils/utils.h"

class Context {
};

class A {
protected:
    virtual void f() {};
public:
    A(Context ctx) {};
};

class B : public A {
public:
    B(Context ctx) : A(ctx) {}
};

class C : public B {
    void f() override;

public:
    C(Context ctx) : B(ctx) {}
};

void C::f() {}

int main() {
    Context ctx;
    std::shared_ptr<A> pa;
    pa = std::make_shared<B>(ctx);
    pa = std::make_shared<C>(ctx);

    int total = 500 * 10000;
    auto start = utils::now();
    std::unordered_map<int64_t, std::shared_ptr<int64_t>> data;
    data.reserve(total);
    for (int i = 0; i < total; ++i) {
        data.emplace(i, std::make_shared<int64_t>(i));
    }

    auto el = utils::elapsed(start);
    std::cout << el << std::endl; // 2461 ms
    return 0;
}