/*Description:
program to implement semaphore to protect any critical section.
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	int fd;
	fd = open("tickets", O_CREAT | O_WRONLY, 0744);
	int ticket_number = 13;
	write(fd, &ticket_number, sizeof(ticket_number));
	close(fd);
}
