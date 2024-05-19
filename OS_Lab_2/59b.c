/*Description:using signal system call to catch the signals.
*/
#include <signal.h>
#include<stdio.h>
#include<stdlib.h>

void handler(int signum){
	if(signum == SIGINT){
		printf("CAPTURED SIGNAL"); 
		
	}
}

int main()
{
	if(signal(SIGINT,handler)==SIG_ERR){
		printf("cant catch");}
	sleep(5);
  	return 0;	
}
