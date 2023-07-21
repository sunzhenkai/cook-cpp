#pragma once

#include "list"
#include "memory"

template<typename T>
class ObjectPool {
public:
    ObjectPool() noexcept = default;

    T *Get() {
        if (store.empty()) {
            return new T();
        } else {
            auto t = store.front();
            store.pop_front();
            return std::move(t);
        }
    }

    void Release(T *obj) {
        obj->Reset();
        store.push_back(obj);
    }

    ~ObjectPool() {
        while (!store.empty()) {
            auto t = store.front();
            store.pop_front();
            delete t;
        }
    };

private:
    std::list<T *> store;
};
