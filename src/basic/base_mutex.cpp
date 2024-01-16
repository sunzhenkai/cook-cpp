#include "mutex"
#include "shared_mutex"
#include "iostream"

void test_shared_mutex() {
    std::shared_mutex shared_mtx;
    {
        std::shared_lock lock(shared_mtx);
    }
    {
        std::unique_lock lock(shared_mtx);
    }
}

void test_mutex() {
    std::mutex mtx;
    std::lock_guard lock(mtx);
}

int main() {
    return 0;
}