#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void my_sig_handler(int sig)
{
    printf("Inside handler:%d\n", sig);
    printf("2 seconds over..\n");
    alarm(2); //to continuosly set alarm after every 2 seconds
}

/*The alarm() function is used to generate a SIGALRM signal 
after a specified amount of time elapsed. */

int main()
{
    signal(SIGALRM, my_sig_handler);
    alarm(2); //Schedule the first alarm after 2 seconds
    for (int i = 1; i <= 5; i++)
    {
        printf("Main %d\n", i);
        sleep(1);
    }
    return 0;
}
