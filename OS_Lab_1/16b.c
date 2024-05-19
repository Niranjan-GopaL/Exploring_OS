#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){

    char filename[100];
    scanf("%s",filename);
    int fd=open(filename,O_RDONLY);
    printf("Lock Setting\n");
    close(fd);
}