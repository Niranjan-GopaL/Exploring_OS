/*Description: program to print the system resource limits using getrlimit system call.
*/
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
int main()
{
    struct rlimit rlimit;

    int lim = getrlimit(RLIMIT_AS, &rlimit);
    printf("AS Hard Limit : %ld, Soft limit : %ld\n", rlimit.rlim_max, rlimit.rlim_cur);

    lim = getrlimit(RLIMIT_CORE, &rlimit);
    printf("CORE Hard Limit : %ld, Soft limit : %ld\n", rlimit.rlim_max, rlimit.rlim_cur);

    lim = getrlimit(RLIMIT_CPU, &rlimit);
    printf("CPU Hard Limit : %ld, Soft limit : %ld\n", rlimit.rlim_max, rlimit.rlim_cur);

    lim = getrlimit(RLIMIT_FSIZE, &rlimit);
    printf("FSIZE Hard Limit : %ld, Soft limit : %ld\n", rlimit.rlim_max, rlimit.rlim_cur);
    return 0;
}
