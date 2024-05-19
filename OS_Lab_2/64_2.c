/*Description:program will send the signal (using kill system call)
*/
#include<stdio.h>
#include<signal.h>
#include<unistd.h>


int main(){
    int pid;
    printf("ENTER PID TO SEND KILL SIGNAL: ");
    scanf("%d",&pid);
    printf("Sending kill signal\n");
    kill(pid,SIGSTOP);
    return 0;
}
