#include "iostream"
#include "atomic"
#include "basic/complex_example.h"

void atomic_int() {
    std::atomic<int> ai;
    std::atomic<int> aj(1);

    ai = 10;
}

void atomic_complex() {
    std::atomic<>
}

int main() {
    atomic_int();
    return 0;
}