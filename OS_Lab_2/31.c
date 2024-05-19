/*Description:
program to create a pipe, write to the pipe, read from pipe and display on
the monitor.
*/
#include<stdio.h>
#include <unistd.h>

int main(){
    int fd[2];
    pipe(fd);

    write(fd[1],"Hello World\n",13);
    char ans[13]; 
    read(fd[0],ans,13);
    write(1,ans,13);
    
}
