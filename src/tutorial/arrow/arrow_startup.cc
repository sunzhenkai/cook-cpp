#include <arrow/type_fwd.h>

#include "arrow/type.h"
#include "gtest/gtest.h"

TEST(ArrowConceptions, Type) {
  // 1. data types
  // 每个类型都有对应的类
  // 1.1 通过枚举 Enums
  auto ai32 = arrow::Type::INT32;
  // 1.2 类型的基类
  arrow::DataType;
  // 1.3 工厂方法
  auto ArrowInt32Type = arrow::int32();
}
