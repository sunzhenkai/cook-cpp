#include "iostream"
#include "atomic"
#include "algorithm"

struct A {
    int x, y;
};

int main() {
    std::string str = "AbCd";
    std::transform(str.begin(), str.end(), str.begin(), (int(*)(int)) std::tolower);
    std::cout << str << std::endl;
    std::atomic<A> aa;
    std::cout << aa.is_lock_free() << std::endl;
    return 0;
}