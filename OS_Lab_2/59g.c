#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

void my_sig_handler(int sig)
{
    printf("Inside handler(SIGPROF):%d\n", sig);
    printf("1 second profiling time over..\n");
}
/*A profiling timer that counts both processor time
used by the process, and processor time spent in system calls on
behalf of the process. This timer sends a SIGPROF signal to the process when it expires.
*/
int main()
{
    struct itimerval it_val;
    signal(SIGPROF, my_sig_handler);

    it_val.it_value.tv_sec = 2;
    it_val.it_value.tv_usec = 0;
    it_val.it_interval = it_val.it_value; //For generating after every interval of 2 secs
    int ret = setitimer(ITIMER_PROF, &it_val, NULL);
    if (ret == -1)
    {
        perror("Error calling setitimer()\n");
        exit(0);
    }
    for (int i = 1; i <= 5; i++)
    {
        printf("Main %d\n", i);
        int sum = 0;
        for (int i = 0; i < 100000; i++)
        {
            for (int j = 0; j < 10000; j++)
                sum += i;
        }
    }
    return 0;
}
