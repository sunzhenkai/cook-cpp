#include <iostream>
#include <memory>

#include "basic/sample_structs.h"

void fa() {
  Animal a;
  std::shared_ptr<Animal> ap(new Animal());
}

struct A {
  int value;
};

void fb() {
  static int value = 4;
  std::cout << value << std::endl;
  value = 5;
}

void fc() {
//  int a = nullptr; // ERR
  int b = NULL; // OK
}

int main() {
  fb();
  fb();
  return 0;
}