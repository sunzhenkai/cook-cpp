#include <arrow/array/array_base.h>
#include <arrow/array/array_nested.h>
#include <arrow/compute/api_aggregate.h>
#include <arrow/compute/exec.h>
#include <arrow/datum.h>
#include <arrow/result.h>
#include <arrow/scalar.h>
#include <arrow/status.h>
#include <arrow/table.h>
#include <arrow/type_fwd.h>
#include <arrow/visit_type_inline.h>

#include <cstdint>
#include <memory>
#include <random>

#include "arrow/api.h"
#include "arrow/builder.h"
#include "arrow/chunked_array.h"
#include "arrow/compute/api.h"
#include "arrow/ipc/json_simple.h"
#include "arrow/record_batch.h"
#include "arrow/type.h"
#include "gtest/gtest.h"

/**
 * 1. cookbook: https://arrow.apache.org/cookbook/cpp/basic.html
 */

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
    std::poisson_distribution<> d{/*mean*/ 3};
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
  ARROW_ASSIGN_OR_RAISE(std::shared_ptr<arrow::RecordBatch> batch, generator.Generate(3));

  std::cout << "Created batch:\n" << batch->ToString() << std::endl;

  ARROW_RETURN_NOT_OK(batch->ValidateFull());
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

  // 3. Array
  arrow::Result<std::shared_ptr<arrow::Array>> arr =
      arrow::ipc::internal::json::ArrayFromJSON(arrow::int32(), R"([1, 2, 3])");
  // Result: A class for representing either a usable value, or an error.
  // auto value = arr.ValueOrDie();
  // arr.ValueOrElse(G &&generate_alternative)
  // auto status = arr.Value(U *out); // set out & return status

  std::cout << "[AR]1> " << arr->get()->ToString() << std::endl;

  // 4. Chunked Array
  auto arr1 = arrow::ipc::internal::json::ArrayFromJSON(arrow::int32(), R"([1, 2, 3])");
  auto arr2 = arrow::ipc::internal::json::ArrayFromJSON(arrow::int32(), R"([4, 5])");
  auto ca = arrow::ChunkedArray::Make({*arr1, *arr2});
  std::cout << "[CA]1> " << ca->get()->ToString() << std::endl;
}

TEST(ArrowConceptions, BasicDataStructures) {
  // 1. Arrays
  arrow::Int8Builder i8b;
  int8_t days_raw[5] = {1, 12, 17, 23, 28};
  ARROW_RETURN_NOT_OK(i8b.AppendValues(days_raw, 5));
  std::shared_ptr<arrow::Array> days;
  ARROW_ASSIGN_OR_RAISE(days, i8b.Finish());
  std::cout << "[BD]1> " << days->ToString() << std::endl;
  // 1.1 after calling Finish, builder is reusable
  int8_t months_raw[5] = {1, 3, 5, 7, 11};
  ARROW_RETURN_NOT_OK(i8b.AppendValues(months_raw, 5));
  std::shared_ptr<arrow::Array> months;
  ARROW_ASSIGN_OR_RAISE(months, i8b.Finish());
  std::cout << "[BD]2> " << months->ToString() << std::endl;

  arrow::Int16Builder i16b;
  int16_t years_raw[5] = {1993, 1999, 2000, 2020, 2025};
  ARROW_RETURN_NOT_OK(i16b.AppendValues(years_raw, 5));
  std::shared_ptr<arrow::Array> years;
  ARROW_ASSIGN_OR_RAISE(years, i16b.Finish());
  std::cout << "[BD]4> " << months->ToString() << std::endl;

  // 2. ChunkedArrays
  auto ca = arrow::ChunkedArray::Make({days, months});
  std::cout << "[BD]3> " << ca->get()->ToString() << std::endl;
  // 3. RecordBatch, from Arrays
  // 3.1 Define schema
  std::shared_ptr<arrow::Field> field_day, field_month, field_year;
  std::shared_ptr<arrow::Schema> schema;
  field_day = arrow::field("Day", arrow::int8());
  field_month = arrow::field("Month", arrow::int8());
  field_year = arrow::field("Year", arrow::int8());
  schema = arrow::schema({field_day, field_month, field_year});
  // 3.2 Build BatchRecord
  std::shared_ptr<arrow::RecordBatch> rb;
  rb = arrow::RecordBatch::Make(schema, days->length(), {days, months, years});
  std::cout << "[BD]5> " << rb->ToString() << std::endl;
  // 4. Table, from ChunkedArrays
  // 4.1 chunked arrayes
  int8_t days_raw2[5] = {6, 12, 3, 30, 22};
  ARROW_RETURN_NOT_OK(i8b.AppendValues(days_raw2, 5));
  std::shared_ptr<arrow::Array> days2;
  ARROW_ASSIGN_OR_RAISE(days2, i8b.Finish());
  int8_t months_raw2[5] = {5, 4, 11, 3, 2};
  ARROW_RETURN_NOT_OK(i8b.AppendValues(months_raw2, 5));
  std::shared_ptr<arrow::Array> months2;
  ARROW_ASSIGN_OR_RAISE(months2, i8b.Finish());
  int16_t years_raw2[5] = {1980, 2001, 1915, 2020, 1996};
  ARROW_RETURN_NOT_OK(i16b.AppendValues(years_raw2, 5));
  std::shared_ptr<arrow::Array> years2;
  ARROW_ASSIGN_OR_RAISE(years2, i16b.Finish());
  arrow::ArrayVector days_vec{days, days2};
  std::shared_ptr<arrow::ChunkedArray> day_chunked = arrow::ChunkedArray::Make(days_vec).ValueOrDie();
  arrow::ArrayVector months_vec{months, months2};
  std::shared_ptr<arrow::ChunkedArray> month_chunked = arrow::ChunkedArray::Make(months_vec).ValueOrDie();
  arrow::ArrayVector years_vec{years, years};
  std::shared_ptr<arrow::ChunkedArray> years_chunked = arrow::ChunkedArray::Make(years_vec).ValueOrDie();
  // 4.2 Making Table
  std::shared_ptr<arrow::Table> table;
  table = arrow::Table::Make(schema, {day_chunked, month_chunked, years_chunked}, 10);
  std::cout << "[BD]6> " << table->ToString() << std::endl;
}

// Docs: https://arrow.apache.org/docs/cpp/tutorials/compute_tutorial.html
TEST(ArrowConceptions, Computer) {
  std::cout << "[CMP]0> start" << std::endl;
  // 0. prepare
  arrow::Int32Builder i32b;
  int32_t some_int32_raw[5] = {12, 234, 8324, 32819, 393928};
  ARROW_RETURN_NOT_OK(i32b.AppendValues(some_int32_raw, 5));
  std::cout << "[CMP]0> start" << std::endl;
  ARROW_ASSIGN_OR_RAISE(auto some_nums, i32b.Finish());
  int32_t more_int32_raw[5] = {1323, 943, 129, 99, 12393};
  ARROW_RETURN_NOT_OK(i32b.AppendValues(more_int32_raw, 5));
  std::cout << "[CMP]0> start" << std::endl;
  ARROW_ASSIGN_OR_RAISE(auto more_nums, i32b.Finish());
  std::cout << "[CMP]0> start" << std::endl;

  auto schema = arrow::schema({
      arrow::field("A", arrow::int32()),
      arrow::field("B", arrow::int32()),
  });
  auto table = arrow::Table::Make(schema, {some_nums, more_nums}, 5);
  std::cout << "[CMP]0> start" << std::endl;
  // 1. datums
  // The datums class is what all compute functions output to
  //  and then can take datums as input, as well
  arrow::Datum sum;
  std::cout << "[CMP]0> start" << std::endl;
  auto r = arrow::compute::Sum({table->GetColumnByName("A")});
  ARROW_ASSIGN_OR_RAISE(sum, arrow::compute::Sum({table->GetColumnByName("A")}));
  std::cout << "[CMP]1> " << sum.ToString() << " - " << sum.type()->ToString() << std::endl;
  // Datum 不能简单得推断我们的数据类型，需要显示指定我们需要的类型
  std::cout << "[CMP]2> " << sum.scalar_as<arrow::Int64Scalar>().value << std::endl;
  // 1.1 CallFunction: add
  // element wise sum: add elements at the same position
  arrow::Datum element_wise_sum;
  ARROW_ASSIGN_OR_RAISE(element_wise_sum, arrow::compute::CallFunction("add", {
                                                                                  table->GetColumnByName("A"),
                                                                                  table->GetColumnByName("B"),
                                                                              }));
  std::cout << "[CMP]3> " << element_wise_sum.ToString() << " - " << element_wise_sum.type()->ToString() << std::endl;
  // 1.2 CallFunction: index
  arrow::Datum third_item;
  arrow::compute::IndexOptions index_options;
  index_options.value = arrow::MakeScalar(8324);
  // get index of value 8324
  ARROW_ASSIGN_OR_RAISE(third_item,
                        arrow::compute::CallFunction("index", {table->GetColumnByName("A")}, &index_options));
  std::cout << "[CMP]4> " << third_item.ToString() << " - " << third_item.type()->ToString() << std::endl;
  std::cout << "[CMP]5> " << third_item.scalar_as<arrow::Int64Scalar>().value << std::endl;

  // 2. kernels
  // 3. acero
}
