#include "chrono"

using namespace std::literals;
// using namespace std::chrono_literals;

int main() {
  std::chrono::steady_clock;
  std::chrono::system_clock;
  std::chrono::high_resolution_clock;
  std::chrono::steady_clock::now();
  std::chrono::duration(10s);
  return 0;
}
