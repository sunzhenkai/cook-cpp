#include <arrow/type.h>
#include <arrow/type_fwd.h>

#include <memory>

#include "arrow/api.h"
#include "arrow/compute/api.h"
#include "arrow/compute/expression.h"
#include "arrow/extension_type.h"
#include "gtest/gtest.h"

// Doc: https://arrow.apache.org/docs/cpp/gandiva.html
/*
Gandiva 是一个运行时表达式编译器，使用 LLVM 生成高效的原生代码
  来对 Arrow Batch Record 进行计算。
Gandiva 只处理 Projections 和 Filters，其他转换使用 Compute Functions

使用 TreeExprBuilder 构建表达式树。
 */
TEST(ArrowGandiva, Expression) {
  // Gandiva提供了一个通用的表达式表示，其中表达式由节点树表示
  // 表达式树使用 TreeExprBuilder 构建
  // 表达式树的叶子，通常是字段引用（field reference）和字面值（literal value）
  //  > field reference 使用 TreeExprBuilder::MakeField() 创建
  //  > literal value 使用 TreeExprBuilder::MakeLiteral() 创建
  // 可以使用以下方法把节点组合成更复杂的表达式树
  //  > TreeExprBuilder::MakeFunction(), 创建 function 节点
  //    >可以调用 GetRegisteredFunctionSignatures() 获取所有可用的方法签名
  //  > TreeExprBuilder::MakeIf(), 创建 if-else 逻辑
  //  > TreeExprBuilder::MakeAnd()、TreeExprBuilder::MakeOr(), 创建布尔表达式
  //    > 对于 not 操作, 在 MakeFunction 中使用 not(bool) function
  //  InExpression 方法（比如 TreeExprBuilder::MakeInExpressionInt32()）创建 set membership tests
  // 每个方法都会创建节点。通过组合这些方法，可以创建任意复杂的树。
  // 一旦表达式树构建完，会被包装在 Expression 或 Condition 中，这取决于被怎样使用。
  //  > Expression 用于 Projections
  //  > Condition 用于 Filters
  //
  // 示例: 构建 expression: x+3, condition: x>3
  std::shared_ptr<arrow::Field> field_x_raw = arrow::field("x", arrow::int32());
}
