#include <iostream>

#include "climits"
#include "random"
#include "unordered_map"

class RandomGenerator {
  static int RandomInt() {
    static std::uniform_int_distribution<> dist_(0, INT_MAX);
    return dist_(gen_);
  }

 protected:
  static std::random_device rd_;
  static std::mt19937 gen_;
};

std::random_device RandomGenerator::rd_{};
std::mt19937 RandomGenerator::gen_{RandomGenerator::rd_()};

class A {
 public:
  explicit A(std::unordered_map<std::string, std::string> &&props) {}
};

void TestIter() {
  std::unordered_map<int, int> mi;
  for (int i = 0; i < 10; ++i) {
    mi[i] = i;
  }

  // 遍历关联容器并, 修改迭代器
  for (auto it : mi) {
    std::cout << it.first << " - " << it.second << std::endl;
    if (it.first == 5) mi.erase(it.first);
  }
  std::cout << " - " << std::endl;
  for (auto it : mi) {
    std::cout << it.first << " - " << it.second << std::endl;
  }
}

int main() {
  TestIter();
  //    A a(std::unordered_map<std::string, std::string>{{"a", "b"}});
  //
  //    std::random_device rd_;
  //    std::mt19937 gen_{rd_()};
  //
  //    for (int i = 0; i < 1000; ++i) {
  //        std::uniform_int_distribution<int> dist(0, 999);
  //        std::cout << dist(gen_) << std::endl;
  //    }
  //
  return 0;
}
