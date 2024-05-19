/*Description:using signal system call to catch the signals.
*/
#include <signal.h>
#include<stdio.h>
#include<stdlib.h>

void handler(int signum){
	if(signum == SIGALRM){
		printf("CAPTURED SIGNAL"); 
		
	}
}

int main()
{
	if(signal(SIGALRM,handler)==SIG_ERR){
		printf("cant catch");}
    alarm(2);
    sleep(5);
    printf("no alarm received\n");
  	return 0;	
}

