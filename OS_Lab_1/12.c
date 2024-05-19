#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Open a file in read-only mode
    int fd_read = open("file0.txt", O_RDONLY);
    // printf("%d\n",fd_read);
    if (fd_read == -1) {
        perror("Error opening file in read-only mode");
        exit(EXIT_FAILURE);
    }

    // Open a file in write-only mode
    int fd_write = open("file1.txt", O_WRONLY);
    // printf("%d\n",fd_write);
    if (fd_write == -1) { perror("Error opening file in write-only mode"); exit(EXIT_FAILURE); }

    // Open a file in read-write mode
    int fd_read_write = open("file2.txt", O_RDWR);
    // printf("%d\n",fd_read_write);
    if (fd_read_write == -1) {
        perror("Error opening file in read-write mode");
        exit(EXIT_FAILURE);
    }

    // Check and print the mode for each file descriptor
    int flags_read = fcntl(fd_read, F_GETFL);
    int flags_write = fcntl(fd_write, F_GETFL);
    int flags_read_write = fcntl(fd_read_write, F_GETFL);

    printf("%d\n",O_RDONLY);
    printf("%d\n",flags_read);
    printf("%d\n",flags_write);

    if (flags_read & O_RDONLY) printf("file0.txt is opened in read-only mode.\n");
    else printf("file0.txt is not opened in read-only mode.\n");

    if (flags_write & O_WRONLY) printf("file1.txt is opened in write-only mode.\n");
    else printf("file1.txt is not opened in write-only mode.\n");

    if ((flags_read_write & O_RDWR) == O_RDWR) printf("file2.txt is opened in read-write mode.\n");
    else printf("file2.txt is not opened in read-write mode.\n");



    // Close file descriptors
    close(fd_read);
    close(fd_write);
    close(fd_read_write);

    return 0;
}
