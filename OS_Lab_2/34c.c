/*Description:
program to execute ls -l | wc using fcntl
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
#include<fcntl.h>

int main(){
    int fd[2];
    pipe(fd);
    int pid = fork();
    if(pid==0){
        close(fd[0]);
        close(1);
        fd[1] = fcntl(fd[1],F_DUPFD);
        execlp("/bin/ls","bin/ls","-l",(char *) NULL);
        close(fd[1]);
        return 0;
    }
    else{
        
        close(fd[1]);
        close(0);
        fd[0] = fcntl(fd[0],F_DUPFD); 
        execlp("wc","wc",(char*)NULL);
        close(fd[0]);


    }
    return 0 ; 


    
    
}

