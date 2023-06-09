#include "basic/sample_structs.h"

Animal GetAnimal() {
    Animal a;
//    a.value = 1;
    return a;
}

void ReceiveAnimalA(Animal &&a) {
    std::cout << "05 --- 1" << std::endl;
    auto b = std::move(a);
}

void ReceiveAnimalB(Animal a) {}

int main() {
    {
        Animal b1;
        //    b1.value = 1;
        Animal b2;
        //    b2.value = 2;

        std::cout << &b1 << " - " << &b2 << std::endl;
//        std::swap(b1, b2);
        //    std::cout << &b1 << " - " << &b2 << std::endl;
    }
    {
        std::cout << "01 ---" << std::endl;
        Animal a1;
        Animal a2 = std::move(a1);
    }
    {
        std::cout << "03 ---" << std::endl;
        Animal a3 = GetAnimal();
//        std::cout << "animal.value=" << a3.value << std::endl;
    }
    {
        std::cout << "04 ---" << std::endl;
        Animal a3 = std::move(GetAnimal());
    }
    {
        std::cout << "04.1 ---" << std::endl;
        Animal a3 = std::forward<Animal>(GetAnimal());
    }
    {
        std::cout << "05 ---" << std::endl;
        Animal a4;
        ReceiveAnimalA(std::move(a4));
        std::cout << "05 --- 2" << std::endl;
    }
    {
        std::cout << "06 ---" << std::endl;
        Animal a6;
        ReceiveAnimalB(std::move(a6));
    }
    {
        std::cout << "06 ---" << std::endl;
        ReceiveAnimalB({});
    }
    std::cout << "end" << std::endl;
    return 0;
}