#include "mutex"
#include "shared_mutex"
#include "iostream"
#include "condition_variable"
#include "vector"

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

using namespace std::literals;
std::mutex mtx;
std::condition_variable cv;
void run_wait() {
    std::unique_lock lock(mtx);
    cv.wait(lock);
    std::cout << __FUNCTION__ << " done" << std::endl;
}
void run_wait_predicate() {
    std::unique_lock lock(mtx);
    cv.wait(lock, []() { return false; });
    std::cout << __FUNCTION__ << " done" << std::endl;
}
void run_wait_for() {
    std::unique_lock lock(mtx);
    cv.wait_for(lock, 1s, []() { return false; });
    std::cout << __FUNCTION__ << " done" << std::endl;
}

void test_run() {
    std::vector<std::thread> ths;
    ths.emplace_back(run_wait);
    ths.emplace_back(run_wait_predicate);
    ths.emplace_back(run_wait_for);

    std::this_thread::sleep_for(2s);
    {
        std::lock_guard lock(mtx);
        cv.notify_all();
    }

    for (auto &th: ths) th.join();
}

int main() {
    //    std::thread td(run_wait);
    test_run();
    return 0;
}