#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> // Include this header for perror()

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];   
    ssize_t bytes_read;

    // Read input from stdin
    while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
        
        // Null-terminate the string
        buffer[bytes_read] = '\0'; 

        // Remove trailing newline character
        // if (bytes_read > 0 && buffer[bytes_read - 1] == '\n') {
        //     buffer[bytes_read - 1] = '\0';
        // }
        
        if (strcmp("-1\n", buffer) == 0) {
            printf("Strings match, Program exiting ...!\n");
            break;  
        }       
        
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

