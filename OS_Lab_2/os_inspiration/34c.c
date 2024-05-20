#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd[2];
    pipe(fd);

    if (fork() > 0) {
        // Parent process
        close(fd[0]);  // Close read end
        close(1);      // Close stdout
        fcntl(fd[1], F_DUPFD, 1);  // Duplicate write end to stdout
        close(fd[1]);  // Close original write end
        execlp("ls", "ls", "-l", NULL);
    } else {
        // Child process
        close(fd[1]);  // Close write end
        close(0);      // Close stdin
        fcntl(fd[0], F_DUPFD, 0);  // Duplicate read end to stdin
        close(fd[0]);  // Close original read end
        execlp("wc", "wc", NULL);
    }

    return 0;
}
