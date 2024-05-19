/*Description:
program to execute ls -l | wc using dup
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    int fd[2];
    pipe(fd);
    int pid = fork();
    if(pid==0){
        close(fd[0]);
        close(1);
        dup(fd[1]);
        execlp("ls","ls","-l",(char*)NULL);
        close(fd[1]);
        return 0;
    }
    else{
        
        close(fd[1]);
        close(0);
        dup(fd[0]); 
        execlp("wc","wc",(char*)NULL);
        close(fd[0]);

    }
    return 0 ; 


    
    
}
