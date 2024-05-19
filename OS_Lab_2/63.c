/*Description:program to create an orphan process. Use kill system call to send SIGKILL signal to
the parent process from the child process.
*/
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void sig_handler(int signo)
{
    if (signo == SIGKILL){
        printf("CAPTURED SIGKILL\n");
    }
}

int main(){
    if(!fork()){
        printf("in child process...sending kill signal \n"); 
        kill(getppid(),SIGKILL);  // Sending kill signal to Parent. //orphan 
    }
    else{
        sleep(5);
        printf("in parent process\n");
        if (signal(SIGKILL, sig_handler) == SIG_ERR)
            printf("can't catch SIGKILL\n");
    }
    return 0;
}
