#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);

    int id = fork();

    if(id == 0){
        // Child process: fd1 reader, fd2 writer
        close(fd1[1]); // Close the write end of fd1
        close(fd2[0]); // Close the read end of fd2

        char readbuff[100];
        read(fd1[0], readbuff, 100);
        printf("[ CHILD ] %s\n", readbuff);

        const char *child_msg = "Child Proc can write here; parent can read from the other end of this buffer.";
        write(fd2[1], child_msg, strlen(child_msg) + 1);

        close(fd1[0]); // Close the read end of fd1
        close(fd2[1]); // Close the write end of fd2
        return 0;

    } else {
        
        // Parent process: fd1 writer, fd2 reader
        close(fd1[0]); // Close the read end of fd1
        close(fd2[1]); // Close the write end of fd2

        const char *parent_msg = "Parent Proc can write here; child can read from the other end of this buffer.";
        write(fd1[1], parent_msg, strlen(parent_msg) + 1);

        // Wait for the child to finish writing
        wait(NULL); 

        char readbuff[100];
        read(fd2[0], readbuff, 100);
        printf("[ PARENT ] %s\n", readbuff);

        close(fd1[1]); // Close the write end of fd1
        close(fd2[0]); // Close the read end of fd2

        return 0;
    }

    return 0;
}
