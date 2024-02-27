#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *args[] = {"./2", "name", NULL};

    execvp(args[0], args);

    // execvp returns only if an error occurs
    perror("execvp");
    return 1;
}
