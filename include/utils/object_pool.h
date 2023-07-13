#pragma once

#include "functional"

template<typename T>
class ObjectPool {
    typedef ::std::function<T *()> CreateFunction;

private:
    struct Node {
        T *object{nullptr};
        Node *next{nullptr};
    };

    struct NodeChain {
        inline NodeChain() noexcept = default;
        inline explicit NodeChain(Node *node) noexcept: head(node), tail(node) {}
        inline void Add(Node *node) noexcept {
            if (head == nullptr) {
                head = tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }

        Node *head{nullptr}, *tail{nullptr};
    };

public:
    class PooledObject {
        // functions
    public:
        inline PooledObject() noexcept = default;
        inline ~PooledObject();
    private:
        inline PooledObject(ObjectPool *pool, Node *node) noexcept;

        // fields
    private:
        T *_object{nullptr};
        ObjectPool _pool{nullptr};
        Node *_node{nullptr};
    };
};