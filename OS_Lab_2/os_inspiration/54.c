#include <stdio.h>
#include <sys/resource.h>
#include <errno.h>

void print_limit(const char *resource_name, int resource) {
    struct rlimit rlim;
    int ret = getrlimit(resource, &rlim);
    if (ret == -1) {
        perror("getrlimit");
        return;
    }
    printf("%s: Soft limit=%llu, Hard limit=%llu\n", resource_name, rlim.rlim_cur, rlim.rlim_max);
}

int main() {
    print_limit("RLIMIT_CORE", RLIMIT_CORE);
    print_limit("RLIMIT_CPU", RLIMIT_CPU);
    print_limit("RLIMIT_MSGQUEUE", RLIMIT_MSGQUEUE);
    print_limit("RLIMIT_STACK", RLIMIT_STACK);
    return 0;
}
