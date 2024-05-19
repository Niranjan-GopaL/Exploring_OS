#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;

    int i;
    for (i = 0; i < 3; i++) {
        child_pid = fork();

        if (child_pid == 0) {
            // Child process
            printf("Child %d (PID: %d)\n", i + 1, getpid());
            exit(0);
        } else if (child_pid < 0) {
            // Fork failed
            fprintf(stderr, "Fork failed\n");
            return 1;
        }
    }

    // Parent process waits for a specific child (in this case, the first child)
    int status;
    pid_t terminated_pid = waitpid(child_pid, &status, 0);

    printf("Parent Process (PID: %d) waited for Child %d (PID: %d)\n", getpid(), 1, terminated_pid);

    return 0;
}
