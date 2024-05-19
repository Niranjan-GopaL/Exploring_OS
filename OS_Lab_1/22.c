#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main() {
    pid_t pid = fork();

    // Child process
    if (pid == 0) {
        printf("Child Process (PID: %d)\n", getpid());
        // Child process terminates immediately
        exit(0);
    } 
    
    // Parent process
    else if (pid > 0) {
        printf("Parent Process (PID: %d)\n", getpid());
        // Parent process continues execution without waiting for the child
        sleep(10);
    } 
    
    else {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;
}
