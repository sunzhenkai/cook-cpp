#include "iostream"
#include "jemalloc/jemalloc.h"

int main() {
    je_malloc(0);
    return 0;
}