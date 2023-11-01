#include "iostream"
#include <fstream>
#include "thread"
#include "chrono"
#include "thread"
#include "chrono"
#include "unordered_set"
#include "unordered_map"
#include "vector"
#include "utils/utils.h"

template<typename T>
void Unique(std::vector<T> &data) {
    std::unordered_set<T> store;
    for (auto &item: data) {
        store.emplace(std::forward<T>(item));
    }

    size_t idx = 0ul;
    for (auto it = store.begin(); it != store.end(); ++it) {
        data[idx++] = std::forward<T>(std::remove_const_t<T>(*it));
    }
    data.resize(idx);
}

template<typename T, typename V>
void ZipUnique(std::vector<T> &data, std::vector<V> &value) {
    if (data.size() <= 1) return;
    std::unordered_map<T, V> store;
    for (size_t i = 0ul; i < data.size(); ++i) {
        store[data[i]] = std::forward<V>(value[i]);
    }

    size_t idx = 0ul;
    for (auto it = store.begin(); it != store.end(); ++it, ++idx) {
        data[idx] = it->first;
        value[idx] = std::forward<V>(it->second);
    }
    data.resize(idx);
    value.resize(idx);
}

int main() {
    //    std::ofstream f;
    //    f.open("test.log");
    //    for (int i = 0; true; ++i) {
    //        f << i << "\u0004\u0004\u0004\u0005\u0005\u0005\n";
    //        std::this_thread::sleep_for(std::chrono::microseconds(100));
    //    }
    //    while (true) {
    //        auto result = std::getenv("NPS_BATCH_SIZE");
    //        std::cout << result << std::endl;
    //        std::cout << (result ? "yes" : "no") << std::endl;
    //        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //    }

    std::vector<uint64_t> ids{1, 3, 1, 2, 2, 3, 4, 2, 5};
    std::vector<float> values{1.1, 3.3, 1.1, 2.2, 2.2, 3.3, 4.4, 2.2, 5.5};
    ZipUnique(ids, values);
    utils::display(ids);
    utils::display(values);
    return 0;
}