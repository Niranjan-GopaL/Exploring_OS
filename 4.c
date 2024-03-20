#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/*
-> `open` and `creat` functions are declared in the header file fcntl.h, 
-> while `close` is declared in unistd.h.
-> `open-time` flags specify options affecting how open will behave
*/


void error_check_and_print(int fd_or_fd_excel, int time){
    if(time==1){
        if (fd_or_fd_excel == -1) { perror("Error opening file"); exit(EXIT_FAILURE);
        } else { printf("File opened successfully in read-write mode with descriptor: %d\n", fd_or_fd_excel); }
    }else if(time ==2){
        if (fd_or_fd_excel == -1) { perror("Error opening file with O_EXCL flag"); exit(EXIT_FAILURE);
        } else { printf("File opened successfully with O_EXCL flag with descriptor: %d\n", fd_or_fd_excel); }
    }
}


int main() {
    const char *filename = "example.txt";

    // Attempt to open the existing file in read-write mode
    int fd = open(filename, O_RDWR);
    error_check_and_print(fd,1);
    close(fd);


    // Attempt to open the existing file with O_EXCL flag (exclusive creation)
    int fd_excl = open(filename, O_RDWR | O_EXCL);
    error_check_and_print(fd_excl,2);
    close(fd_excl);
    return 0;
}

