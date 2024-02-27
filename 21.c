#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    // Open a file
    int fileDescriptor = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    pid_t pid = fork();

    // Child process
    if (pid == 0) 
        dprintf(fileDescriptor, "Child Process (PID: %d)\n", getpid());
    
    // Parent process
    else if (pid > 0) {
        dprintf(fileDescriptor, "Parent Process (PID: %d)\n", getpid());

        // Wait for the child process to finish writing
        wait(NULL);
    } 
    
    else {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    // Close the file
    close(fileDescriptor);

    return 0;
}
