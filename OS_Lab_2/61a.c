#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void my_sig_handler(int sig)
{
    printf("Received SIGSEGV signal: %d\n", sig);
    printf("Exiting....\n");
    exit(0);
}
/*SIGSEGV is caused
by an invalid memory reference or segmentation fault. */

int main()
{
    struct sigaction siga;
    siga.sa_handler = my_sig_handler;
    siga.sa_flags = SA_RESTART; //To avoid setting the dafault action
    sigaction(SIGSEGV, &siga, NULL);
    printf("Catching SIGSEGV\n");
    int *p1 = NULL;
    int *p2 = malloc(sizeof(int));
    int k = *p1; //change to p2 for valid memory assignment
    printf("%d\n", k);
    printf("No SIGSEGV signal received\n");
    return 0;
}
