#include "arrow/dataset/plan.h"
#include "gtest/gtest.h"

// https://arrow.apache.org/docs/cpp/
int main(int argc, char **argv) {
  arrow::dataset::internal::Initialize();
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
