#include "iostream"
#include "atomic"
#include "basic/sample_structs.h"
#include "unordered_map"

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
}

int main() {
    atomic_complex();
    return 0;
}