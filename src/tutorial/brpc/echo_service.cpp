#include "iostream"
#include "gflags/gflags.h"
#include "brpc/server.h"
#include "spdlog/spdlog.h"
#include "echo.pb.h"

DEFINE_int32(port, 8000, "TCP Port of this server");

namespace example {
    class EchoServiceImpl : public EchoService {
    public:
        EchoServiceImpl() = default;
        ~EchoServiceImpl() override = default;
        void Echo(google::protobuf::RpcController *cntl_base,
                  const EchoRequest *request,
                  EchoResponse *response,
                  google::protobuf::Closure *done) override {
            // 以 RAII 的方式调用 done->Run()
            brpc::ClosureGuard done_guard(done);
            brpc::Controller *cntl = static_cast<brpc::Controller *>(cntl_base);
            spdlog::info("Received response from {} to {}: {} latency={}",
                         endpoint2str(cntl->local_side()).c_str(),
                         endpoint2str(cntl->remote_side()).c_str(),
                         request->message(), cntl->latency_us());
            response->set_message(request->message());
        }
    };
}

int main(int argc, char **argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    // 通常只需要定义一个 server
    // 可以注册多个 service
    brpc::Server server;
    example::EchoServiceImpl service_impl;
    if (server.AddService(&service_impl, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        spdlog::error("Fail to add service");
        return 1;
    }

    butil::EndPoint ep = butil::EndPoint(butil::IP_ANY, FLAGS_port);
    brpc::ServerOptions options;
    if (server.Start(ep, &options) != 0) {
        spdlog::error("Start server failed.");
        return 1;
    }
    server.RunUntilAskedToQuit();
    return 0;
}