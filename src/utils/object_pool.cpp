#include "utils/object_pool.h"

template<typename T>
inline ObjectPool<T>::PooledObject::PooledObject(ObjectPool<T> *pool, ObjectPool::Node *node) noexcept :
        _pool(pool), _node(node) {
}

template<typename T>
inline ObjectPool<T>::PooledObject::~PooledObject() {
    
}