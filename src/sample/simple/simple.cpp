#include <cstdlib>
#include <iostream>
#include <ctime>
#include "memory"
#include "map"
#include "vector"
#include <string>
#include "thread"
#include "utils/safe_map.h"

class A {
public:
    int vi;

    A(int v = 0) : vi(v) {
        std::cout << "construct A" << std::endl;
    }

    ~A() {
        std::cout << "destroy A" << std::endl;
    }
};

A f() {
    A a;
    return a;
}

struct AB {
    int a;
};

struct AC {
    int b;
};

struct AD : AB, AC {
    int c;
};

//template<typename T>
//void to_str(std::vector<std::string> &keys, const T &t) {
//    if constexpr (std::is_same_v<T, const char *> || std::is_same_v<T, std::string>) {
//        keys.template emplace_back(t);
//    } else {
//        keys.template emplace_back(std::to_string(t));
//    }
//}
//
//template<typename T, typename... Args>
//void to_str(std::vector<std::string> &keys, const T &t, const Args &... args) {
//    to_str(keys, t);
//    to_str(keys, args...);
//}
//
//template<typename V, typename... Args>
//V &find(const std::map<std::string, V> &m, const std::string &dft_key, const char &separator, const Args &... args) {
//    std::vector<std::string> keys;
//    to_str(keys, args...);
//    std::cout << keys.size() << std::endl;
//}

int main() {
    SimpleSafeMap<int, int> sm;
    sm.Insert(1, 12);
//    std::cout << "done" << std::endl;
    sm.SafetyRunV2([](decltype(sm) *m) {
        for (auto iter = m->Begin(); iter != m->End(); ++iter) {
            std::cout << iter->first << " - " << iter->second << std::endl;
        }
    });
//    std::string o = "";
//    std::map<std::string, int> mi;
//    mi["a_b_3"] = 1;
//    mi["a_b"] = 2;
//    mi["a"] = 3;
//    mi["all"] = 4;
//    find(mi, "all", '_',"a", "b", 3);
//    find(mi, "all", '_', 1, "b", 3);
//    find(mi, "all", '_', 1, 4ul, 3);
//    fa(1, 2, 3);
//    float no = -1.0;
//    float zero = 0, nzero = -0;
//    if (no == -1.0) {
//        std::cout << "yes" << std::endl;
//    }
//
//    if (zero == 0 && nzero == 0) {
//        std::cout << "yes2" << std::endl;
//    }
//    AD ad;
//    ad.a = 12;
//    std::cout << ad.a << std::endl;
//    std::cout << std::to_string(true) << std::endl;
    //    A a;
    //    {
    //        std::map<int, A> ma;
    //        ma[0] = std::move(a);
    //    }

//    {
//        std::vector<A> va;
//        va.reserve(10);
//        va.emplace_back(1);
//        va.emplace_back(2);
//        va.emplace_back(3);
//        std::cout << "before re" << std::endl;
//        va.reserve(2);
//
//        for (auto& v : va) {
//            std::cout << "> " << v.vi << std::endl;
//        }
//    }

//    std::cout << "done" << std::endl;
    //    A a = f();
    //    std::string s;
    //    s.append("1").append("2").append("3");
    //    std::cout << s << std::endl;
    //    {
    //        std::shared_ptr<A> l = std::shared_ptr<A>(new A());
    //    }
    //    std::cout << "done" << std::endl;
    //    std::srand(std::time(nullptr));
    //
    //    for (int i = 0; i < 100; ++i) {
    //        std::cout << std::rand() << std::endl;
    //    }
    return 0;
}