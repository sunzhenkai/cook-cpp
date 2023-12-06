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
#include "memory"
#include "shared_mutex"
#include "mutex"
#include "functional"
#include "unordered_set"

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

template<typename K, typename V>
class SimpleSafeMap {
private:
    std::unordered_map<K, V> m;
    std::shared_mutex mtx;

public:
    void Insert(const K &key, const V &value) {
        std::unique_lock lock(mtx);
//        m[key] = value;
                    m.insert({key, value});
    }

    void Insert(const K &key, const std::function<V(const K &key)> &generator) {
        std::unique_lock lock(mtx);
        m[key] = generator(key);
        //            m.insert({key, generator(key)});
    }

    typename std::unordered_map<K, V>::iterator Find(const K &key) {
        std::shared_lock lock(mtx);
        return m.find(key);
    }

    void Erase(const K &key) {
        std::unique_lock lock(mtx);
        m.erase(key);
    }

    typename std::unordered_map<K, V>::iterator End() {
        return m.end();
    }

    typename std::unordered_map<K, V>::iterator Begin() {
        return m.begin();
    }

    typename std::unordered_map<K, V>::const_iterator CEnd() const {
        return m.end();
    }

    typename std::unordered_map<K, V>::const_iterator CBegin() const {
        return m.begin();
    }

    size_t Size() const {
        return m.size();
    }

    template<typename F>
    void SafetyRun(F &func, bool unique = false) {
        if (unique) {
            std::unique_lock lock(mtx);
            func(this);
        } else {
            std::shared_lock lock(mtx);
            func(this);
        }
    }
};

struct TestA {
    int i = 0;
};


int main() {
    std::unordered_set<std::string_view> ss;
    std::vector<std::string> s = {"a", "b", "a", "c", "d", "v", "b", "c"};
    for (auto &i: s) {
        std::cout << "- " << (ss.find(i) == ss.end()) << std::endl;
        ss.insert(i);
    }

    SimpleSafeMap<std::string, std::shared_ptr<TestA>> m;
    m.Insert("a", std::make_shared<TestA>(1));
    m.Insert("a", std::make_shared<TestA>(2));
    std::cout << m.Find("a")->second->i << std::endl;
    std::cout << (m.Find("a") == m.End()) << std::endl;

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

//    std::vector<uint64_t> ids{1, 3, 1, 2, 2, 3, 4, 2, 5};
//    std::vector<float> values{1.1, 3.3, 1.1, 2.2, 2.2, 3.3, 4.4, 2.2, 5.5};
//    ZipUnique(ids, values);
//    utils::display(ids);
//    utils::display(values);
    return 0;
}