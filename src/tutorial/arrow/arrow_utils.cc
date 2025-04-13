// 1. DataSet, Table, RecordBatch, ExecBatch

#include "tutorial/arrow/arrow_utils.h"

#include <arrow/array/array_primitive.h>
#include <arrow/array/builder_primitive.h>
#include <arrow/compute/exec.h>
#include <arrow/dataset/api.h>
#include <arrow/dataset/dataset.h>
#include <arrow/record_batch.h>
#include <arrow/result.h>
#include <arrow/status.h>
#include <arrow/table.h>
#include <arrow/type.h>
#include <arrow/type_fwd.h>
#include <arrow/util/async_generator.h>
#include <arrow/util/async_generator_fwd.h>
#include <sys/types.h>

#include <iostream>
#include <limits>
#include <memory>
#include <vector>

arrow::Result<std::shared_ptr<arrow::RecordBatch>> GetSampleRecordBatch(
    const arrow::ArrayVector& array_vector, const arrow::FieldVector& field_vector) {
  std::shared_ptr<arrow::RecordBatch> record_batch;
  ARROW_ASSIGN_OR_RAISE(auto struct_result, arrow::StructArray::Make(array_vector, field_vector));
  record_batch->FromStructArray(struct_result);
}

arrow::Result<std::shared_ptr<arrow::Table>> GetTable() {
  auto null_long = std::numeric_limits<int64_t>::quiet_NaN();
  ARROW_ASSIGN_OR_RAISE(auto int64_array, GetArrayDataSample<arrow::Int64Type>(
                                              {1, 2, null_long, 3, null_long, 4, 5, 6, 7, 8}));
  arrow::BooleanBuilder boolean_builder;
  std::shared_ptr<arrow::BooleanArray> bool_array;

  std::vector<u_int8_t> bool_values = {false, true,  true,  false, true,
                                       false, false, false, false, true};
  std::vector<bool> is_valid = {false, true, true, true, true, true, false, true, true, true};
  ARROW_RETURN_NOT_OK(boolean_builder.Reserve(10));
  ARROW_RETURN_NOT_OK(boolean_builder.AppendValues(bool_values, is_valid));
  ARROW_RETURN_NOT_OK(boolean_builder.Finish(&bool_array));

  auto record_batch = arrow::RecordBatch::Make(
      arrow::schema({arrow::field("a", arrow::int64()), arrow::field("b", arrow::boolean())}), 10,
      {int64_array, bool_array});
  ARROW_ASSIGN_OR_RAISE(auto table, arrow::Table::FromRecordBatches({record_batch}));
  return table;
}

arrow::Result<std::shared_ptr<arrow::dataset::Dataset>> GetDataset() {
  ARROW_ASSIGN_OR_RAISE(auto table, GetTable());
  auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(table);
  return ds;
}

arrow::Result<cp::ExecBatch> GetExecBatchFromVectors(const arrow::FieldVector& field_vector,
                                                     const arrow::ArrayVector& array_vector) {
  std::shared_ptr<arrow::RecordBatch> record_batch;
  ARROW_ASSIGN_OR_RAISE(auto res_batch, GetSampleRecordBatch(array_vector, field_vector));
  cp::ExecBatch batch{*res_batch};
  return batch;
}

arrow::Result<BatchesWithSchema> MakeBasicBatches() {
  BatchesWithSchema out;
  auto field_vector = {arrow::field("a", arrow::int32()), arrow::field("b", arrow::boolean())};
  ARROW_ASSIGN_OR_RAISE(auto b1_int, GetArrayDataSample<arrow::Int32Type>({0, 4}));
  ARROW_ASSIGN_OR_RAISE(auto b2_int, GetArrayDataSample<arrow::Int32Type>({5, 6, 7}));
  ARROW_ASSIGN_OR_RAISE(auto b3_int, GetArrayDataSample<arrow::Int32Type>({8, 9, 10}));

  ARROW_ASSIGN_OR_RAISE(auto b1_bool, GetArrayDataSample<arrow::BooleanType>({false, true}));
  ARROW_ASSIGN_OR_RAISE(auto b2_bool, GetArrayDataSample<arrow::BooleanType>({true, false, true}));
  ARROW_ASSIGN_OR_RAISE(auto b3_bool, GetArrayDataSample<arrow::BooleanType>({false, true, false}));

  ARROW_ASSIGN_OR_RAISE(auto b1, GetExecBatchFromVectors(field_vector, {b1_int, b1_bool}));
  ARROW_ASSIGN_OR_RAISE(auto b2, GetExecBatchFromVectors(field_vector, {b2_int, b2_bool}));
  ARROW_ASSIGN_OR_RAISE(auto b3, GetExecBatchFromVectors(field_vector, {b3_int, b3_bool}));

  out.batches = {b1, b2, b3};
  out.schema = arrow::schema(field_vector);
  return out;
}

arrow::Result<BatchesWithSchema> MakeSortTestBasicBatches() {
  BatchesWithSchema out;
  auto field = arrow::field("a", arrow::int32());
  ARROW_ASSIGN_OR_RAISE(auto b1_int, GetArrayDataSample<arrow::Int32Type>({1, 3, 0, 2}));
  ARROW_ASSIGN_OR_RAISE(auto b2_int, GetArrayDataSample<arrow::Int32Type>({121, 101, 120, 12}));
  ARROW_ASSIGN_OR_RAISE(auto b3_int, GetArrayDataSample<arrow::Int32Type>({10, 110, 210, 121}));
  ARROW_ASSIGN_OR_RAISE(auto b4_int, GetArrayDataSample<arrow::Int32Type>({51, 101, 2, 34}));
  ARROW_ASSIGN_OR_RAISE(auto b5_int, GetArrayDataSample<arrow::Int32Type>({11, 31, 1, 12}));
  ARROW_ASSIGN_OR_RAISE(auto b6_int, GetArrayDataSample<arrow::Int32Type>({12, 101, 120, 101}));
  ARROW_ASSIGN_OR_RAISE(auto b7_int, GetArrayDataSample<arrow::Int32Type>({0, 110, 210, 11}));
  ARROW_ASSIGN_OR_RAISE(auto b8_int, GetArrayDataSample<arrow::Int32Type>({51, 10, 2, 3}));

  ARROW_ASSIGN_OR_RAISE(auto b1, GetExecBatchFromVectors({field}, {b1_int}));
  ARROW_ASSIGN_OR_RAISE(auto b2, GetExecBatchFromVectors({field}, {b2_int}));
  ARROW_ASSIGN_OR_RAISE(auto b3, GetExecBatchFromVectors({field, field}, {b3_int, b8_int}));
  ARROW_ASSIGN_OR_RAISE(auto b4, GetExecBatchFromVectors({field, field, field, field},
                                                         {b4_int, b5_int, b6_int, b7_int}));
  out.batches = {b1, b2, b3, b4};
  out.schema = arrow::schema({field});
  return out;
}

arrow::Result<BatchesWithSchema> MakeGroupableBatches(int multiplicity = 1) {
  BatchesWithSchema out;
  auto fields = {arrow::field("i32", arrow::int32()), arrow::field("str", arrow::utf8())};
  ARROW_ASSIGN_OR_RAISE(auto b1_int, GetArrayDataSample<arrow::Int32Type>({12, 7, 3}));
  ARROW_ASSIGN_OR_RAISE(auto b2_int, GetArrayDataSample<arrow::Int32Type>({-2, -1, 3}));
  ARROW_ASSIGN_OR_RAISE(auto b3_int, GetArrayDataSample<arrow::Int32Type>({5, 3, -8}));

  ARROW_ASSIGN_OR_RAISE(auto b1_str,
                        GetBinaryArrayDataSample<arrow::StringType>({"alpha", "beta", "alpha"}));
  ARROW_ASSIGN_OR_RAISE(auto b2_str,
                        GetBinaryArrayDataSample<arrow::StringType>({"alpha", "gamma", "alpha"}));
  ARROW_ASSIGN_OR_RAISE(auto b3_str,
                        GetBinaryArrayDataSample<arrow::StringType>({"gamma", "beta", "alpha"}));

  ARROW_ASSIGN_OR_RAISE(auto b1, GetExecBatchFromVectors(fields, {b1_int, b1_str}));
  ARROW_ASSIGN_OR_RAISE(auto b2, GetExecBatchFromVectors(fields, {b2_int, b2_str}));
  ARROW_ASSIGN_OR_RAISE(auto b3, GetExecBatchFromVectors(fields, {b3_int, b3_str}));

  out.batches = {b1, b2, b3};
  size_t batch_count = out.batches.size();
  for (int repeat = 1; repeat <= multiplicity; ++repeat) {
    for (size_t i = 0; i < batch_count; ++i) {
      out.batches.push_back(out.batches[i]);
    }
  }

  out.schema = arrow::schema(fields);
  return out;
}

arrow::Status ExecutePlayAndCollectAsTable(ac::Declaration plan) {
  std::shared_ptr<arrow::Table> response_table;
  ARROW_ASSIGN_OR_RAISE(response_table, ac::DeclarationToTable(plan));
  std::cout << "PlanAsTableResults: " << response_table->ToString() << std::endl;
  return arrow::Status::OK();
}

// arrow::Status ScanSinkExample() {
//   ARROW_ASSIGN_OR_RAISE(std::shared_ptr<arrow::dataset::Dataset> dataset, GetDataset());
//   auto options = std::make_shared<arrow::dataset::ScanOptions>();
//   options->projection = cp::project({}, {});
//   auto scan_node_options = arrow::dataset::ScanNodeOptions{dataset, options};
//   ac::Declaration scan{"scan", std::move(scan_node_options)};
//   return ExecutePlayAndCollectAsTable(std::move(scan));
// }
//
// arrow::Status SourceSinkExample() {
//   ARROW_ASSIGN_OR_RAISE(auto basic_data, MakeBasicBatches());
//   auto source_node_options = ac::SourceNodeOptions{basic_data.schema, basic_data.Gen()};
//   ac::Declaration source{"source", std::move(source_node_options)};
//   return ExecutePlayAndCollectAsTable(std::move(source));
// }
