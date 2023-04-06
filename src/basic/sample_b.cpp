#include "iostream"
#include "fmt/format.h"
#include "regex"
#include "string_view"
#include "unordered_map"

using namespace std::string_view_literals;

namespace std {
    std::string to_string(const std::string &s) {
        return s;
    }
}

//template<typename T>
//std::string ToString(const T &t) {
//    if constexpr (std::is_same<T, std::string>::value) {
//        return static_cast<std::string>(t);
//    } else {
//        return std::to_string(t);
//    }
//}

template<typename T>
std::string ToString(const T &t) {
    return fmt::format("{}", t);
}

//template<typename T>
//std::string ToString(const T *t) {
//    return fmt::format("{}", t);
//}

void f1(const std::string &s) {
    std::cout << ToString(s) << std::endl;
}

template<typename T>
void f2(const T &s) {
    std::cout << ToString(s) << std::endl;
}

template<typename T>
void f2(const T *s) {
    std::cout << ToString(s) << std::endl;
}

struct SMA {
    float f{0.0};
    int order{0};
};

void f3() {
    std::vector<SMA> s;
    s.resize(10);
    std::vector<SMA *> sp;
    int start = 0;
    for (auto &sm: s) {
        sp.emplace_back(&sm);
        sm.order = ++start;
    }
    std::sort(s.begin(), s.end(), [&](const SMA &a, const SMA &b) {
        return a.f < b.f;
    });
    for (int i = 0; i < s.size(); ++i) {
        //        std::cout << &s[i] << " - " << sp[i] << " - " << s[i].f << std::endl;
        if (s[i].f == sp[i]->f) {
            std::cout << "+";
        } else {
            std::cout << "-";
        }
    }
}

static bool startsWith(const std::string &s, const std::string &prefix) {
    return s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
}

bool StartsWith(const std::string &compared, const std::string &comparing) {
    return compared.size() >= comparing.size() &&
           compared.compare(0, comparing.size(), comparing) == 0;
}

struct AA {
    int i;
    bool b;
    std::string s;
};

class BB {
public:
    BB(std::string v) {
        m.emplace(v, v);
    }

    std::unordered_map<std::string, std::string> m;
};

std::time_t GetFileTimeFromString(const std::string &time_str, const char *format) {
    struct tm tm;
    tm.tm_sec = 0;
    sscanf(time_str.c_str(),
           format,
           &tm.tm_year,
           &tm.tm_mon,
           &tm.tm_mday,
           &tm.tm_hour,
           &tm.tm_min,
           &tm.tm_sec);
    --tm.tm_mon;
    tm.tm_year -= 1900;
    /* mktime determines if Daylight Saving Time was in effect
     * see: http://en.cppreference.com/w/cpp/chrono/c/mktime */
    tm.tm_isdst = 0;
    return std::mktime(&tm);
}

template<typename T, typename... Rest>
inline void HashCombine(std::size_t &seed, const T &v, const Rest &... rest) {
    seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    (HashCombine(seed, rest), ...);
}

int main() {
    std::size_t result = 0;
    HashCombine(result, 1, 0, 0);
    std::cout << result << std::endl;
    //    auto t = GetFileTimeFromString("", "%4d%2d%2d%2d%2d");
    //    std::cout << t << std::endl;
    //    BB bb("hello");
    //    std::cout << bb.m.size() << std::endl;
    //    AA a{10, true, "hello"};
    //    AA b = std::move(a);
    //    std::cout << a.i << " - " << a.b << " - " << a.s << std::endl;
    //    std::cout << b.i << " - " << b.b << " - " << b.s << std::endl;
    //    //    std::cout << (379158254l ^ 3 ^ 1206216001l ^ 1217285001l ^ 1363775002l ^ -302l ^ 904l ^ 102l ^ 0l ^ 2835797446l) << std::endl;
    //    //    std::cout << (379158254l ^ 3 ^ 1363641001l ^ 1217285001l ^ 1363775002l ^ -302l ^ 904l ^ 102l ^ 0l ^ 2835797446l) << std::endl;
    //    std::string s = "on:log";
    //    std::string sa = "on:";
    //    std::cout << StartsWith("on:log", "on") << std::endl;
    //    std::cout << StartsWith("on:log", "on:") << std::endl;
    //    std::cout << StartsWith("on:log", "on,") << std::endl;
    //    std::cout << StartsWith("on:log", "on:l") << std::endl;
    //    std::cout << StartsWith("on:log", "aon:l") << std::endl;
    //    f3();
    //    std::to_string("a");
    //    uint64_t i6 = 140729257965632;
    //    int64_t ui6 = i6;
    //    std::cout << i6 << " - " << ui6 << std::endl;
    //    f1("hello");
    //    f2("hello");
    //    std::string_view v = R"("g)";
    //    std::cout << std::regex_replace(std::string(v), std::regex("\""), "\\\"") << std::endl;
    //    std::vector<std::shared_ptr<int>> shr;
    //    shr.resize(10000);
    //    for (auto &s: shr) {
    //        std::cout << s.get() << std::endl;
    //    }
    return 0;
}