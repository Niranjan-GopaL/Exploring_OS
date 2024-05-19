/*Description:
program to send some data from parent to the child process
*/
#include<stdio.h>
#include <unistd.h>

int main(){
    int fd[2];
    pipe(fd);
    int id = fork();
    if(id==0){
        
        close(fd[1]);
        char buff[13];
        read(fd[0],buff,13);
        printf("%s",buff);

    }
    else{
        close(fd[0]);
        write(fd[1],"Hello World\n",13);

    }
    return 0 ;
}
