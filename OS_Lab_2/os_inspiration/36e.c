#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    if (mkfifo("myfifo2", 0744) == -1) {
        perror("FIFO creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Success\n");
    return 0;
}
