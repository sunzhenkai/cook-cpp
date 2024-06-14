#include "iostream"
#include "unordered_map"
#include "basic/sample_structs.h"
#include "utils/utils.h"
#include "memory"
#include "cmath"
#include "algorithm"

void ta() {
    std::unordered_map<std::string, Animal> am;
    am.emplace("dog", Animal());
    std::cout << "---" << std::endl;
    for (auto &[k, v]: am) { // no construction
        std::cout << k << std::endl;
    }
}

void tb() {
    std::exception_ptr ex = std::make_exception_ptr(std::out_of_range("empty result"));
    try {
        std::rethrow_exception(ex);
    } catch (const std::out_of_range &e) {
        std::cout << "out_of_range: " << e.what() << std::endl;
    } catch (...) {
        std::cout << utils::WhatError(ex) << std::endl;
    }
}

void tc() {
    Animal a, b;
    std::cout << "---" << std::endl;
    std::cout << (true ? a : b).value << std::endl;
    std::cout << "---" << std::endl;
}

void td() {
    std::shared_ptr<int> si = std::make_shared<int>();
    auto si2 = si;
    std::cout << si2.use_count() << std::endl;
    std::weak_ptr<int> si3 = si;
    std::cout << si2.use_count() << " - " << si3.use_count() << std::endl;
}

void te() {
    std::shared_ptr<int> pa = std::make_shared<int>(1);
    std::cout << pa.get() << std::endl;
    std::shared_ptr<int> pb = pa;
    pa = nullptr;
    std::cout << pb.get() << std::endl;
    std::cout << pa.get() << std::endl;
}

void tf() {
    int a[9];
    auto j = a; // 此时j 为指针为 int* 类型，而不是 int(*)[9] 类型
    std::cout << typeid(j).name() << " " << sizeof(j) << " " << sizeof(a) << std::endl;
}

void tg() {
    auto r = "6601160d8e989550754ceaax";
    auto s = utils::GetTimestampFromRequestId(r);
    std::cout << s << std::endl;
}

void th() {
    std::shared_ptr<int> i;
    if (i == nullptr) {
        std::cout << "YES" << std::endl;
    }
}

int solve(const std::string &s) {
    if (s.size() <= 1) return s.size();
    std::vector<int> flag(26, -1);
    int result = 0;
    for (int i = 0, j = 0; i < s.size(); ++j) {
        int pre = flag[s[j] - 'a'];
        if (pre > i) {
            result = std::max(result, j - i);
            i = pre + 1;
        }
        flag[s[j] - 'a'] = j;
    }
    return result;
}

struct AnimalB {
    int value = 0;

    // 默认构造函数
    AnimalB(int value) : value(value) {
        std::cout << "[Animal] " << this << " default constructor" << std::endl;
    };
};

void fg() {
    static AnimalB animal(2);
    std::cout << animal.value << std::endl;
    animal.value = 3;
}

void solve(std::string &s) {
    for (int i = 0, j = s.size() - 1; i < j; ++i, --j) {
        std::swap(s[i], s[j]);
    }
}

void solve2(int &result, const std::vector<int> &nums) {
    // 1, 2, 3, 4, 2, 1, -1, 2, 3, 5
    // nums[i,j] = nums[0,j] - nums[0,i]
    // sum_i_j = sum[j] - sum[i]
    // result = max(result, sum_ - min_sum_);
    // sum[i] 前 i 个的和

    // [i, j]
    // sum(i, j) = sum(0, j) - sum[0, i-1], i 在 [0, j) 之间
    // sum_min: sum[0, i-1]
    // sum    : sum[0, j]

//    int sum_ = 0, sum_min = 0;
//    for (int i = 0; i < nums.size(); ++i) {
//        sum_ += nums[i];
//        result = max(result, sum_ - sum_min);
//        sum_min = min(sum_min, sum_);
//    }
//
//    int min_ = nums[0];
//    for (auto i: nums) {
//        min_ = min(i, min_);
//    }
//    if (min_ < 0) {
//        for (int i = 0; i < nums.size(); ++i) {
//            nums[i] -= min_;
//        }
//    }
//
//    int sum_ = 0, sum_min = 0, length = 0, sum_min_index = 0;
//    for (int i = 0; i < nums.size(); ++i) {
//        sum_ += nums[i];
//        if (sum_ - sum_min > result) {
//            result = sum_ - sum_min;
//            length = i - sum_min_index;
//        }
//        if (sum_min > sum_) {
//            sum_min_index = i;
//            sum_min = sum_;
//        }
//    }
//    if (min_ < 0) {
//        result = (-min_) * length;
//    }
//

    // i             0  1
    // nums       - -1  2
    // sum_       0 -1  1
    // result   MIN -1  2
    // min_sum_   0 -1 -2

    //    if (nums.empty()) return;
    //
    //    result = INT_MIN;
    //    int sum_ = nums[0];
    //    int min_sum_ = 0;
    //    for (int i = 1; i < nums.size(); ++i) {
    //        sum_ += nums[i];
    //        result = max(result, sum_ - min_sum_);
    //        min_sum_ = min(min_sum_, sum_);
    //    }


}

/*
 * 一个文件, 有 20 亿个无符号整数, 一行一个数字
 * 其中, 有 1% 的重复
 * 找到重复的数和频次
 * 并输出到文件
 * */

/* 分析
 * 1. 文件大小 7.5G
 * 2. 读取优化. hdd, 一个线程顺序读比较好. ssd, 可以并行度
 * 3. 计算优化.
 * 4. 逻辑实现.
 * */

//void solve3(const std::string &file_name, const std::string &output_file_name) {
//
//    std::unordered_map<uint32_t, uint32_t> num_freq;
//    std::ifstream file(file_name);
//    if (file.is_open()) {
//        std::string line;
//        while (std::getline(file, line)) {
//            num_freq[std::stoul(line)]++;
//        }
//        file.close();
//    } else {
//        std::cerr << "open file failed. file=" << file_name << std::endl;
//    }
//
//    std::ostream output_file_stream;
//    output_file_stream.open(output_file_name);
//    for (auto &[k, v]: num_freq) {
//        if (v > 1) {
//            output_file_stream << k << " " << v << std::endl;
//        }
//    }
//    output_file_stream.close();
//}
//

void fh() {
    float f = 0.0;
    double d = 0.0;
    std::cout << (f == d) << std::endl;
    std::cout << (f == 0.0) << std::endl;
    std::cout << (d == 0.0) << std::endl;
}

// 字符串, 不会有重复的
// 所有字符的组合
// a b c

void
solve_recursive(std::vector<std::string> &result, const std::string &s, std::string &cur, size_t length, size_t index) {
    if (index >= s.size()) {
        result.emplace_back(std::string{cur.data(), cur.data() + length});
        return;
    }
    solve_recursive(result, s, cur, length, index + 1);
    cur[length] = s[index];
    solve_recursive(result, s, cur, length + 1, index + 1);
}

void solve(std::vector<std::string> &result, const std::string &s) {
    std::string cur;
    cur.resize(s.size());
    solve_recursive(result, s, cur, 0, 0);
}

// int 数组, 奇数+偶数, 最长子数组长度, 要求奇偶个数相等
/*
1, 2, 3, 4, 5, 6, 7
1  1  2  2  3  3  4
0  1  1  2  2  3  3

1  0  1  0  1  0  1

奇数 +1, 偶数 -1

sum_1，奇数
sum_2，偶数

 i
cur_min = min(sum_1[i], sum_2[i])
max_p = 2 * min(sum_1[i], sum_2[i]);
sum_1[i] - sum_1[i-cur_min*2] == cur_min && sum_2[i] - sum_2[i-cur_min*2] == cur_min
  更新 result

 for 1 -> cur_min

1 0 0 0 0 0 0 0 1
1 1 1 1 1 1 1 1 2
0 1 2 3 4 5 6 7 7


 * */

void aa() {
    std::string s = "ff";
    std::cout << utils::HexToInt64(s) << " - " << std::stol(s, nullptr, 16) << std::endl;
}

int main() {
    aa();
    return 0;
}
