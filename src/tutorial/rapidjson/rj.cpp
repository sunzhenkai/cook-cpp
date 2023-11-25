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

    // Value
    rapidjson::Value v1(rapidjson::kArrayType);
    rapidjson::Value v2(rapidjson::kStringType);
    rapidjson::Value v3("string_value");
    rapidjson::Value v4(1);
    rapidjson::Value v5(1.1);
    std::cout << v4.GetType() << std::endl; // number type
    std::cout << v5.GetType() << std::endl; // number type
    return 0;
}