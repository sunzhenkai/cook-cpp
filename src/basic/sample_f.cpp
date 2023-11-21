#include "iostream"
#include "list"
#include "vector"
#include "utils/utils.h"
#include "forward_list"

void test_list() {
    std::vector<int> v = {1, 2, 3};
    std::list<int> l = {1, 2, 3};
    std::list<int> l2(v.begin(), v.end());
    l.insert(l.begin(), 4);
    utils::display(l);
    l.insert(l.begin(), 4, 5);
    utils::display(l);
    l.erase(l.begin());
    utils::display(l);
    l.remove(5);
    utils::display(l);
    l.begin();
    l.end();
    l.front();
    l.back();
    utils::display(l);
    l.assign(3, -1);
    utils::display(l);
}

void test_forward_list() {
    std::forward_list<int> fl;
    std::forward_list<int> fl2 {1, 2, 3};
    std::cout << std::distance(fl2.begin(), fl2.end()) << std::endl;
    std::forward_list<int> fl3(fl2.begin(), fl2.end());

    fl.push_front(0);
    utils::display(fl);
}

int main() {
    test_forward_list();
    return 0;
}