#include "pthread.h"
#include <cstdio>

struct Arg {
    int value;
};

void *payload(void *arg) {
    auto v = (Arg *) arg;
    printf("value: %d\n", v->value);
    return nullptr;
}

void c_thread() {
    // 1. init variables
    auto arg = new Arg{2};
    pthread_attr_t attr;
    int exit_status;

    // 2. create thread & run
    pthread_t thread_id;
    pthread_create(&thread_id, &attr, payload, arg);
    pthread_join(thread_id, (void **) &exit_status);

    // 3. clean
    delete arg;
    printf("thread exit status: %d\n", exit_status);
}

int main() {
    c_thread();
    return 0;
}