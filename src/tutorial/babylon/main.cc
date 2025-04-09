#include <babylon/anyflow/vertex.h>

#include <iostream>
#include <memory>

#include "babylon_start.h"

// int main(int argc, char *argv[]) {
//   RunStartupGraph();
//   return 0;
// }

#define M_STR(e) #e
#define M_M_STR(x) M_STR(x)
#define REQ req

#include "babylon/anyflow/builder.h"

using babylon::anyflow::GraphBuilder;
using babylon::anyflow::GraphProcessor;

// 实现一个简单的算子，做加法，继承函数基类
class PlusProcessorV2 : public GraphProcessor {
  // 实现计算功能
  int process() noexcept override {
    *z.emit() = *x + *y;
    return 0;
  }
  // 定义函数接口，除辅助函数外，主要产生
  // int* x;
  // int* y;
  // OutputData<int> z;
  // 三个对应的成员，其中x和y为输入，会在process调用前准备好
  // z是输出，调用emit函数进行实际的数据发布
  // 接口定义具备一定的反射能力，可以在构图时指定"x"，"y"，"z"这样的字面值来指代
  ANYFLOW_INTERFACE(ANYFLOW_DEPEND_DATA(int, x) ANYFLOW_DEPEND_DATA(int, y) ANYFLOW_EMIT_DATA(int, z))
};

class ErrorTrigger : public GraphProcessor {
  int process() noexcept override {
    std::cout << "run ErrorTrigger" << std::endl << std::flush;
    return 1;
  }
  ANYFLOW_INTERFACE(ANYFLOW_DEPEND_DATA(int, x) ANYFLOW_EMIT_DATA(int, y))
};

int main(int, char**) {
  {
    GraphBuilder builder;
    // 创建图节点
    {
      // 指定节点的Processor构造工厂
      // auto& v = builder.add_vertex([] { return std::make_unique<PlusProcessor>(); });
      auto& v = builder.add_vertex([] { return std::make_unique<PlusProcessor>(); });
      // 为x，y分别指定A，B为输入
      // 为z指定输出到C
      v.named_depend("x").to("A");
      v.named_depend("y").to("B");
      v.named_emit("z").to("C");
      auto& v2 = builder.add_vertex([]() { return std::make_unique<ErrorTrigger>(); });
      v2.named_depend("x").to("A");
      v2.named_emit("y").to("D");
    }
    // 结束构建
    builder.finish();
    // 获得一个可以运行的图实例
    auto graph = builder.build();
    // 找到图数据，用于外部操作
    auto* a = graph->find_data("A");
    auto* b = graph->find_data("B");
    auto* c = graph->find_data("C");
    auto* d = graph->find_data("D");
    // 初始数据赋值
    *(a->emit<int>()) = 1;
    *(b->emit<int>()) = 2;
    // 针对c数据进行求解，会使用A, B的数据为依赖，运行节点来得到C
    auto closer = graph->run(c, d);
    closer.wait();
    if (!closer.error_code()) {
      // 最终应该返回3
      std::cout << "RUN: " << *c->value<int>() << std::endl;
      std::cout << "RUN: " << *d->value<int>() << std::endl;
    } else {
      std::cout << "Run failed. error_code=" << closer.error_code() << std::endl;
    }
  }
  {
    GraphBuilder builder;
    // 创建图节点
    {
      // auto& v = builder.add_vertex([] { return std::make_unique<PlusProcessor>(); });
      auto& v = builder.add_vertex([]() { return std::make_unique<PlusProcessor>(); });
      // x、y 字段分别指定输入数据为 A、B
      v.named_depend("x").to("A");
      v.named_depend("y").to("B");
      // z 字段作为输出数据，指定数据名为 C
      v.named_emit("z").to("C");
      // A、B、C 是 processor 之外的名字
      auto& v2 = builder.add_vertex([]() { return std::make_unique<ErrorTrigger>(); });
      v2.named_depend("x").to("A");
    }
    builder.finish();
  }
  RunStartupGraph();
  // not work
  RunStartupGraphV2();

  std::cout << M_STR(REQ) << std::endl;
  std::cout << M_M_STR(REQ) << std::endl;
  return 0;
}
