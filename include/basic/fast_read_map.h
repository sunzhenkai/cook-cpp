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
}