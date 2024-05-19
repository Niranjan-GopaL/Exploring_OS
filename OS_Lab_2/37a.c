/*Description:
two programs so that both can communicate by FIFO -Use one way communication.
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd = open("fifo",O_RDWR|O_CREAT);
    char mssg[100];
    read(fd,mssg,100);
    printf("%s",mssg);
    
}
