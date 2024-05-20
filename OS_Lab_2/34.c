#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) { perror("pipe"); exit(EXIT_FAILURE); }


    pid_t pid = fork();
    if (pid == -1) { perror("fork"); exit(EXIT_FAILURE); }


    // Child process
    if (pid == 0) { 

        close(pipefd[0]); 

        // Redirect stdout to the writing end of the pipe
        dup2(pipefd[1], STDOUT_FILENO); 
        
        // Close the original writing end of the pipe
        close(pipefd[1]); 

        
        execlp("ls", "ls", "-l", NULL); perror("execlp");
        exit(EXIT_FAILURE);
    } 
    
    // Parent process
    else { 
        // Close writing end of the pipe
        close(pipefd[1]); 

        // Redirect stdin to the reading end of the pipe
        dup2(pipefd[0], STDIN_FILENO); 
        
        // Close the original reading end of the pipe
        close(pipefd[0]); 

        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0;
}
