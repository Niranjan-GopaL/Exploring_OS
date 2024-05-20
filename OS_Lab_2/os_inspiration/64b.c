#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

int main()
{
    int pid;
    printf("Enter process id which you want to send SIGSTOP signal:\n");
    scanf("%d", &pid);
    if (!kill(pid, SIGSTOP))
        printf("SIGSTOP sent to process with pid %d\n", pid);
    else if (errno == EPERM)
        printf("Operation not permitted\n");
    else
        printf("%d doesn't exist\n", pid);
    return 0;
}