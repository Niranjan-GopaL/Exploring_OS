/*Description:program using sigaction system call to catch the signals
*/
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void sig_handler(int signo)
{
    if (signo == SIGSEGV){
        printf("CAPTURED SIGSEGV\n");
        exit(0);
    }
}

int main(void)
{
    struct sigaction act;
    act.sa_handler = &sig_handler;
    if (sigaction(SIGSEGV, &act, NULL) < 0) { //SIGSEGV invalid memory reference
		perror ("invalid memory");
		return 1;
	}
    int* p = NULL;
    printf("%d\n",*p);
    printf("no SIGSEGV received\n");
    return 0;
}
