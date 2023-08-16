#include "iostream"
#include "google/protobuf/util/json_util.h"
#include "package/package_example.pb.h"

int main() {
    package_example::EchoRequest request;
    request.set_message("hello");

    std::string output;
    google::protobuf::util::MessageToJsonString(request, &output);

    std::cout << output << std::endl;
    return 0;
}