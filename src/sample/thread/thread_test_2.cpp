#include "iostream"
#include "thread"

int main() {
    auto f = [] {

    };
    std::thread t(f);
    std::terminate(t);
    return 0;
}