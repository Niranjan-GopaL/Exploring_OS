#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> // Include this header for perror()

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];   
    ssize_t bytes_read;

    // Read input from stdin
    while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
        // Write input to stdout
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    return 0;
}

