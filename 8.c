// #include <unistd.h>
// #include <stdio.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>

// int main(void){
//     int fd1;
//     char buf[100];
    
//     fd1=open("file2.txt",O_RDONLY| O_EXCL);

//     while(read(fd1,buf,1)>0){
//         // \n in buffer needs to be removed 
//         if(buf[0] == '\n')  getchar(); 

//         else { printf("%s",buf); }
//     }

//     close(fd1);
// }


#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("file1.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[100];  // Assuming each line is not longer than 100 characters

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
    return 0;
}
