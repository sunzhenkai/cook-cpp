#include <iostream>
using namespace std;

#pragma pack(push)
struct A {
    char a;
    double b;
};
#pragma pack(1)
struct B {
    char a;
    double b;
};
#pragma pack(4)
struct C {
    char a;
    double b;
};
#pragma pack(8)
struct D {
    char a;
    double b;
};
#pragma pack(16)
struct E{
    char a;
    double b;
};
#pragma pack(pop)

int main() {
    cout << sizeof(char) << " " << sizeof(double) << std::endl;
    cout << sizeof(A) << " " << sizeof(B) << " " << sizeof(C) << " " << sizeof(D) << " " << sizeof(E) << endl;
    return 0;
}
