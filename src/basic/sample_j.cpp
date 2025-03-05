#include "iostream"
#include <vector>

#include "boost/algorithm/string.hpp"
#include "boost/spirit/home/x3.hpp"

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

void sort() {
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
}

using boost::spirit::x3::char_;
auto ident = +(char_("a-zA-z_0-9"));

void combine_rule() {
  std::vector<std::string> feature_columns;
  auto push = [&](auto &context) {
    feature_columns.push_back(_attr(context));
  };
  auto combine_rule = ident[push] % '#';
  std::string line = "a#b#c";
  std::cout << boost::spirit::x3::parse(line.begin(), line.end(), combine_rule) << std::endl;
  std::cout << feature_columns.size() << std::endl;
  for (auto &e: feature_columns) {
    std::cout << "> " << e << std::endl;
  }
}

int main() {
  combine_rule();
  return 0;
}