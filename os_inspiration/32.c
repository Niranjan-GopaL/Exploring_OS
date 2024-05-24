#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* Read and write are blocking system calls.*/
int main()
{
    int fd[2];
    pipe(fd);
    int ret = fork();
    if (ret > 0) //parent process
    {
        close(fd[0]);
        printf("Writing to the pipe from the parent proces....\n");
        write(fd[1], "Hello There!", 13);
        wait(0);
    }
    else
    {
        close(fd[1]);
        char buf[80];
        printf("Reading from pipe from the child process...\n");
        read(fd[0], buf, 13);
        printf("%s\n", buf);
    }
    return 0;
}