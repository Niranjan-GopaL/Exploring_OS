#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

int main() {
    fd_set read_fds;
    struct timeval timeout;
    int ready;

    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);

    // Set the timeout to 10 seconds
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input from STDIN for 10 seconds...\n");

    ready = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &timeout);

    if (ready == -1) {
        perror("select");
        return 1;
    } else if (ready == 0) {
        printf("Timeout occurred, no data available.\n");
    } else {
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            printf("Data available on STDIN. Reading input...\n");

            // Read and process the input
            char buffer[1024];
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                printf("Input received: %s", buffer);
            } else {
                printf("Error reading input.\n");
            }
        } else {
            printf("Unknown file descriptor ready.\n");
        }
    }

    return 0;
}

