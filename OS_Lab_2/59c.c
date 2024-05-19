/*Description:using signal system call to catch the signals.
*/
#include <signal.h>
#include<stdio.h>
#include<stdlib.h>

void handler(int signum){
	if(signum == SIGFPE){
		printf("CAPTURED SIGNAL"); 
		
	}
}

int main()
{
	if(signal(SIGFPE,handler)==SIG_ERR){
		printf("cant catch");}
	sleep(5);
  	return 0;	
}

