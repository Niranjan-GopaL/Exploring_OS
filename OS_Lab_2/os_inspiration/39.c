#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <string.h>

#define FIFO_NAME "myfifo"

int main() {
    // Create FIFO if it does not exist
    if (mkfifo(FIFO_NAME, 0777) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Open FIFO for reading and writing
    int fd = open(FIFO_NAME, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Enter your message: \n");
    fflush(stdout);

    // Set up file descriptor set for select
    fd_set rfds;
    struct timeval tv;
    tv.tv_sec = 10;  // Set timeout to 10 seconds
    tv.tv_usec = 0;
    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);  // Add stdin to file descriptor set

    // Wait for input from stdin with a timeout of 10 seconds
    int retval = select(STDIN_FILENO + 1, &rfds, NULL, NULL, &tv);
    if (retval == -1) {
        perror("select");
        exit(EXIT_FAILURE);
    } else if (retval == 0) {
        printf("No data within ten seconds.\n");
    } else {
        // Read input from stdin
        char buf[100];
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0'; // Remove trailing newline
        }
        // Write input to FIFO
        if (write(fd, buf, strlen(buf)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        printf("Reading from FIFO: %s\n", buf);

        // Read response from FIFO
        if (read(fd, buf, sizeof(buf)) == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        printf("Response from FIFO: %s\n", buf);
    }
    // Close FIFO
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    // Remove FIFO
    if (unlink(FIFO_NAME) == -1) {
        perror("unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}
