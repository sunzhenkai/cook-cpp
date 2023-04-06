#pragma once

#include "unordered_map"
#include "atomic"
#include "mutex"

namespace utils {
    template<typename K, typename V>
    class FastReadMap {
    public:
        FastReadMap(int buf_size) {
            this->buffer.resize(buf_size);
            this->index = 0;
            this->buf_size = buf_size;
        }

        const std::unordered_map<K, V> *GetData() {
            return &buffer[index];
        }

        void Put(const K &k, const V &v) {
            std::lock_guard lock(mtx);
            int next = (index + 1) % buf_size;
            buffer[next] = buffer[index];
            buffer[next].emplace(k, v);
            index = next;
        }

    private:
        int buf_size = 2;
        int index;
        std::mutex mtx;
        std::vector<std::unordered_map<K, V>> buffer;
    };

    template<typename K, typename V>
    class FastReadMapV2 {
    public:
        explicit FastReadMapV2(int buf_size) {
            data.reserve(buf_size);
        }

        V &Get(const K &k) {
            while (flag.load()) {}
            auto it = data.find(k);
            return it->second;
        }

        void Put(const K &k, V &&v) {
            while (!flag.compare_exchange_strong(BOOL_FALSE, BOOL_TRUE)) {}
            data.find(k);
            data.emplace(k, std::move(v));
            flag.store(BOOL_FALSE);
        }

        std::unordered_map<K, V> data;
    private:
        std::atomic<bool> flag{false};
        bool BOOL_TRUE{true}, BOOL_FALSE{false};
    };
}