#include "sample/simple/template_class.h"

#include "iostream"
#include "memory"

namespace simple {
template <typename T>
void TCls<T>::f() {
  auto v = std::make_shared<T>();
  std::cout << "f(): " << *v.get() << std::endl;
}

template <typename T>
void NonTCls::f() {
  T t{};
  std::cout << t << std::endl;
}
}  // namespace simple

int main() {
  simple::TCls<int> t;
  t.f();

  simple::NonTCls nt;
  nt.f<int>();
  return 0;
}
