#include "gtest/gtest.h"
#include "bvar/bvar.h"
#include "bthread/bthread.h"
#include "gflags/gflags.h"

DEFINE_int32(thread_num, 50, "number of threads");

TEST(BRPC, BVAR) {
    // basic bvar
    bvar::Adder<int> count;
    count << 1;
    std::cout << count.get_value() << std::endl;
}

void *RunTask(void *args) {
    bthread_usleep(500);
    return nullptr;
}

TEST(BRPC, BTHREAD) {
    std::vector<bthread_t> ids;
    ids.resize(FLAGS_thread_num);
    std::cout << "create task" << std::endl;
    for (int i = 0; i < FLAGS_thread_num; ++i) {
        if (bthread_start_background(&ids[i], nullptr, RunTask, nullptr) != 0) {
            std::cerr << "failed to create bthread" << std::endl;
        }
    }
    std::cout << "wait done" << std::endl;
    for (auto &i: ids) {
        bthread_join(i, nullptr);
    }
    std::cout << "done" << std::endl;
}