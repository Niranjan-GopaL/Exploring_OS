#include <sys/sem.h>

union semum {
	int val;
	unsigned short int *array;
} args;

int main() {
	int key, semid;
	key = ftok(".", 'r');
	semid = semget(key, 1, IPC_CREAT | 0744);
	args.val = 1;
	semctl(semid, 0, SETVAL, args);
}
