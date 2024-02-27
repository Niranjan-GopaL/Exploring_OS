#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // execl
    execl("/bin/ls", "ls", "-Rl", NULL);

    // execlp
    execlp("ls", "ls", "-Rl", NULL);

    // execle
    char *envp[] = {NULL};
    execle("/bin/ls", "ls", "-Rl", NULL, envp);

    // execv
    char *args[] = {"/bin/ls", "ls", "-Rl", NULL};
    execv(args[0], args);

    // execvp
    execvp("ls", args);

    // If any of the exec calls fail
    perror("exec");
    return 1;
}
