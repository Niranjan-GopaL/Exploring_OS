#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(){
    struct timeval t;
    fd_set readfds;

    int fd = open("fifo_question_a",O_RDWR|O_CREAT);

    const int msg_size = 100;
    char msg[msg_size];

    printf("enter a message : ");
    fflush(stdout);

    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    
    t.tv_sec = 10;
    t.tv_usec = 0;

    if(!select(fd+1, &readfds, NULL, NULL, &t)){
        printf("User didn't enter anything!\n");
    }
    else{
        fgets(msg, msg_size, stdin);
        write(fd,msg,msg_size);
    }
    return (0);
}
