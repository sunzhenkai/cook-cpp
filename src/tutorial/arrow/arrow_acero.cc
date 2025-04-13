#include <iostream>
#include <memory>
#include <utility>

#include "arrow_utils.h"
#include "gtest/gtest.h"

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

TEST(ArrowAcero, SourceSinkExample) {
  ARROW_ASSIGN_OR_RAISE(auto basic_data, MakeBasicBatches());
  auto source_node_options = ac::SourceNodeOptions{basic_data.schema, basic_data.Gen()};
  ac::Declaration source{"source", std::move(source_node_options)};
  auto status = ExecutePlayAndCollectAsTable(std::move(source));
  std::cout << "[SSE]1> " << status.ToString() << std::endl;
}
