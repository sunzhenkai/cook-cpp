#include "iostream"
#include "vector"
#include "utils/utils.h"

#define FIND_CHAR_BETWEEN(data, start, end, delimiter) \
    std::find(data.begin() + start, data.begin() + end, delimiter) - data.begin()
void ExtractEntities(std::vector<std::string_view> &entity_keys,
                     std::vector<float> &entity_values,
                     const std::string &data,
                     char entity_delimiter,
                     char entity_key_delimiter) {
    for (size_t start = 0, end; start < data.size(); start = end + 1) {
        end = data.find(entity_delimiter, start);
        end = end == std::string::npos ? data.size() : end;

        // [start, end)
        auto kvd = FIND_CHAR_BETWEEN(data, start, end, entity_key_delimiter);
        if (kvd != end) {
            entity_keys.emplace_back(data.data() + start, kvd - start);
            entity_values.emplace_back(std::stof(data.data() + kvd + 1));
        } else {
            entity_keys.emplace_back(data.data() + start, end - start);
            entity_values.emplace_back(1.0f);
        }
    }
}

struct FA {
    std::string_view name;
    std::vector<std::string_view> svs;
    std::vector<float> values;
};

int main() {
    std::string hello = "hello";
    std::vector<FA> fas;
    fas.emplace_back(std::string_view{hello.data(), hello.size()});

    {
        std::vector<std::string_view> sv;
        std::vector<float> sf;
        std::string data = "";
        ExtractEntities(sv, sf, data, '\001', '\003');
        utils::display(sv);
        utils::display(sf);
    }
    std::cout << "---" << std::endl;
    {
        std::vector<std::string_view> sv;
        std::vector<float> sf;
        std::string data = "a";
        ExtractEntities(sv, sf, data, '\001', '\003');
        utils::display(sv);
        utils::display(sf);
    }
    std::cout << "---" << std::endl;
    {
        std::vector<std::string_view> sv;
        std::vector<float> sf;
        std::string data = "a\0031.1";
        ExtractEntities(sv, sf, data, '\001', '\003');
        utils::display(sv);
        utils::display(sf);
    }
    std::cout << "---" << std::endl;
    {
        std::vector<std::string_view> sv;
        std::vector<float> sf;
        std::string data = "a\0031.0\001b\0032.2";
        ExtractEntities(sv, sf, data, '\001', '\003');
        utils::display(sv);
        utils::display(sf);
    }
    std::cout << "---" << std::endl;
    {
        std::vector<std::string_view> sv;
        std::vector<float> sf;
        std::string data = "a\0031.0\001b\0032.2\001c\001d\001e\0033.3";
        ExtractEntities(sv, sf, data, '\001', '\003');
        utils::display(sv);
        utils::display(sf);
    }
    return 0;
}