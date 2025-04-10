#include <arrow/array/array_nested.h>
#include <arrow/result.h>
#include <arrow/scalar.h>
#include <arrow/status.h>
#include <arrow/type_fwd.h>
#include <arrow/visit_type_inline.h>

#include <cstdint>
#include <memory>
#include <random>

#include "arrow/api.h"
#include "arrow/builder.h"
#include "arrow/record_batch.h"
#include "arrow/type.h"
#include "gtest/gtest.h"

TEST(ArrowStatus, A) {
  arrow::NullBuilder nb;
  arrow::Status st = nb.Reserve(2);
  std::cout << "[S] 1 > " << st << std::endl;
  st = nb.AppendNulls(-1);
  std::cout << "[S] 2 > " << st << std::endl;
  std::cout << "[S] 3 > " << arrow::Status::OK() << std::endl;

  // check status, reture the error status if not ok
  ARROW_RETURN_NOT_OK(nb.AppendNulls(-1));
  std::cout << "hey, this is unreachable code" << std::endl;
}

/**
Apache Arrow 的 DataType, Scalar 和 Array 类型体系采用了多态设计
每个基类都有大量具体子类（例如 Int32Type, StringScalar, FloatArray 等）
访问者模式可帮助开发者‌针对不同子类编写类型特化逻辑‌，同时保持代码的可扩展性和性能。

VisitTypeInline, DataType 子类, 数据类型元操作（如类型转换）
VisitScalarInline, Scalar 子类, 标量值处理（如序列化/反序列化）
VisitArrayInline, Array 子类, 批量数据处理（如统计分析）

Arrow 提供 Visitors 工具类，来遍历特定的子类
*/
TEST(ArrowVistor, Basic) {
  class IntVistor {
   public:
    arrow::Status Visit(const arrow::DataType &tp, int arg) {
      std::cout << "unknown type: " << tp.ToString() << std::endl;
      return arrow::Status::OK();
    }
    arrow::Status Visit(const arrow::Int32Type &tp, int arg) {
      std::cout << "Int32 Type, arg=" << arg << std::endl;
      return arrow::Status::OK();
    };
    arrow::Status Visit(const arrow::Int64Type &tp, int arg) {
      std::cout << "Int64 Type" << std::endl;
      return arrow::Status::OK();
    };
  };
  class IntVistorNoArg {
   public:
    arrow::Status Visit(const arrow::DataType &tp) {
      std::cout << "unknown type: " << tp.ToString() << std::endl;
      return arrow::Status::UnknownError(tp.ToString());
    }
    arrow::Status Visit(const arrow::Int32Type &tp) {
      std::cout << "Int32 Type, arg=" << std::endl;
      return arrow::Status::OK();
    };
    arrow::Status Visit(const arrow::Int64Type &tp) {
      std::cout << "Int64 Type" << std::endl;
      return arrow::Status::OK();
    };
  };

  auto intTp = arrow::int32();
  auto strTp = arrow::utf8();
  IntVistor intv;
  std::cout << arrow::VisitTypeInline(*intTp, &intv, 1);
  IntVistorNoArg ivn;
  std::cout << "---" << std::endl;
  std::cout << arrow::VisitTypeInline(*intTp, &ivn) << std::endl;
  std::cout << arrow::VisitTypeInline(*strTp, &ivn) << std::endl;
}

TEST(ArrowConceptions, Type) {
  // 1. data types
  // 每个类型都有对应的类
  // 1.1 通过枚举 Enums
  auto ai32 = arrow::Type::INT32;
  // 1.2 类型的基类
  arrow::DataType;
  // 1.3 工厂方法
  auto ArrowInt32Type = arrow::int32();

  // 2. Scalar
  // 标量, 单个不可变值, 包含元素值及其类型
  // 变量作为函数单值输入时很有用
  // 虽然可以作为 Array 的元素，但是会产生额外的包装成本(比如额外的类型信息)
  arrow::Result<std::shared_ptr<arrow::Scalar>> i32_scalar = arrow::MakeScalar(arrow::int32(), 10);
  std::shared_ptr<arrow::Scalar> i32_scalar2 = arrow::MakeScalar(12);  // 自行推断类型
  std::cout << "[SC]1> " << i32_scalar->get()->ToString() << std::endl;
  std::cout << "[SC]2> " << i32_scalar2->ToString() << std::endl;
}

class RandomBatchGenerator {
 public:
  std::shared_ptr<arrow::Schema> schema;

  RandomBatchGenerator(std::shared_ptr<arrow::Schema> schema) : schema(schema) {}

  arrow::Result<std::shared_ptr<::arrow::RecordBatch>> Generate(int32_t num_rows) {
    num_rows_ = num_rows;
    // for (size_t i = 0; i < schema->num_fields(); ++i) {
    //   ARROW_RETURN_NOT_OK(arrow::VisitTypeInline(*(schema->field(-i)->type()), this));
    // }
    for (std::shared_ptr<arrow::Field> f : schema->fields()) {
      ARROW_RETURN_NOT_OK(arrow::VisitTypeInline(*f->type(), this));
    }
    return arrow::RecordBatch::Make(schema, num_rows, arrays_);
  }

  arrow::Status Visit(const arrow::DataType &tp) {
    return arrow::Status::NotImplemented("Generate data for ", tp.ToString());
  }

  arrow::Status Visit(const arrow::DoubleType &) {
    auto builder = arrow::DoubleBuilder();
    std::normal_distribution<> d{/*mean=*/0.5, /*stddev=*/2.0};
    for (int i = 0; i < num_rows_; ++i) {
      ARROW_RETURN_NOT_OK(builder.Append(d(gen_)));
    }
    ARROW_ASSIGN_OR_RAISE(auto array, builder.Finish());
    arrays_.push_back(array);
    return arrow::Status::OK();
  }

  arrow::Status Visit(const arrow::ListType &type) {
    std::poisson_distribution<> d{/*mean*/ 4};
    // 借助 RandomBatchGenerator 生成一维的随机数据，再进行拷贝
    auto builder = arrow::Int32Builder();
    ARROW_RETURN_NOT_OK(builder.Append(0));
    int32_t last_val = 0;
    for (int32_t i = 0; i < num_rows_; ++i) {
      last_val += d(gen_);
      ARROW_RETURN_NOT_OK(builder.Append(last_val));
    }
    ARROW_ASSIGN_OR_RAISE(auto offsets, builder.Finish());

    // 生成一维数据
    RandomBatchGenerator value_gen(arrow::schema({arrow::field("x", type.value_type())}));
    ARROW_ASSIGN_OR_RAISE(auto inner_batch, value_gen.Generate(last_val));
    std::shared_ptr<arrow::Array> values = inner_batch->column(0);
    ARROW_ASSIGN_OR_RAISE(auto array, arrow::ListArray::FromArrays(*offsets, *values));
    arrays_.push_back(array);
    return arrow::Status::OK();
  }

 private:
  std::random_device rd_{};
  std::mt19937 gen_{rd_()};
  std::vector<std::shared_ptr<arrow::Array>> arrays_;
  int32_t num_rows_;
};

TEST(ArrowData, GenerateRandom) {
  std::shared_ptr<arrow::Schema> schema = arrow::schema({
      arrow::field("x", arrow::float64()),
      arrow::field("y", arrow::list(arrow::float64())),
  });
  RandomBatchGenerator generator(schema);
  ARROW_ASSIGN_OR_RAISE(std::shared_ptr<arrow::RecordBatch> batch, generator.Generate(5));

  std::cout << "Created batch:\n" << batch->ToString() << std::endl;

  ARROW_RETURN_NOT_OK(batch->ValidateFull());
}
