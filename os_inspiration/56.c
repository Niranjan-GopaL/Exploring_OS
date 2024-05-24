#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

unsigned long long rdtsc() {
    unsigned long long dst;
    __asm__ __volatile__("rdtsc" : "=A"(dst));
    return dst;
}

int main() {
    unsigned long long start, end;

    start = rdtsc();
    for (int i = 0; i < 100; i++) {
        getppid();
    }
    end = rdtsc();

    printf("Time taken to execute 100 getppid() system calls: %llu CPU cycles\n", end - start);

    return 0;
}
