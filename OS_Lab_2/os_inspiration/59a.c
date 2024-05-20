#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void my_sigsegv_handler(int sig)
{
    printf("Received SIGSEGV signal: %d\n", sig);
    printf("Exiting due to segmentation fault.\n");
    exit(EXIT_FAILURE);
}
/*SIGSEGV is caused
by an invalid memory reference or segmentation fault. */
int main()
{
    signal(SIGSEGV, my_sigsegv_handler);
    printf("Catching SIGSEGV\n");

    int *p = NULL;
    int k = *p; // Dereference a null pointer to trigger segmentation fault
    printf("%d\n", k); // This line won't be executed if segmentation fault occurs

    printf("No SIGSEGV signal received\n");
    return 0;
}




