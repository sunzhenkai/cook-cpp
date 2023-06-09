#include <iostream>
#include "unordered_map"
#include "vector"
#include "utils/utils.h"
#include "boost/container/small_vector.hpp"

using namespace std;

class A {
public:
    A() {
        //        std::cout << "GO" << std::endl;
    }
    A(const int &a) {
        v = a;
    }
    int v;
};

void f(A &&a) {
}

void fb(A a) {
}

void SplitData(const std::string &s, const std::string &delim, std::vector<std::string> *ret) {
    ret->clear();
    size_t last = 0;
    size_t index = s.find_first_of(delim, last);
    while (index != std::string::npos) {
        ret->push_back(s.substr(last, index - last));
        last = index + 1;
        index = s.find_first_of(delim, last);
    }
    if (index - last > 0) {
        ret->push_back(s.substr(last, index - last));
    }
}

#define VALID_STR(s) (!s.empty() && s != "none" && s != "\"\"")
#define VALID_SV(s) (!s.empty() && s != "none"sv && s != "\"\""sv)

class FeatureGroup {
public:
    FeatureGroup() = default;

    explicit FeatureGroup(const std::string_view &t) {
        if (VALID_SV(t)) {
            splits.emplace_back(t);
        }
    }

    explicit FeatureGroup(const std::string &t) {
        if (VALID_STR(t)) {
            splits.emplace_back(t.c_str(), t.size());
        }
    }

    explicit FeatureGroup(std::string &&t) {
        str_holder = std::move(t);
        if (VALID_STR(str_holder)) {
            splits.emplace_back(str_holder.c_str(), str_holder.size());
        }
    }

    explicit FeatureGroup(const std::vector<std::string> &t) {
        splits.reserve(t.size());
        for (auto &s: t) {
            if (!VALID_STR(s)) continue;
            splits.emplace_back(s.c_str(), s.size());
        }
    }

    explicit FeatureGroup(std::vector<std::string> &&t) {
        str_vector_holder = std::move(t);
        splits.reserve(str_vector_holder.size());
        for (auto &s: str_vector_holder) {
            if (!VALID_STR(s)) continue;
            splits.emplace_back(s.c_str(), s.size());
        }
    }

    explicit FeatureGroup(const std::vector<std::string_view> &t) {
        splits.reserve(t.size());
        for (auto &v: t) {
            if (!VALID_SV(v)) continue;
            splits.emplace_back(v);
        }
    }

    explicit FeatureGroup(std::vector<std::string_view> &&t) {
        splits.reserve(t.size());
        for (auto &v: t) {
            if (!VALID_SV(v)) continue;
            splits.emplace_back(v);
        }
    }

    //    std::string DebugString();
    //    static std::string DebugString(FeatureGroup *);
    //    void FigureHashValues();
    //    const std::string_view &GetData(const size_t &idx) const;
    //    const std::uint64_t &GetHashValue(const size_t &idx) const;
    //    size_t GetSize() const;

    std::vector<std::string_view> splits;
    std::vector<std::uint64_t> hash_ids;
private:
    std::string str_holder;
    std::vector<std::string> str_vector_holder;
};

using SVHashVector = boost::container::small_vector<std::string_view, 1>;
template<typename StrCopyable>
class Cell {
public:
    Cell(StrCopyable &&cont) : content(std::forward<StrCopyable>(cont)) {
        if (content != "none" && !content.empty()) {
            //            splits.emplace_back(content.c_str(), content.length());
        }
    }

    Cell(const Cell &other) {
        content = other.content;
        //        splits.clear();
        //        if (content != "none" && !content.empty()) {
        //            splits.emplace_back(content.c_str(), content.length());
        //        }
        //        if (other.splits.size() > 1) {
        //            Split();
        //        }
    }
    Cell(std::vector<StrCopyable> &&array) {
        //        splits.reserve(array.size());
        //        for (auto &&str: array) {
        //            if (str != "none" && !str.empty()) {
        //                splits.emplace_back(std::move(str));
        //            }
        //        }
    }


    Cell(Cell &&other) {
        content = std::move(other.content);
        //        splits.clear();
        //        if (content != "none" && !content.empty()) {
        //            splits.emplace_back(content.c_str(), content.length());
        //        }
        //        if (other.splits.size() > 1) {
        //            Split();
        //        }
    }

    Cell &operator=(const Cell &other) {
        content = other.content;
        //        splits.clear();
        //        if (content != "none" && !content.empty()) {
        //            splits.emplace_back(content.c_str(), content.length());
        //        }
        //        if (other.splits.size() > 1) {
        //            Split();
        //        }
        return *this;
    }

    Cell &operator=(Cell &&other) {
        content = std::move(other.content);
        //        splits.clear();
        //        if (content != "none" && !content.empty()) {
        //            splits.emplace_back(content.c_str(), content.length());
        //        }
        //        if (other.splits.size() > 1) {
        //            Split();
        //        }
        return *this;
    }

    void Split(const char *delim = "\u0001") {
        //        if (!splits.empty()) {
        ////            splits = Common::splitSVAndFilter(splits[0].sv_, delim);
        //        }
    }

    //    const SVHashVector &Access() const {
    //        return splits;
    //    }

    std::string ToString() const {
        //        std::ostringstream sout;
        //        sout << "[";
        //        for (size_t i = 0; i < splits.size(); i++)
        //            sout << (i ? ", " : "") << details::ToSource(splits.at(i).sv_) << "," << splits.at(i).hashcode_;
        //        sout << "]";
        //        return sout.str();
    }

private:
    StrCopyable content;
    SVHashVector splits;
};


void p() {
    std::string_view vv;
    {
        std::string v = "hello";
        v = v + " world";
        //        vv = std::move(v);
        vv = std::string_view(v.data(), v.size());
        std::cout << v << std::endl;
        //        v = "no";
    }
    std::vector<std::string> vvs;
    std::string dest = "hello world";
    std::string tv = "ggggg";
    //    for (int i = 0; i < 100000000; i++) {
    //        vvs.emplace_back(tv + "hhhhhh");
    //    }
    int i = 0;
    while (vv == dest) {
        vvs.emplace_back(tv + "hhhh" + std::to_string(i++));
        if (vvs.size() >= 2 && (&vvs[vvs.size() - 2] > &vvs[vvs.size() - 1])) {
            break;
        }
        if (vvs.size() > 2) {
            //            std::cout << (&vvs[vvs.size() - 2]) << " - " << (&vvs[vvs.size() - 1]) << std::endl;
        }
    }
    tv = tv + "ss";
    std::cout << vv << std::endl;
}

struct FeatureGroupData {
    std::vector<std::string_view> splits;
    std::vector<std::uint64_t> hash_ids;
};

struct FeatureGroupDataStr : FeatureGroupData {
    std::string holder;

    explicit FeatureGroupDataStr(std::string &&s);
};

class FeatureGroupB {
public:
    FeatureGroupData *fgd{nullptr};
};

struct B {
    virtual ~B() = default;
};

struct BB : public B {
    int v;
    B *b;
};

void StringSplit(const std::string &in, const char &c, std::vector<std::string> &ret) {
    ret.clear();
    for (size_t i = 0, j = 0; j < in.size(); i = ++j) {
        while (j < in.size() && in[j] != c) ++j;
        if (j != i) {
            ret.emplace_back(std::move(in.substr(i, j - i)));
        }
    }
}

vector<string> SplitV2(const string &str, const char &delim, std::vector<std::string> &res) {
    res.clear();
    size_t start = 0, end = 0; // 记录当前子串的起始和结束位置
    while ((end = str.find(delim, start)) != string::npos) { // 查找分隔符出现的位置
        res.push_back(str.substr(start, end - start)); // 提取子串并保存到 vector 中
        start = end + 1; // 更新起始位置
    }
    res.push_back(str.substr(start)); // 处理最后一个子串（如果存在）
    return res;
}

int main() {
    //    std::vector<std::string> result;
    //    SplitV2("1^2^3^^", '^', result);
    //    std::cout << result.size() << std::endl;
    //
    //    std::string_view sv = "go"sv;
    //    std::vector<std::string_view> svv;
    //    svv.emplace_back(sv);
    //    std::cout << sv << std::endl;
    //    //    B *b = new BB();
    //    //    delete b;
    //    //
    //    //    BB *bb = new BB();
    //    //    std::cout << bb->b << std::endl;
    //    std::cout << sizeof(FeatureGroupB) << std::endl;
    //    std::cout << sizeof(std::string) << std::endl;
    //    std::cout << sizeof(std::shared_ptr<int>) << std::endl;
    //    std::cout << sizeof(std::vector<std::string>) << std::endl;
    //    std::cout << sizeof(std::vector<::uint64_t>) << std::endl;
    //    std::cout << sizeof(std::vector<std::pair<int, int>>) << std::endl;
    //    p();

    //    std::cout << sizeof(FeatureGroup) << std::endl;
    //    std::cout << sizeof(Cell<std::string>) << std::endl;
    //    //    std::vector<std::string> result;
    //    //    SplitData("1,1", ",", &result);
    //    //    std::cout << result.size() << std::endl;
    //    //    std::cout << result[0] << std::endl;
    //
    //    //    A a;
    //    //    f(std::move(a));
    //    //    f(A());
    //    //    f(std::move(A()));
    //    //    fb(a);
    //    //    fb(std::move(a));
    //    //
    //    //    a.v;
    //    //    std::vector<int> vi;
    //    //    std::cout << vi.capacity() << std::endl;
    //    //    vi.reserve(100);
    //    //    std::cout << vi.capacity() << std::endl;
    //    //    vi.resize(10);
    //    //    std::cout << vi.capacity() << std::endl;
    //
    //    std::shared_ptr<A> a;
    //    std::cout << a.get() << std::endl;
    //
    std::vector<std::shared_ptr<A> > b;
    //    std::vector<A> c;
    //
    int loop = 1000 * 10000;
    b.reserve(loop + 10);
    auto start = utils::now();
    for (int i = 0; i < loop; ++i) {
        A *ap = new A(1);
//        delete ap;
        b.push_back(std::shared_ptr<A>(ap));
//        b.push_back(std::move(std::make_shared<A>(1)));
        //        b.emplace_back(std::make_shared<A>());
        //        b.emplace_back(std::move(std::make_shared<A>()));
    }
    auto el = utils::elapsed(start);
    std::cout << el << std::endl;

    //    c.reserve(loop + 10);
    //    start = utils::now();
    //    for (int i = 0; i < loop; ++i) {
    //        c.resize(i);
    //    }
    //    //    c.resize(loop / 10);
    //    el = utils::elapsed(start);
    //    std::cout << el << std::endl;
    //
    //    std::vector<Cell<std::string>> e;
    //    e.reserve(loop + 10);
    //    start = utils::now();
    //    for (int i = 0; i < loop; ++i) {
    //        e.emplace_back("");
    //    }
    //    //    c.resize(loop);
    //    el = utils::elapsed(start);
    //    std::cout << el << std::endl;
    //
    //    std::vector<FeatureGroup> f;
    //    f.reserve(loop + 10);
    //    std::string t;
    //    start = utils::now();
    //    for (int i = 0; i < loop; ++i) {
    //        f.emplace_back(t);
    //    }
    //    //    c.resize(loop);
    //    el = utils::elapsed(start);
    //    std::cout << el << std::endl;
    //
    //    //    for (int i = 0; i < 10000 * 10000; ++i) {
    //    //
    //    //    }
    return 0;
}