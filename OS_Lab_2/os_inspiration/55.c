#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
    struct rlimit rlim;

    if (getrlimit(RLIMIT_STACK, &rlim) == -1) {
        perror("Error retrieving resource limits");
        exit(EXIT_FAILURE);
    }

    printf("Soft limit: %llu    Hard limit: %llu\n", rlim.rlim_cur, rlim.rlim_max);

    rlim.rlim_cur += 4; // Increase soft limit by 4 bytes

    printf("Changing soft limit...\n");
    if (setrlimit(RLIMIT_STACK, &rlim) == -1) {
        perror("Error changing resource limit");
        exit(EXIT_FAILURE);
    }

    printf("Changed...\n");

    if (getrlimit(RLIMIT_STACK, &rlim) == -1) {
        perror("Error retrieving resource limits");
        exit(EXIT_FAILURE);
    }

    printf("Soft limit: %llu    Hard limit: %llu\n", rlim.rlim_cur, rlim.rlim_max);

    return 0;
}
