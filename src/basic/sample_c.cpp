#include "iostream"
#define GetStringDataAddress(s) static_cast<void *>(&s[0])

std::string GetString() {
    std::string t = "abc";
    std::string res = t + "def";
    std::cout << "A " << GetStringDataAddress(res) << std::endl;
    return res; // 函数返回临时变量, 未进行对象拷贝
}

void GetStringAddrA(std::string &&s) {
    std::cout << "C " << GetStringDataAddress(s) << " " << s << std::endl;
    s = s + "GG";
    std::string t = s;
    t += "HH";
}

void GetStringAddrB(std::string s) {
    std::cout << "D " << GetStringDataAddress(s) << " " << s << std::endl;
}

int main() {
    std::cout << "01 ---" << std::endl;
    auto r = GetString(); // 右值引用赋值给左值变量, 不进行对象拷贝
    std::cout << "B " << GetStringDataAddress(r) << std::endl;
    std::cout << "02 ---" << std::endl;
    auto r2 = std::move(GetString());
    std::cout << "B " << GetStringDataAddress(r2) << std::endl;
    std::cout << "03 ---" << std::endl;
    auto r21 = std::forward<std::string>(GetString());
    std::cout << "B " << GetStringDataAddress(r21) << std::endl;
    std::cout << "04 ---" << std::endl;
    std::string r3 = GetString();
    GetStringAddrA(std::move(r3));
    std::cout << "05 ---" << std::endl;
    std::string r31 = r2;
    std::cout << "B " << GetStringDataAddress(r31) << std::endl;
    GetStringAddrA(std::move(r31));
    std::cout << "06 ---" << std::endl;
    auto r4 = GetString();
    GetStringAddrB(std::forward<std::string>(r4));

    std::cout << std::endl << std::endl;
    std::cout << "1 " << r << std::endl;
    std::cout << "2 " << r2 << std::endl;
    std::cout << "3 " << r21 << std::endl;
    std::cout << "4 " << r3 << std::endl;
    std::cout << "5 " << r31 << std::endl;
    std::cout << "6 " << r4 << std::endl;

    r3 = "asd";
    r31 = "ase";
    std::cout << std::endl << std::endl;
    std::cout << "1 " << r << std::endl;
    std::cout << "2 " << r2 << std::endl;
    std::cout << "3 " << r21 << std::endl;
    std::cout << "4 " << r3 << std::endl;
    std::cout << "5 " << r31 << std::endl;
    std::cout << "6 " << r4 << std::endl;
    std::cout << "07 ---" << std::endl;
    std::string r5 = r;
    std::cout << "A " << GetStringDataAddress(r5) << " " << r5 << std::endl;
    std::string r6 = std::move(r5);
    std::cout << "B " << GetStringDataAddress(r5) << " " << r5 << std::endl;
    std::cout << "C " << GetStringDataAddress(r6) << " " << r6 << std::endl;
    return 0;

// 2
#include "vector"

void StringSplit(const std::string &in, const char &c, std::vector<std::string> &ret) {
    ret.clear();
    for (size_t i = 0, j = 0; j <= in.size(); i = ++j) {
        while (j < in.size() && in[j] != c) ++j;
        ret.emplace_back(std::move(in.substr(i, j - i)));
    }
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

void PrintVector(std::vector<std::string> &v) {
    for (auto &s: v) {
        std::cout << s << "|";
    }
    std::cout << std::endl;
}

int main() {
    std::string s = ",aa,ad,a,a,,,a,,,a,";
    std::vector<std::string> v;
    StringSplit(s, ',', v);
//    SplitData(s, ",", &v);
    std::cout << v.size() << std::endl;
    PrintVector(v);


//    int a[10] = {0};
//    std::cout << sizeof(a) << std::endl;
//    for (int i: a) {
//        std::cout << i << std::endl;
//    }
//
//    int b[3][3] = {0};
//    for (auto i: b) {
//        for (int j = 0; j < 3; ++j) {
//            std::cout << i[j] << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    int size = 3;
//    int *c = new int[size];
//    std::cout << sizeof(c) << " - " << sizeof(*c) << std::endl;
////    memset(c, 0, size * sizeof(*c));
//    delete[] c;
//    return 0;
}
