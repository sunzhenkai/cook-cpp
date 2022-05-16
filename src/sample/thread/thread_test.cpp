#include "thread"
#include "mutex"
#include "iostream"
#include "chrono"
#include <iomanip>
#include "sstream"
#include <sys/time.h>
#include "shared_mutex"
#include "signal.h"

std::mutex mtx;
std::shared_mutex s_mtx;


// time
long current_milliseconds() {
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
}

long current_milliseconds_v2() {
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
}

long current_milliseconds_v3() {
    struct timeval now{};
    gettimeofday(&now, nullptr);
    return now.tv_sec * 1000 + now.tv_usec / 1000;
}

long current_seconds() {
    time_t t;
    time(&t);
    return (long) t;
}

long duration(std::chrono::time_point<std::chrono::system_clock,
        std::chrono::milliseconds> start) {
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
}

std::string now_format(const std::string &f = "%F %T") {
    auto now = std::chrono::system_clock::now();
    auto now_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_t), f.c_str());
    return ss.str();
}

std::string now_format_v2(const std::string &f = "%F %T") {
    time_t now;
    time(&now);
    char s[30];
    struct tm *time_info = localtime(&now);
    strftime(s, 30, f.c_str(), time_info);
    return {s};
}

std::string now_format_v3(const std::string &f = "%F %T") {
    std::time_t t = std::time(nullptr);
    char buf[100];
    std::strftime(buf, sizeof(buf), "%F %T", std::localtime(&t));
    return {buf};
}

std::string now_format_v4(const std::string &f = "%F %T") {
    std::time_t t = std::time(nullptr);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), f.c_str());
    return ss.str();
}

void test_mutex() {
    std::cout << "A " << now_format() << std::endl << std::flush;
    mtx.lock();
    std::cout << "B " << now_format() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    mtx.unlock();
    std::cout << "C " << now_format() << std::endl;
}

void workload() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "workload" << std::endl;
}

int main() {
    {
        std::thread tt(workload);
        pthread_kill(tt.native_handle(), SIGQUIT);
//        tt.detach();
    }
    std::cout << "hello" << std::endl;
    std::unique_lock lock(s_mtx);
    std::thread t(test_mutex);
    {
        mtx.lock();
        std::cout << "D " << now_format() << std::endl << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        mtx.unlock();
    }
    {
        std::lock_guard g(mtx);
        std::cout << "E " << now_format() << std::endl << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    t.join();

    std::cout << current_milliseconds() << std::endl;
    std::cout << current_milliseconds_v2() << std::endl;
    std::cout << current_milliseconds_v3() << std::endl;
    std::cout << current_seconds() << std::endl;

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < 10000 * 10000; ++i) {
        current_milliseconds();
    }
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count()
              << std::endl; // 4s

    start = std::chrono::steady_clock::now();
    for (int i = 0; i < 10000 * 10000; ++i) {
        current_milliseconds_v2();
    }
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count()
              << std::endl; // 5s

    start = std::chrono::steady_clock::now();
    for (int i = 0; i < 10000 * 10000; ++i) {
        current_milliseconds_v3();
    }
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count()
              << std::endl; // 3s

    start = std::chrono::steady_clock::now();
    for (int i = 0; i < 10000 * 10000; ++i) {
        current_seconds();
    }
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count()
              << std::endl; // 3s

    std::cout << now_format_v2() << std::endl;
    std::cout << now_format_v3() << std::endl;
    std::cout << now_format_v4() << std::endl;
    return 0;
}