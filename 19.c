#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define CHILD_SLEEP 5
#define PARENT_SLEEP 2



void display_process_status() {
    printf("current_process_id: %d\n", getpid());
    printf("current_process_status:\n");
    system("ps -o pid,state,comm");
}



int main() {
    pid_t child_pid;
    
    child_pid = fork();
    
    if (child_pid < 0) {
        perror("Forking Failed...\nProgram Terminated...\n");
        return 1;
    } else if (child_pid == 0) {
        // Child process gets here
        printf("Executing child process...\n");
        display_process_status();
        
        // Simulate sleeping state in child process
        sleep(CHILD_SLEEP);
        
        printf("Child process wakes up...\n");
        display_process_status();
    } else {
        // Parent process gets here
        printf("Executing parent process...\n");
        display_process_status();
        
        // Allow time for the child to enter the sleeping state
        sleep(PARENT_SLEEP);
        
        // Pause the child process
        kill(child_pid, SIGSTOP);
        printf("Child process paused...\n");
        display_process_status();
        
        // Resume the child process
        kill(child_pid, SIGCONT);
        printf("Child process resumes...\n");
        display_process_status();
        
        // Wait for the child process to finish
        wait(NULL);
    }
    
    return 0;
}
