#include "iostream"
#include <vector>

/**
 * 自定义类排序
 */

class ClsSortable {
public:
    int a;
    std::string b;

    bool operator>(const ClsSortable &obj) const {
        if (a == obj.a) return b > obj.b;
        return a > obj.a;
    }
};

int main() {
    std::vector<ClsSortable> ls = {{1, "2"},
                                   {1, "1"},
                                   {3, "1"},
                                   {3, "3"},
                                   {2, "1"}};
    std::sort(ls.begin(), ls.end(), std::greater<>());
    // 打印排序后的结果
    for (auto &i: ls) {
        std::cout << i.a << " " << i.b << std::endl;
    }
    return 0;
}