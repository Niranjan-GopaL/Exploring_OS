#include <stdio.h>
#include <stdlib.h>

// contains the environment variables
extern char **environ;


int main(void){
    int i = 0;
    while (environ[i]){
        printf("%s\n", environ[i]); i++;
    }
    return 0;
}