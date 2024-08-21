#include <iostream>

void fa() {
    std::string s = "hello world";
    std::cout << s.find("world") << std::endl; // 6. world 字符串的起始索引
    std::cout << s.find_first_of("abcde") << std::endl; // 1. 'abcde' 中任一字符在字符串中第一次出现的位置
    std::cout << s.find_first_not_of("abcde") << std::endl; // 0. 不在 'abcde' 中任一字符在字符串中的第一次出现的置
    std::cout << s.find_last_of("abcde") << std::endl; // 10. 'abcde' 中任一字符在字符串中最后一次出现的位置
    std::cout << s.find_last_not_of("abcde") << std::endl; // 9. 不在 'abcde' 中任一字符在字符串中最后一次出现的位置
    std::cout << s.starts_with("hello") << std::endl;  // 1. true
    std::cout << s.ends_with("world") << std::endl; // 1. true
    std::cout << (std::find_if(s.begin(), s.end(), [](char c) { return c == 'e'; }) - s.begin()) << std::endl; // 1. 使用条件查询
}

int main() {
    fa();
    return 0;
}