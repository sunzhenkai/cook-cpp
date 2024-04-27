#include "iostream"
#include "atomic"
#include "basic/sample_structs.h"
#include "unordered_map"
#include "assert.h"

void atomic_int() {
    std::atomic<int> ai;
    std::atomic<int> aj(1);

    ai = 10;
}

struct B {
    int i1;
    int i2;
};

struct A {
    int value;
    B b;
};

void atomic_complex() {
    //    std::cout << std::is_trivially_copyable<Animal>::value << std::endl;
    //    std::cout << std::is_trivially_copy_assignable<Animal>::value << std::endl;
    std::atomic<A> aa;
    std::cout << aa.is_lock_free() << std::endl;
    std::atomic<B> ab;
    std::cout << ab.is_lock_free() << std::endl;
    ab.store({2});
    B b = ab.load();
}

struct AA {
    int v;
};

void t_a(int k) {
    std::cout << k << std::endl;
    std::unordered_map<std::string, int> si;
    std::cout << si["a"] << std::endl;
    {
        int i, j{};
        std::cout << i << std::endl;
        std::cout << j << std::endl;
    }

    for (int i = 0; i < 1000000; ++i) {
        int m;
        assert(m == 0);

        AA aa;
        assert(aa.v == 0);
    }
}

int main() {
    int k;
    //    atomic_complex();
    t_a(k);
    return 0;
}