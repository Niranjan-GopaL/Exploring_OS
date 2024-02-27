#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    int ticket_number = 0;
    
    // Open the file in write mode
    file = fopen("ticket.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    // Write the ticket number to the file
    fprintf(file, "%d\n", ticket_number);

    // Close the file
    fclose(file);
    
    printf("Ticket number %d stored successfully.\n", ticket_number);
    
    return 0;
}