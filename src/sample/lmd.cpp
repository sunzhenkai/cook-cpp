#include "iostream"
#include "thread"
#include <csignal>

typedef void (*F1)();
typedef std::function<void()> F2;

void f1(F1 &&f) {
    f();
}

void f2(F2 &&f) {
    f();
}

class TF {
public:
    std::thread t;
    pthread_t nh;
public:
    explicit TF(F2 f) : t(f) {
        nh = t.native_handle();
    }
    void join() {
        t.join();
    }
    void close() const {
        pthread_kill(nh, SIGUSR1);
    }
};

int main() {
    f1([]() {
        std::cout << "run f1" << std::endl;
    });
    f2([]() {
        std::cout << "run f2" << std::endl;
    });
    auto f3 = []() {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "run f3" << std::endl;
    };
    TF tf(f3);
    tf.close();
//    tf.join();
    std::cout << "done" << std::endl;
    return 0;
}