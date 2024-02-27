#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Open the file for appending
    int fd = open("file.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Duplicate the file descriptor using dup
    int dup_fd1 = dup(fd);
    if (dup_fd1 == -1) {
        perror("Error duplicating file descriptor");
        close(fd);
        return 1;
    }

    // Duplicate the file descriptor using dup2
    int dup_fd2 = dup2(fd, 3); // Using fd 3 as an example
    if (dup_fd2 == -1) {
        perror("Error duplicating file descriptor");
        close(fd);
        return 1;
    }

    // Append to the file using both descriptors
    if (dprintf(fd, "Content appended using original descriptor\n") < 0) {
        perror("Error appending to file");
        close(fd);
        return 1;
    }
    if (dprintf(dup_fd1, "Content appended using dup descriptor\n") < 0) {
        perror("Error appending to file");
        close(fd);
        return 1;
    }
    if (dprintf(dup_fd2, "Content appended using dup2 descriptor\n") < 0) {
        perror("Error appending to file");
        close(fd);
        return 1;
    }

    // Close all file descriptors
    close(fd);
    close(dup_fd1);
    close(dup_fd2);

    printf("Content appended successfully.\n");
    return 0;
}

