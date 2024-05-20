#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd[2];
    pipe(fd);
    char buf[100];
    write(fd[1], "This is unnamed pipe", 21);
    read(fd[0], buf, 21);
    printf("%s\n", buf);
    return 0;
}