#include <stdio.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd, key, semid;
	fd = open("tickets", O_RDWR);
	struct sembuf s = {0, -1, 0 | SEM_UNDO};
	key = ftok(".", 'r');
	semid = semget(key, 1, 0);

	int ticket_num;
	printf("Before the lock\n");
	semop(semid, &s, 1);
	printf("The file has been locked\n");
	read(fd, &ticket_num, sizeof(ticket_num));
	ticket_num++;
	printf("Ticket Num : %d\n", ticket_num);
	lseek(fd, -sizeof(ticket_num), SEEK_CUR);
	write(fd, &ticket_num, sizeof(ticket_num));
	printf("Press Enter to unlock\n");
	getchar();
	s.sem_op = 1;
	semop(semid, &s, 1);
	printf("Out of critical section\n");
}

