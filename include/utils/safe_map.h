#ifndef COOK_CPP_SAFE_MAP_H
#define COOK_CPP_SAFE_MAP_H

#include <mutex>
#include <shared_mutex>
#include <unordered_map>

#include "functional"

template <typename K, typename V>
class SimpleSafeMap {
 private:
  std::unordered_map<K, V> m;
  std::shared_mutex mtx;

 public:
  void Insert(const K &key, const V &value) {
    std::unique_lock lock(mtx);
    m.insert({key, value});
  }

  typename std::unordered_map<K, V>::iterator Find(const K &key) {
    std::shared_lock lock(mtx);
    return m.find(key);
  }

  typename std::unordered_map<K, V>::iterator End() { return m.end(); }

  void Erase(const K &key) {
    std::unique_lock lock(mtx);
    m.erase(key);
  }

  typename std::unordered_map<K, V>::iterator Begin() { return m.begin(); }

  size_t Size() { return m.size(); }

  void SafetyRun(void (*f)(SimpleSafeMap<K, V> *), bool unique = false) {
    if (unique) {
      std::unique_lock lock(mtx);
      f(this);
    } else {
      std::shared_lock lock(mtx);
      f(this);
    }
  }

  template <typename F>
  void SafetyRunV2(F &&func, bool unique = false) {
    if (unique) {
      std::unique_lock lock(mtx);
      func(this);
    } else {
      std::shared_lock lock(mtx);
      func(this);
    }
  }
};

#endif  // COOK_CPP_SAFE_MAP_H
