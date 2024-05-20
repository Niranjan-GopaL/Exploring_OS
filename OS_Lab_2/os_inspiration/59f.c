#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

void my_sig_handler(int sig)
{
    printf("Inside handler SIGVTALRM:%d\n", sig);
    printf("1 second over(virtual time when process is executing)..\n");
}

/*This is very similar to SIGALRM, but while SIGALRM is sent after a
certain amount of real time has passed, SIGVTALRM is sent after a certain
amount of time has been spent running the process*/
int main()
{
    struct itimerval it_val;
    signal(SIGVTALRM, my_sig_handler);

    it_val.it_value.tv_sec = 1;
    it_val.it_value.tv_usec = 0;
    it_val.it_interval = it_val.it_value; //For generating after every interval of 2 secs
    int ret = setitimer(ITIMER_VIRTUAL, &it_val, NULL);
    if (ret == -1)
    {
        perror("Error calling setitimer()\n");
        exit(0);
    }
    for (int i = 1; i <= 5; i++)
    {
        printf("Main %d\n", i);
        int sum = 0;
        //1e9 computations take 1 sec time
        for (int i = 0; i < 100000; i++)
        {
            for (int j = 0; j < 10000; j++)
                sum += i;
        }
    }
    return 0;
}
