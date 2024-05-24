#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void my_sig_handler()
{
    printf("SIGSTOP signal caught\n");
    printf("Exiting...\n");
    exit(0);
}

int main()
{
    printf("Current process id: %d\n", getpid());
    printf("Waiting for SIGSTOP signal\n");
    sleep(20); // Wait for 10 seconds
    if (signal(SIGSTOP, my_sig_handler) == SIG_ERR)
    {
        perror("signal");
        printf("Can't catch the signal\n");
    }
    return 0;
}
