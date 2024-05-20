#include<stdio.h>
#include <unistd.h>

int main(){

    // create pipe
    int fd[2];
    pipe(fd);

    // write to pipe
    write(fd[1],"Hello World\n",13);
    char ans[13]; 

    // read from pipe
    read(fd[0],ans,13);
    
    write(1,ans,13);
}
