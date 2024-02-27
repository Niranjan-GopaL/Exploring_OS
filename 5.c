#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>  

// These are the contents of the files that are gonna be used for all other programs 
const char contents_of_file_i[][80] = {
    "CONTENTS IN FILE 0", 
    "CONTENTS IN FILE 1\nTHIS IS LINE 2\n THIS IS LINE 3\n ", // these contents are used in other programs too 
    "CONTENTS IN FILE 2", 
    "CONTENTS IN FILE 3", 
    "CONTENTS IN FILE 4", 
};


void generateFiles() {
    for (int i = 0; i < 5; ++i) {
        char filename[20];
        snprintf(filename, sizeof(filename), "file%d.txt", i);

        // Create a new file
        int fd = open(filename, O_CREAT | O_WRONLY, 0644);
        if (fd == -1) {
            perror("Error creating file");
            exit(EXIT_FAILURE);
        }

        // Write something to the file
        const char *content = contents_of_file_i[i];
        write(fd, content, strlen(content));

        // Close the file
        close(fd);

        sleep(1);  // Sleep for a second
    }
}

int main() {
    // Run in an infinite loop
    while (1) {
        // Generate new files
        generateFiles();

        // Print the file descriptor table
        printf("File Descriptor Table:\n");
        system("ls -l /proc/self/fd");

        // Sleep for a while before generating more files
        sleep(5);
    }

    return 0;
}
