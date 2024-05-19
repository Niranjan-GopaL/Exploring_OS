/*Description: set a interval timer in 10sec and
10micro second using ITIMER_PROF
*/
#include <sys/time.h>
#include<stdio.h>

int main()
{
	struct itimerval value; 
	int which = ITIMER_PROF ;
	getitimer(which,&value);

	value.it_interval.tv_sec = 10; 
	value.it_interval.tv_usec = 10;

	value.it_value.tv_sec = 10;
	value.it_value.tv_usec = 10;

	setitimer(which,&value,NULL); 
	while(1);
}
