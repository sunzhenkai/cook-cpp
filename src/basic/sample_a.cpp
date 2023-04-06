#include "basic/sample_a.h"
#include "iostream"
#include "unordered_map"
#include "memory"
#include "shared_mutex"

#include "utils/utils.h"
#include "basic/fast_read_map.h"
#include "thread"
#include "atomic"

void f1() {
    int total = 500 * 10000;
    auto start = utils::now();
    std::unordered_map<int64_t, std::shared_ptr<int64_t>> data;
    data.reserve(total);
    for (int i = 0; i < total; ++i) {
        data.emplace(i, std::make_shared<int64_t>(i));
    }
    auto el = utils::elapsed(start);
    std::cout << el << std::endl;
}

void f2() {
    int total = 500 * 10000;
    auto start = utils::now();
    std::unordered_map<int64_t, std::shared_ptr<int64_t>> data;
    data.reserve(total);
    for (int i = 0; i < total; ++i) {
        data.emplace(i, std::make_shared<int64_t>(i));
    }
    auto el = utils::elapsed(start);
    std::cout << el << std::endl;

    start = utils::now();
    for (int i = 0; i < total; ++i) {
        auto &v = data.find(12)->second;
    }
    el = utils::elapsed(start);
    std::cout << el << std::endl;
}

void f3() {
    int total = 10000;
    auto start = utils::now();
    utils::FastReadMap<int64_t, int64_t> data(10);
    for (int i = 0; i < total; ++i) {
        data.Put(i, i);
    }
    auto el = utils::elapsed(start);
    std::cout << el << std::endl;

    int f;
    start = utils::now();
    std::shared_mutex read_mtx;
    for (int i = 0; i < 500 * 10000; ++i) {
        //        std::shared_lock lock(read_mtx);
        auto d = data.GetData();
        d->find(12);
        ++f;
    }
    el = utils::elapsed(start);
    std::cout << el << std::endl;
}

void f4() {
    int total = 500 * 10000;
    auto start = utils::now();
    std::unordered_map<int64_t, std::shared_ptr<int64_t>> data;
    data.reserve(5000000);
    auto f = [&](int cycle) {
        for (int i = 0; i < total; ++i) {
            data.emplace(i + cycle, std::make_shared<int64_t>(i));
        }
    };
    std::thread td1(f, 0);
    std::thread td2(f, 1);
    std::thread td3(f, 2);
    std::thread td4(f, 3);
    std::thread td5(f, 4);
    std::thread td6(f, 5);
    std::thread td7(f, 6);
    std::thread td8(f, 7);
    auto el = utils::elapsed(start);
    std::cout << el << std::endl;

    start = utils::now();
    std::shared_mutex read_mtx;
    for (int i = 0; i < total * 4; ++i) {
        //        try {
        //        std::shared_lock lock(read_mtx);
        data.find(12);
        //        } catch (std::exception p) {
        //
        //        }
    }
    el = utils::elapsed(start);
    std::cout << el << std::endl;
    td1.join();
    td2.join();
    td3.join();
    td4.join();
    td5.join();
    td6.join();
    td7.join();
    td8.join();
}

void f5() {
    std::atomic<bool> flag(false);
    int total = 500 * 10000;
    auto start = utils::now();

    std::unordered_map<int64_t, std::shared_ptr<int64_t>> data;
    data.reserve(total);
    for (int i = 0; i < total; ++i) {
        data.emplace(i, std::make_shared<int64_t>(i));
    }
    auto el = utils::elapsed(start);
    std::cout << el << std::endl;

    start = utils::now();
    std::shared_mutex read_mtx;
    for (int i = 0; i < total; ++i) {
        while (flag) {}
        //        std::shared_lock lock(read_mtx);
        data.find(12);
    }
    el = utils::elapsed(start);
    std::cout << el << std::endl;
}

void f6() {
    int total = 500 * 10000;
    auto start = utils::now();
    std::vector<std::unordered_map<int64_t, std::shared_ptr<int64_t>>> data;
    data.resize(10);
    //    data.reserve(total);
    for (int i = 0; i < total; ++i) {
        data[i % 10].emplace(i, std::make_shared<int64_t>(i));
    }
    auto el = utils::elapsed(start);
    std::cout << el << std::endl;

    start = utils::now();
    std::shared_mutex read_mtx;
    for (int i = 0; i < total; ++i) {
        //        std::shared_lock lock(read_mtx);
        data[i % 10].find(12);
    }
    el = utils::elapsed(start);
    std::cout << el << std::endl;
}

void f7() {
    int total = 500 * 10000;
    auto start = utils::now();
    utils::FastReadMapV2<int64_t, std::shared_ptr<int64_t>> data(0);
    for (int i = 0; i < total; ++i) {
        data.Put(i, std::move(std::make_shared<int64_t>(i)));
    }
    auto el = utils::elapsed(start);
    std::cout << el << std::endl;

    start = utils::now();
    for (int i = 0; i < total; ++i) {
        //        data.data.find(12);
        auto &t = data.Get(12);
    }
    el = utils::elapsed(start);
    std::cout << el << std::endl;
}

void f8() {
    std::atomic<bool> flag(false);
    bool v = false, t = true;
    std::cout << flag.load() << " - " << flag.compare_exchange_strong(v, true) << " - " << flag.load() << std::endl;
    std::cout << flag.load() << " - " << flag.compare_exchange_strong(v, false) << " - " << flag.load() << std::endl;
    std::cout << flag.load() << " - " << flag.compare_exchange_strong(t, false) << " - " << flag.load() << std::endl;

}

void f9() {
    int total = 500 * 10000;
    auto start = utils::now();
    std::unordered_map<int64_t, std::shared_ptr<int64_t>> data;
    data.reserve(total);
    for (int i = 0; i < total; ++i) {
        data.emplace(i, std::make_shared<int64_t>(i));
    }
    auto el = utils::elapsed(start);
    std::cout << el << std::endl;

    start = utils::now();
    std::shared_mutex read_mtx;
    for (int i = 0; i < total; ++i) {
        std::shared_lock lock(read_mtx);
        auto &v = data.find(12)->second;
    }
    el = utils::elapsed(start);
    std::cout << el << std::endl;
}

int main() {
    f2();
    f2();
    f7();
    f9();
    //    f4();
    return 0;
}