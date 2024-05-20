#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    char buf[100];
    int fd = open("myfifo", O_RDONLY);
    if (fd == -1) {
        perror("Failed to open FIFO");
        exit(EXIT_FAILURE);
    }
    if (read(fd, buf, sizeof(buf)) == -1) {
        perror("Failed to read from FIFO");
        exit(EXIT_FAILURE);
    }
    printf("Message : %s\n", buf);
    close(fd);
    return 0;
}
