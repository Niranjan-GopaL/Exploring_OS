#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
     // Open FIFO for for reading and writing, create if not exists
    int fd = open("fifo",O_RDWR|O_CREAT);
    
    char strbuffer[100];

    // read from file and STORE in the strbuffer
    read(fd,strbuffer,100);
    printf("%s\n",strbuffer);
}
