#include "thread"
#include "iostream"

struct Arg {
    int value;
};

void payload(Arg &v) {
    std::cout << v.value << std::endl;
}

void cpp_thread() {
    // 1. init variables
    Arg arg{2};

    // 2. create thread & run
    std::thread td; // Creates a new std::thread object which does not represent a thread.
    td = std::thread(payload, std::ref(arg));
    td.join();
}

int main() {
    cpp_thread();
    return 0;
}