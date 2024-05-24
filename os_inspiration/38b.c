#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    mkfifo("myfifo2", 0777);
    int fd1 = open("myfifo1", O_RDONLY);
    char buf1[100];
    read(fd1, buf1, sizeof(buf1));
    printf("Message : %s\n", buf1);
    close(fd1);
    int fd2 = open("myfifo2", O_WRONLY);
    char buf2[100];
    printf("Enter your message: \n");
    scanf(" %[^\n]", buf2);
    write(fd2, buf2, sizeof(buf2));
    close(fd2);
    return 0;
}
