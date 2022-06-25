#include <iostream>

template<unsigned N>
void f() {
    std::cout << N << std::endl;
}

int main() {
    f<10>();
    return 0;
}