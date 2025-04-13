#pragma once

#include <absl/log/internal/log_message.h>
#include <arrow/array/array_base.h>
#include <arrow/record_batch.h>
#include <arrow/result.h>
#include <arrow/status.h>
#include <arrow/type_fwd.h>
#include <arrow/type_traits.h>

#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "arrow/api.h"
#include "arrow/compute/api.h"
#include "arrow/dataset/api.h"

#define DECLARE_BUILDER_TYPE using ArrowBuildType = typename arrow::TypeTraits<TYPE>::BuilderType;

namespace cp = arrow::compute;
namespace ac = arrow::acero;

template <typename TYPE, typename = typename std::enable_if<arrow::is_number_type<TYPE>::value |
                                                            arrow::is_boolean_type<TYPE>::value |
                                                            arrow::is_temporal_type<TYPE>::value>>
arrow::Result<std::shared_ptr<arrow::Array>> GetArrayDataSample(
    const std::vector<typename TYPE::c_type>& values) {
  DECLARE_BUILDER_TYPE;
  ArrowBuildType builder;
  ARROW_RETURN_NOT_OK(builder.Reserve(values.size()));
  ARROW_RETURN_NOT_OK(builder.AppendValues(values));
  return builder.Finish();
}

template <typename TYPE>
arrow::Result<std::shared_ptr<arrow::Array>> GetBinaryArrayDataSample(
    const std::vector<std::string>& values) {
  DECLARE_BUILDER_TYPE;
  ArrowBuildType builder;
  ARROW_RETURN_NOT_OK(builder.Reserve(values.size()));
  ARROW_RETURN_NOT_OK(builder.AppendValues(values));
  return builder.Finish();
}

arrow::Result<std::shared_ptr<arrow::RecordBatch>> GetRecordBatchSample(
    const arrow::ArrayVector& array_vector, const arrow::FieldVector& field_vector);

/// \brief Create a sample table
/// The table's contents will be:
/// a,b
/// 1,null
/// 2,true
/// null,true
/// 3,false
/// null,true
/// 4,false
/// 5,null
/// 6,false
/// 7,false
/// 8,true
/// \return The created table
arrow::Result<std::shared_ptr<arrow::Table>> GetTable();
arrow::Result<std::shared_ptr<arrow::dataset::Dataset>> GetDataset();
arrow::Result<cp::ExecBatch> GetExecBatchFromVectors(const arrow::FieldVector& field_vector,
                                                     const arrow::ArrayVector& array_vector);

struct BatchesWithSchema {
  std::vector<cp::ExecBatch> batches;
  std::shared_ptr<arrow::Schema> schema;

  arrow::AsyncGenerator<std::optional<cp::ExecBatch>> Gen() const {
    // 为 Batches 包装 Optional
    auto opt_batches = ::arrow::internal::MapVector(
        [](cp::ExecBatch batch) { return std::make_optional(std::move(batch)); }, batches);
    arrow::AsyncGenerator<std::optional<cp::ExecBatch>> gen;
    gen = arrow::MakeVectorGenerator(std::move(opt_batches));
    return gen;
  }
};

arrow::Result<BatchesWithSchema> MakeBasicBatches();
arrow::Result<BatchesWithSchema> MakeSortTestBasicBatches();
arrow::Result<BatchesWithSchema> MakeGroupableBatches(int multiplicity = 1);
arrow::Status ExecutePlayAndCollectAsTable(ac::Declaration plan);
