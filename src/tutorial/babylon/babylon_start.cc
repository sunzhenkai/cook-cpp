#include "babylon_start.h"

#include <babylon/anyflow/vertex.h>

#include <memory>

#include "babylon/anyflow/builder.h"

void RunStartupGraph() {
  // 1. 创建 Graph Builder
  babylon::anyflow::GraphBuilder builder;
  // 创建图节点
  {
    auto &v = builder.add_vertex([]() { return std::make_unique<PlusProcessor>(); });
    // x、y 字段分别指定输入数据为 A、B
    v.named_depend("x").to("A");
    v.named_depend("y").to("B");
    // z 字段作为输出数据，指定数据名为 C
    v.named_emit("z").to("C");
    // A、B、C 是 processor 之外的名字
  }
  builder.finish();

  // 2. 创建 Graph 对象
  auto graph = builder.build();

  // 3. 图依赖数据赋值
  // 3.1 找到 graph 数据对象
  auto *a = graph->find_data("A");
  auto *b = graph->find_data("B");
  *(a->emit<int>()) = 1;
  *(b->emit<int>()) = 2;

  // 4. 运行
  auto *c = graph->find_data("c");  // 作为 output 数据
  graph->run(c);
  std::cout << "I: " << *c->value<int>() << std::endl;

  // 5. reset graph
  graph.reset();
  *(a->emit<int>()) = 2;
  *(b->emit<int>()) = 3;
  graph->run(c);
  std::cout << "I: " << *c->value<int>() << std::endl;
}
