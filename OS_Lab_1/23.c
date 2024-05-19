#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main() {
    pid_t pid = fork();

    // Child process
    if (pid == 0) {
        sleep(5);
        printf("Orphan Process (PID: %d)\n", getpid());

    // Parent process
    } else if (pid > 0) {
        printf("Parent Process (PID: %d)\n", getpid());
        // Parent process terminates, leaving the child as an orphan
    } 
    
    else {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;
}
