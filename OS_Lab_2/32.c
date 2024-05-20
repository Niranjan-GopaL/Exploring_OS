#include<stdio.h>
#include <unistd.h>

int main(){
    int fd[2]; pipe(fd);
    int id = fork();

    // CHILD proc
    if(id==0){
        close(fd[1]); 
        char buff[13];
        read(fd[0],buff,13); 
        printf("%s",buff);

    }
    // PARENT proc
    else{
        close(fd[0]);
        write(fd[1],"Hello World\n",13);
    }
    
    return 0 ;
}
