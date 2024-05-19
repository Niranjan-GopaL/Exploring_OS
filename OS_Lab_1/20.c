#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main() {
    pid_t pid = fork();

    // child process
    if (pid == 0) 
        printf("Child Process (PID: %d)\n", getpid());

    // parent process
    else if (pid > 0) 
        printf("Parent Process (PID: %d)\n", getpid());

    // maximum limit for concurrent processes reached
    // OR is facing resource constraints
    else {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;
}
