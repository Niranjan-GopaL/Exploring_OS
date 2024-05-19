/*Description:program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.
*/
#include <signal.h>
#include<stdio.h>
void sig_handler(int s){
	if(s==SIGINT){
		signal(SIGINT,SIG_DFL);
		printf("\n received signal set to default"); 
	}
}


int main(){
	if(signal(SIGINT,sig_handler)==SIG_ERR)
		printf("\n Cant catch SIGNINT\n");
	while(1);
	return 0 ;
}
