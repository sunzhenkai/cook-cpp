#include "iostream"
#include "unordered_map"
#include "vector"
#include "cstring"
#include "tuple"

struct ModelServiceResponse {
    int status; // 0: 正常
    // 打分结果分为三级, 第一级: 打分记录, 第二级: 多任务, 第三级: 多头
    std::vector<std::vector<std::vector<float> > > scores;
    std::string model_name;
    std::string model_version;
    std::string debug_info;
};

class ModelServiceClient {
public:
    using RFM = std::unordered_map<std::string, std::string>; // Raw Feature Map
    virtual ModelServiceResponse
    Predict(RFM *l1, const std::vector<RFM *> &l2, const std::vector<std::vector<RFM *>> &l3) = 0;
};

void t() {
    std::string s = "abd\t65af745c";
    std::vector<std::string> values;
    std::vector<float> weights;
    auto extract = [&](const char *entity) {
        const char *c = strchr(entity, '\003');
        if (c == nullptr || *c == '\0') {
            values.emplace_back(entity);
            weights.emplace_back(1.0);
        } else {
            values.emplace_back(entity, c);
            weights.emplace_back(std::stof(c + 1));
        }
    };
    extract(s.c_str());
    std::cout << values.front() << std::endl;
}

class SliceIterator {
public:
    SliceIterator(uint64_t total, uint64_t min_len, uint64_t max_slices) :
            total_(total), min_len_(min_len), max_slices_(max_slices) {
        if (total < min_len_) {
            slices_ = 1;
        } else {
            uint64_t intv = total / max_slices;
            if (intv > min_len) {
                slices_ = total / intv;
            } else {
                slices_ = total / min_len;
                if ((total % min_len) / (double) min_len > 0.5) {
                    slices_ += 1;
                }
            }
        }
        interval_ = total_ / slices_;
    }

    std::tuple<uint64_t, uint64_t, bool> Next() {
        if (cur_ >= slices_) {
            return {0, 0, false};
        }

        uint64_t begin = cur_ * interval_;
        uint64_t end = (cur_ + 1) * interval_;
        if (cur_ == slices_ - 1) {
            end = total_;
        }
        ++cur_;
        return {begin, end, true};
    }

private:
    uint64_t total_;
    uint64_t min_len_;
    uint64_t max_slices_;
    uint64_t slices_ = 0;
    uint64_t cur_ = 0;
    uint64_t interval_ = 0;
};

void fa() {
    SliceIterator iter(10, 3, 3);
    while (true) {
        auto next = iter.Next();
        if (!std::get < 2 > (next)) break;
        std::cout << std::get < 0 > (next) << " - " << std::get < 1 > (next) << std::endl;
    }
}

using RawFeatureMap = std::unordered_map<std::string, std::string>;
struct RawFeatureMapBundle {
    // 保存 level 1 级别的特征, 包括 request、user、supply 侧
    RawFeatureMap l1;
    // 保存 level 2 级别的特征, demand 侧单子相关特征
    // NOTE: key=offer_id
    std::unordered_map<std::string, std::vector<RawFeatureMap>> l2;
    // 保存 level 3 级别的特征, demand 侧创意相关特征
    // NOTE: key=demand_creative_id
    std::unordered_map<std::string, std::vector<RawFeatureMap>> l3;
};

void StringSplit(const std::string &in, const char &c, std::vector<std::string_view> &ret) {
    ret.clear();
    for (size_t i = 0, j = 0; j <= in.size(); i = ++j) {
        while (j < in.size() && in[j] != c)
            ++j;
        ret.emplace_back(std::string_view(in.data() + i, j - i));
    }
}

void fb() {
    std::string s = "1#1.1#2.1";
    std::vector<std::string_view> svs;
    StringSplit(s, '#', svs);
    for (auto v: svs) {
        std::cout << v << std::endl;
    }
}

void fc() {
    std::vector<std::string> vs {"1", "2", "3"};
    std::unordered_map<std::string, std::string> m;
}

int main() {
//    fb();
    //    std::unordered_map<std::string, std::string> ms;
    //    t();

    //    std::vector<std::string> values;
    //    std::string value = "abcd";
    //    auto entity = value.c_str();
    //    auto c = strchr(entity, 'c');
    //    for (auto s = entity; s != c; ++s) {
    //        std::cout << "> " << *s << std::endl;
    //    }
    //    std::cout << (c - entity) << " " << std::string(entity, 2) << std::endl;
    //    values.emplace_back(entity, c);
    //    values.emplace_back(entity, (size_t)(c - entity));
    //    std::cout << values.front() << std::endl;
    return 0;
}