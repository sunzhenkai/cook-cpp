#include "iostream"
#include "atomic"

void atomic_int() {
    std::atomic<int> ai;
    std::atomic<int> aj(1);

    ai = 10;
}

int main() {
    atomic_int();
    return 0;
}