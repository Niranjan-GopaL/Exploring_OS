#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2];
    pipe(fd);

    if (fork() > 0) {
        // Parent process
        close(fd[1]);   // Close write end
        dup2(fd[0], 0); // Make STDIN same as fd[0]
        execlp("wc", "wc", NULL);
    } else {
        // Child process
        close(fd[0]);   // Close read end
        dup2(fd[1], 1); // Make STDOUT same as fd[1]
        execlp("ls", "ls", "-l", NULL);
    }

    return 0;
}
