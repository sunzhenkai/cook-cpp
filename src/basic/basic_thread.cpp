#include "iostream"
#include "thread"

using namespace std::literals;

void payload() {
    while (true) {}
}

/**
 * terminate called without an active exception
 * Process finished with exit code 134 (interrupted by signal 6:SIGABRT)
 */
void run_thread() {
    std::thread th(payload);
}

/**
 * Process finished with exit code 0
 */
void run_thread_detach() {
    std::thread th(payload);
    th.detach();
}

int main() {
    // run_thread();
    run_thread_detach();
    return 0;
}