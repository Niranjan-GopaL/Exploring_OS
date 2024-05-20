#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

int main() {
    int ret = fork();
    if (ret == 0) {
        printf("In child process...sending kill signal\n");
        int ppid = getppid();
        int pid = getpid();
        if (!kill(ppid, SIGKILL))
            printf("SIGKILL sent to parent process with pid %d from the child process with pid: %d\n", ppid, pid);
        else if (errno == EPERM)
            printf("Operation not permitted\n");
        else
            printf("%d doesn't exist\n", ppid);
        sleep(1);
        printf("Orphan process\n");
    } else {
        wait(0);
        printf("Back In parent process\n");
    }
    return 0;
}
