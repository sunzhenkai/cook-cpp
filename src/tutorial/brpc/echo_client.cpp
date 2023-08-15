#include "iostream"
#include "gflags/gflags.h"
#include "brpc/channel.h"
#include "echo.pb.h"
#include "spdlog/spdlog.h"

DEFINE_int32(timeout_ms, 100, "RPC timeout in milliseconds");
DEFINE_string(connection_type, "", "Connection type. Available values: single, pooled, short");
DEFINE_string(protocol, "baidu_std", "Protocol type. Defined in src/brpc/options.proto");
DEFINE_string(load_balancer, "", "The algorithm for load balancing");
DEFINE_string(server, "0.0.0.0:8000", "IP Address of server");

int main(int argc, char **argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    // 创建 channel
    // 1. channel 用于和 server 通讯
    // 2. channel 线程安全, 应当被所有线程复用
    brpc::Channel channel;
    // 创建 channel option
    brpc::ChannelOptions options;
    options.protocol = FLAGS_protocol;
    options.timeout_ms = FLAGS_timeout_ms;
    options.connection_type = FLAGS_connection_type;
    if (channel.Init(FLAGS_server.c_str(), FLAGS_load_balancer.c_str(), &options) != 0) {
        std::cerr << "fail to initialize channel" << std::endl;
    }

    // 通常不需要直接使用 channel 来访问远程服务
    // 需要创建爱你一个 Service Stub 来包装 channel
    // stub 也应该被所有线程共用
    example::EchoService_Stub stub(&channel);

    int log_id = 0;
    while (!brpc::IsAskedToQuit()) {
        example::EchoRequest request;
        example::EchoResponse response;
        request.set_message("hello world");

        brpc::Controller cntl;
        cntl.set_log_id(log_id++);
        stub.Echo(&cntl, &request, &response, nullptr);
        if (!cntl.Failed()) {
            spdlog::info("Received request from {} to {}: {} latency={}",
                         endpoint2str(cntl.local_side()).c_str(),
                         endpoint2str(cntl.remote_side()).c_str(),
                         response.message(), cntl.latency_us());
        }
        usleep(1000 * 1000);
    }

    return 0;
}