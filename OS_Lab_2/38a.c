#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_PATH "fifo_question_a"
#define MSG_SIZE 15

int main() {
    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) { perror("open"); exit(EXIT_FAILURE); }

    char msg_write[MSG_SIZE];

    while (1) {
        printf("Enter message: ");
        fgets(msg_write, MSG_SIZE, stdin);
        // msg_write[strlen(msg_write) - 1] = '\0'; // Remove newline character

        if (write(fd, msg_write, MSG_SIZE) == -1) { perror("write"); close(fd); exit(EXIT_FAILURE); }
        
    }

    close(fd);
    return 0;
}
