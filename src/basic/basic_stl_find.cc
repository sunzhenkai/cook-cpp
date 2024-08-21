#include <iostream>
#include <vector>

void fa() {
    std::vector<int> v{1, 2, 3, 4, 2, 6};
    std::vector<int> f{3, 4, 2};
    std::cout << (std::find(v.begin(), v.end(), 3) - v.begin()) << std::endl; // 2. 查找元素
    std::cout << (std::find_if(v.begin(), v.end(), [](int v) { return v == 4; }) - v.begin()) << std::endl; // 3. 查找第一个满足条件的元素
    std::cout << (std::find_if_not(v.begin(), v.end(), [](int v) { return v != 3; }) - v.begin()) << std::endl; // 2. 查找第一个不满足条件的元素
    std::cout << (std::find_first_of(v.begin(), v.end(), f.begin(), f.end()) - v.begin()) << std::endl; // 1. 查找目标序列的任一元素位置
    std::cout << (std::find_end(v.begin(), v.end(), f.begin(), f.end()) - v.begin()) << std::endl; // 1. 子序列查找
}

int main() {
    fa();
    return 0;
}