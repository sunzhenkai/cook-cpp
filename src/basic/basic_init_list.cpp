#include "iostream"

class SampleClass {
public:
    // 默认构造函数
    SampleClass() {
        std::cout << "Default constructor" << std::endl;
    }

    // 带参数的构造函数
    explicit SampleClass(int value) : data(value) {
        std::cout << "Parameterized constructor" << std::endl;
    }

    // 复制构造函数
    SampleClass(const SampleClass &other) : data(other.data) {
        std::cout << "Copy constructor" << std::endl;
    }

    // 移动构造函数
    SampleClass(SampleClass &&other) noexcept: data(std::move(other.data)) {
        std::cout << "Move constructor" << std::endl;
    }

    // 复制赋值操作符
    SampleClass &operator=(const SampleClass &other) {
        if (this != &other) {
            data = other.data;
        }
        std::cout << "Copy assignment operator" << std::endl;
        return *this;
    }

    // 移动赋值操作符
    SampleClass &operator=(SampleClass &&other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
        }
        std::cout << "Move assignment operator" << std::endl;
        return *this;
    }

    // 析构函数
    ~SampleClass() {
        std::cout << "Destructor" << std::endl;
    }

private:
    int data;
};

int main() {
    return 0;
}