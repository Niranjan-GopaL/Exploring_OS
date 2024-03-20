#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 100

/* 
use :=
file1.txt
file2.txt
output.txt
*/

int main(void) {
    char file_name_1[100], file_name_2[100];
    char buffer[BUFFER_SIZE];

    printf("Enter the input file name: ");
    scanf("%s", file_name_1);

    // Open the input file for reading
    int fd1 = open(file_name_1, O_RDONLY);
    if (fd1 == -1) { perror("Error opening input file"); return 1; }

    printf("Enter the output file name: ");
    scanf("%s", file_name_2);

    // Open or create the output file for writing
    int fd2 = open(file_name_2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 == -1) {
        perror("Error opening output file");
        close(fd1);
        return 1;
    }

    // Read from input file and write to output file
    ssize_t bytes_read;
    while ((bytes_read = read(fd1, buffer, BUFFER_SIZE)) > 0) {
        ssize_t bytes_written = write(fd2, buffer, bytes_read);
        if (bytes_written == -1) {
            perror("Error writing to output file");
            close(fd1);
            close(fd2);
            return 1;
        }
    }

    // Check if there was an error while reading from the input file
    if (bytes_read == -1) {
        perror("Error reading from input file");
        close(fd1); close(fd2);
        return 1;
    }

    // Close both files
    close(fd1); close(fd2);
    printf("File copied successfully.\n");
    return 0;
}