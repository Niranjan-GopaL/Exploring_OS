#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Create a file named "example.txt" with read and write permissions
    int fd = creat("example.txt", 0644);

    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    printf("File created successfully with descriptor: %d\n", fd);

    close(fd);

    return 0;
}

