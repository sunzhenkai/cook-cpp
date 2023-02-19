#include "basic/sample_a.h"
#include "iostream"
#include "unordered_map"
#include "memory"
#include "shared_mutex"

#include "utils/utils.h"
#include "basic/fast_read_map.h"
#include "thread"

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
    std::shared_mutex read_mtx;
    for (int i = 0; i < total; ++i) {
//            std::shared_lock lock(read_mtx);
        data.find(12);
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
    data.reserve(total);
    auto f = [&]() {
        for (int i = 0; i < total; ++i) {
            data.emplace(i, std::make_shared<int64_t>(i));
        }
    };
    std::thread td1(f);
    std::thread td2(f);
    std::thread td3(f);
    std::thread td4(f);
    auto el = utils::elapsed(start);
    std::cout << el << std::endl;

    start = utils::now();
    std::shared_mutex read_mtx;
    for (int i = 0; i < total; ++i) {
//        try {
//            std::shared_lock lock(read_mtx);
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
}

int main() {
    f4();
    return 0;
}