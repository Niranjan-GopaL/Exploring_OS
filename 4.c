#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "example.txt";

    // Attempt to open the existing file in read-write mode
    int fd = open(filename, O_RDWR);

    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    } else {
        printf("File opened successfully in read-write mode with descriptor: %d\n", fd);
    }

    // Close the file descriptor
    close(fd);

    // Attempt to open the existing file with O_EXCL flag (exclusive creation)
    int fd_excl = open(filename, O_RDWR | O_EXCL);

    if (fd_excl == -1) {
        perror("Error opening file with O_EXCL flag");
        exit(EXIT_FAILURE);
    } else {
        printf("File opened successfully with O_EXCL flag with descriptor: %d\n", fd_excl);
    }

    // Close the file descriptor
    close(fd_excl);

    return 0;
}

