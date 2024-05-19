/*Description:program using sigaction system call to catch the signals
*/
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void sig_handler(int signo)
{
    if (signo == SIGFPE){
        printf("CAPTURED SIGFPE\n");
        exit(0);
    }
}

int main(void)
{
    struct sigaction act;
    act.sa_handler = &sig_handler;
    if (sigaction(SIGFPE, &act, NULL) < 0) { // SIGFPE : Floating point exception.
		perror ("floating point error");
		return 1;
	}
    float n = 1/0;
    printf("no SIGFPE received\n");
    return 0;
}
