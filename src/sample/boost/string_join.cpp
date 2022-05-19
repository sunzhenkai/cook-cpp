#include <iostream>
#include "vector"
#include "utils/utils.h"
#include <boost/algorithm/string.hpp>

using namespace std;

void string_split(const string &in, const string &seq, vector<string> &ret) {
    ret.clear();
    size_t last = 0;
    size_t index = in.find_first_of(seq, last);

    while (index != string::npos) {
        if (index > last) {
            ret.push_back(in.substr(last, index - last));
        }

        last = index + 1;
        index = in.find_first_of(seq, last);
    }

    if (index > last) {
        ret.push_back(in.substr(last, index - last));
    }
}

void string_split_v2(const string &in, const char &c, vector<string> &ret) {
    ret.clear();
    for (size_t i = 0, j = 0; j < in.size(); i = ++j) {
        while (j < in.size() && in[j] != c) ++j;
        if (j != i) {
            ret.emplace_back(std::move(in.substr(i, j - i)));
        }
    }
}

int main() {
    {
        std::vector<std::string> res;
        string_split_v2("", ':', res);
        utils::display(res);
        string_split_v2("a", ':', res);
        utils::display(res);
        string_split_v2("abc", ':', res);
        utils::display(res);
        string_split_v2(":a", ':', res);
        utils::display(res);
        string_split_v2("a:", ':', res);
        utils::display(res);
        string_split_v2("a::::", ':', res);
        utils::display(res);
        string_split_v2("a::::a", ':', res);
        utils::display(res);
        string_split_v2("a:::::ab:ccc:", ':', res);
        utils::display(res);
        string_split_v2("::::::a:", ':', res);
        utils::display(res);
        string_split_v2("1080x1080", 'x', res);
        utils::display(res);
    }

    std::string s = "a:b:c:d";
    int loop = 1000 * 10000;
    auto start = utils::now();
    for (int i = 0; i < loop; ++i) {
        vector<string> dest;
        string_split(s, ":", dest);
    }
    std::cout << "elapsed: " << utils::elapsed(start) << std::endl; // 1667

    start = utils::now();
    for (int i = 0; i < loop; ++i) {
        vector<string> dest;
        boost::split(dest, s, boost::is_any_of(":"));
    }
    std::cout << "elapsed: " << utils::elapsed(start) << std::endl; // 4337

    start = utils::now();
    for (int i = 0; i < loop; ++i) {
        vector<string> dest;
        string_split_v2(s, ':', dest);
    }
    std::cout << "elapsed: " << utils::elapsed(start) << std::endl; // 1121
    return 0;
} /** output
elapsed: 1667
elapsed: 4337
elapsed: 1121
 * */