#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    mkfifo("myfifo", 0777);
    char buf[100];
    printf("Enter your message: \n");
    scanf(" %[^\n]", buf); 
    int fd = open("myfifo", O_WRONLY);
    if (fd == -1) {
        perror("Failed to open FIFO");
        exit(EXIT_FAILURE);
    }
    if (write(fd, buf, sizeof(buf)) == -1) {
        perror("Failed to write to FIFO");
        exit(EXIT_FAILURE);
    }
    close(fd);
    return 0;
}
