/*Description:using signal system call to catch the signals.
*/
#include <signal.h>
#include<stdio.h>
#include<stdlib.h>

void handler(int signum){
	if(signum == SIGSEGV){
		printf("CAPTURED SIGNAL"); 
		exit(0);
	}
}

int main()
{
	if(signal(SIGSEGV,handler)==SIG_ERR){
		printf("cant catch");}
	int* p = NULL;
	printf("%d\n",*p);
  	
	printf("no SIGSEGV received\n");
  	return 0;	
}
