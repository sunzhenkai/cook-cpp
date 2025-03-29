#pragma once
#include <babylon/anyflow/builder.h>
class PlusProcessor : public babylon::anyflow::GraphProcessor {
 public:
  int process() noexcept override {
    *z.emit() = *x + *y;
    return 0;
  }

  // clang-format off
  ANYFLOW_INTERFACE(
    ANYFLOW_DEPEND_DATA(int, x)
    ANYFLOW_DEPEND_DATA(int, y) 
    ANYFLOW_EMIT_DATA(int, z))
  // clang-format on
};

void RunStartupGraph();
void RunStartupGraphV2();
