#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_PATH "fifo_question_a"
#define MSG_SIZE 15

int main() {
    int fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) { perror("open"); exit(EXIT_FAILURE); }

    char msg_read[MSG_SIZE];
    while (1) {

        if (read(fd, msg_read, MSG_SIZE) == -1) { perror("read"); close(fd); exit(EXIT_FAILURE); }
        printf("Received message: %s\n", msg_read);

    }

    close(fd);
    return 0;
}
