#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>

#define RECORD_SIZE 100

void lockFile(FILE *file) {
    if (flock(fileno(file), LOCK_EX) == -1) {
        perror("Error locking file");
        exit(EXIT_FAILURE);
    }
}

void unlockFile(FILE *file) {
    if (flock(fileno(file), LOCK_UN) == -1) {
        perror("Error unlocking file");
        exit(EXIT_FAILURE);
    }
}

int main() {
    FILE *file;
    int ticket_number;

    // Open the file in read mode and handle errors
    if ((file = fopen("ticket.txt", "r+")) == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Implement a write lock
    lockFile(file);

    // Read the ticket number from the file
    if (fscanf(file, "%d", &ticket_number) != 1) {
        perror("Error reading ticket number");
        unlockFile(file);
        fclose(file);
        exit(EXIT_FAILURE);
    }
    
    // Increment the ticket number
    ticket_number++;

    // New ticket number
    printf("New ticket number: %d\n", ticket_number);

    // Move the file pointer to the beginning of the file
    rewind(file);

    // Write the updated ticket number to the file
    if (fprintf(file, "%d\n", ticket_number) < 0) {
        perror("Error writing ticket number");
        unlockFile(file);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Release the write lock
    unlockFile(file);

    // Close the file
    fclose(file);

    return 0;
}
