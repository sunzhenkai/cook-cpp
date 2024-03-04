#include "iostream"
#include "unordered_map"
#include "basic/sample_structs.h"

void ta() {
    std::unordered_map<std::string, Animal> am;
    am.emplace("dog", Animal());
    std::cout << "---" << std::endl;
    for (auto &[k, v]: am) { // no construction
        std::cout << k << std::endl;
    }
}

int main() {
    ta();
    return 0;
}