#include "iostream"
#include <fstream>
#include "thread"
#include "chrono"
#include "thread"
#include "chrono"

int main() {
    //    std::ofstream f;
    //    f.open("test.log");
    //    for (int i = 0; true; ++i) {
    //        f << i << "\u0004\u0004\u0004\u0005\u0005\u0005\n";
    //        std::this_thread::sleep_for(std::chrono::microseconds(100));
    //    }
    while (true) {
        auto result = std::getenv("NPS_BATCH_SIZE");
        std::cout << result << std::endl;
        std::cout << (result ? "yes" : "no") << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}