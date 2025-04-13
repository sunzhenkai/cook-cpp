#include <iostream>
#include <memory>
#include <utility>

#include "arrow_utils.h"
#include "gtest/gtest.h"

namespace ac = arrow::acero;

// Docs: https://arrow.apache.org/docs/cpp/streaming_execution.html
TEST(ArrowAcero, ScanSinkExample) {
  ARROW_ASSIGN_OR_RAISE(std::shared_ptr<arrow::dataset::Dataset> dataset, GetDataset());
  std::cout << "[DS]1> " << dataset->schema()->ToString() << std::endl;

  auto options = std::make_shared<arrow::dataset::ScanOptions>();
  options->projection = cp::project({}, {});

  auto scan_node_options = arrow::dataset::ScanNodeOptions{dataset, options};
  ac::Declaration scan{"scan", std::move(scan_node_options)};
  auto status = ExecutePlayAndCollectAsTable(scan);
  std::cout << "[DS]2> " << status.ToString() << std::endl;
}

// TEST(ArrowAcero, SourceSinkExample) {
//   ARROW_ASSIGN_OR_RAISE(auto basic_data, MakeBasicBatches());
//   auto source_node_options = ac::SourceNodeOptions{basic_data.schema, basic_data.Gen()};
//   ac::Declaration source{"source", std::move(source_node_options)};
//   auto status = ExecutePlayAndCollectAsTable(std::move(source));
//   std::cout << "[SSE]1> " << status.ToString() << std::endl;
// }

TEST(ArrowAcero, TableSourceSinkExample) {
  ARROW_ASSIGN_OR_RAISE(auto table, GetTable());
  arrow::AsyncGenerator<std::optional<arrow::ExecBatch>> sink_gen;
  int max_batch_size = 2;
  auto table_source_options = ac::TableSourceNodeOptions{table, max_batch_size};
  ac::Declaration table_source{"table_source", std::move(table_source_options)};
  auto status = ExecutePlayAndCollectAsTable(std::move(table_source));
  std::cout << "[TSS]1> " << status.ToString() << std::endl;
}

TEST(ArrowAcero, ScanFilterSinkExample) {
  ARROW_ASSIGN_OR_RAISE(auto dataset, GetDataset());
  cp::Expression filter_expr = cp::greater(cp::field_ref("a"), cp::literal(3));
  auto options = std::make_shared<arrow::dataset::ScanOptions>();
  options->filter = filter_expr;
  options->projection = cp::project({}, {});

  arrow::dataset::ScanNodeOptions scan_node_options{dataset, options};

  ac::Declaration scan{"scan", std::move(scan_node_options)};
  ac::Declaration filter{
      "filter", {std::move(scan)}, ac::FilterNodeOptions(std::move(filter_expr))};
  auto status = ExecutePlayAndCollectAsTable(std::move(filter));

  std::cout << "[SFS]1> " << status.ToString() << std::endl;
}

// https://arrow.apache.org/docs/cpp/acero/user_guide.html#project
