/*Description:program using sigaction system call to catch the signals
*/
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void sig_handler(int signo)
{
    if (signo == SIGINT){
        printf("\nCAPTURED SIGINT\n");
        exit(0);
    }
}

int main(void)
{
    struct sigaction act;
    act.sa_handler = &sig_handler;
    if (sigaction(SIGINT, &act, NULL) < 0) { // SIGINT : Interrupt from keyboard
		perror ("error occured");
		return 1;
	}
    sleep(5);
    printf("no SIGINT received\n");
    return 0;
}
