#include<stdio.h>
#include <unistd.h>

int main(){

    // 0 -> read  ; 1 -> write
    int fd[2];
    pipe(fd);

    // write to write-end of pipe
    write(fd[1],"Hello World\n",13);
    char ans[13]; 

    // read from read-end of pipe
    read(fd[0],ans,13);
    
    write(1,ans,13);
}
