#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    int fd[2];
    pipe(fd);
    int pid = fork();
    
    if (pid == 0) {
        // Child process
        close(fd[0]); // Close unused read end
        close(1); // Close stdout

        // Duplicate fd[1] to stdout using fcntl
        fcntl(fd[1], F_DUPFD, 1);

        // Execute ls -l
        execlp("ls", "ls", "-l", (char *)NULL);
        close(fd[1]); // Close write end of pipe (not strictly needed after exec)
        return 0;
    } else {
        // Parent process
        close(fd[1]); // Close unused write end
        close(0); // Close stdin

        // Duplicate fd[0] to stdin using fcntl
        fcntl(fd[0], F_DUPFD, 0);

        // Execute wc
        execlp("wc", "wc", (char *)NULL);
        close(fd[0]); // Close read end of pipe (not strictly needed after exec)
    }
    
    return 0;
}
