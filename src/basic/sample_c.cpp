#include "iostream"
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