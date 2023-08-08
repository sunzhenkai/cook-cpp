#include "iostream"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

int main() {
    using namespace rapidjson;
    std::string js = R"({"a": 1, "b": "v", "arr": [1, 2, 3]})";

    Document d;
    d.Parse(js.c_str());
    // 遍历 KV
    for (auto iter = d.MemberBegin(); iter != d.MemberEnd(); ++iter) {
        std::cout << "key: " << iter->name.GetString() << std::endl;
    }


    // 遍历数组
    Value &arr = d["arr"];
    std::cout << arr.IsArray() << std::endl;
    for (auto iter = arr.Begin(); iter != arr.End(); ++iter) {
        std::cout << " > " << iter->GetInt() << std::endl;
    }
    std::cout << d.HasParseError() << std::endl;
    return 0;
}