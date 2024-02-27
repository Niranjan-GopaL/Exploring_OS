#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Open the file in read-write mode
    int fd = open("file.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Write 10 bytes to the file
    char data1[] = "0123456789";
    if (write(fd, data1, 10) != 10) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    // Move the file pointer by 10 bytes
    off_t new_offset = lseek(fd, 10, SEEK_CUR);
    if (new_offset == -1) {
        perror("Error seeking file");
        close(fd);
        return 1;
    }

    // Write another 10 bytes to the file
    char data2[] = "ABCDEFGHIJ";
    if (write(fd, data2, 10) != 10) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }

    printf("Data written successfully.\n");
    return 0;
}

