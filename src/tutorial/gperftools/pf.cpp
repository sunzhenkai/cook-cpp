#include <csignal>
#include "iostream"
#include "gperftools/heap-profiler.h"
#include "gperftools/profiler.h"

void ProcessProfiler(int signum) {
    static bool start = false;
    if (signum == SIGUSR1) {
        if (!start) {
            HeapProfilerStart("heap-profiler");
            ProfilerStart("cpu-profiler.prof");
            std::cout << "ProfilerStart" << std::endl;
            start = true;
        } else {
            HeapProfilerDump("done");
            ProfilerFlush();
            std::cout << "ProfilerFlush" << std::endl;
        }
    } else if (signum == SIGUSR2) {
        ProfilerStop();
        HeapProfilerStop();
        std::cout << "ProfilerStop" << std::endl;
    }
}

int main() {
    signal(SIGUSR1, ProcessProfiler);
    signal(SIGUSR2, ProcessProfiler);
    return 0;
}