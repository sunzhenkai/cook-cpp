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

void RunTask() {
    bthread_usleep(500);
}

TEST(BRPC, BTHREAD) {
    std::vector<bthread_t> ids;
    ids.resize(FLAGS_thread_num);
    for (int i = 0; i < FLAGS_thread_num; ++i) {
        if (bthread_start_background(&ids[i], NULL, RunTask, NULL) != 0) {

        }
    }
}