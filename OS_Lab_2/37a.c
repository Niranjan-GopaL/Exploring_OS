#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    // Open FIFO for writing only
    int fd = open("fifo",O_WRONLY);

    char mssg[20] = "Hello how are you\n";

    // Write message to FIFO
    write(fd,mssg,20);
    return 0 ;
}
