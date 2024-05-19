#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int choice;
    printf("Enter an integer from 1 to 5: ");
    scanf("%d", &choice);

    char *envp[] = {"-a",NULL}; 
    char *args[] = {"/bin/ls", "-Rl", NULL};

    switch (choice) {
        case 1: execl("/bin/ls", "ls", "-Rl", NULL); break;
        case 2: execlp("ls", "ls", "-Rl", NULL); break;
        case 3: execle("/bin/ls", "ls", "-Rl",NULL, envp); break;
        case 4: execv(args[0], args); break;
        case 5: execvp("ls", args); break;
        default: printf("Invalid input. Please enter an integer from 1 to 5.\n"); break;
    }

    
    // If any of the exec calls fail
    perror("exec");
    return 1;
}
