/*Description:
program to send and receive data from parent to child vice versa using two way
communication
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
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);

    int id = fork();
    //child says hello parent
    //parent says hello child 
    if(id==0){
        //fd1 reader fd2 writer
        close(fd1[1]);
        char readbuff[20];
        read(fd1[0],readbuff,13);
        printf("%s",readbuff);
        close(fd2[0]);
        write(fd2[1],"Hello parent\n",14);
        return 0 ; 



    }
    else{
        //fd1 writer , fd2 reader
        
        close(fd1[0]);
        write(fd1[1],"Hello Child\n",13);
        //Need to wait for child to finish writing only then
        //read 
        wait(NULL);

        close(fd2[1]);
        char rbuff[20];
        read(fd2[0],rbuff,14);
        printf("%s",rbuff);
        
        
        return 0 ; 
    }
    return 0 ;
}
