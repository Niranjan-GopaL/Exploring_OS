/*Description: program to set (any one) system resource limit using setrlimit system call.
*/
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

int main()
{
    struct rlimit r;
    getrlimit(RLIMIT_CPU, &r);
    printf("CPU Hard Limit : %ld, Soft limit : %ld\n", r.rlim_max, r.rlim_cur);
    r.rlim_cur = 1;
    r.rlim_max = 3;

    setrlimit(RLIMIT_CPU, &r);
    getrlimit(RLIMIT_CPU, &r);
    printf("CPU Hard Limit : %ld, Soft limit : %ld\n", r.rlim_max, r.rlim_cur);
}
