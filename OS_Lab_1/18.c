#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>


// Fun fact :-
// this value should not be changed since gcc throws a buffer "overread" error
// this is a bug that is still to be addressed. Look at :-
//  https://stackoverflow.com/questions/69891976/gcc-11-gives-wstringop-overflow-when-no-string-operation-is-used
#define RECORD_SIZE 22



// Function to lock a record for reading
void lockRecordForRead(int fileDescriptor, int recordIndex) {
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = recordIndex * RECORD_SIZE;
    lock.l_len = RECORD_SIZE;
    lock.l_pid = getpid();

    if (fcntl(fileDescriptor, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
}

// lock a record for writing
void lockRecordForWrite(int fileDescriptor, int recordIndex) {
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = recordIndex * RECORD_SIZE;
    lock.l_len = RECORD_SIZE;
    lock.l_pid = getpid();

    if (fcntl(fileDescriptor, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
}

// Unlock a record
void unlockRecord(int fileDescriptor, int recordIndex) {
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = recordIndex * RECORD_SIZE;
    lock.l_len = RECORD_SIZE;
    lock.l_pid = getpid();

    if (fcntl(fileDescriptor, F_SETLK, &lock) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int fileDescriptor;
    char buffer[RECORD_SIZE];

    if ((fileDescriptor = open("records.txt", O_RDWR | O_CREAT, 0666)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write some initial data
    //  char inputString[100];
    printf("Enter a string: ");

    const char* record_1_data = "Data in Record 1 ... ";
    const char* record_2_data = "Data in Record 2 ... ";
    const char* record_3_data = "Data in Record 3 ... ";

    write(fileDescriptor, record_1_data , RECORD_SIZE);
    write(fileDescriptor, record_2_data , RECORD_SIZE);
    write(fileDescriptor, record_3_data , RECORD_SIZE);

    // Perform operations on records with locking

    // Lock and read the first record
    lockRecordForRead(fileDescriptor, 0);
    lseek(fileDescriptor, 0, SEEK_SET);
    read(fileDescriptor, buffer, RECORD_SIZE);
    printf("Read Record 1: %s\n", buffer);
    unlockRecord(fileDescriptor, 0);

    // Lock and write to the second record
    lockRecordForWrite(fileDescriptor, 1);
    lseek(fileDescriptor, 1 * RECORD_SIZE, SEEK_SET);

    const char* new_record = "Data in Record 1 ... ";
    write(fileDescriptor, new_record, RECORD_SIZE);
    printf("Wrote to Record 2\n");
    unlockRecord(fileDescriptor, 1);

    // Lock and read the third record
    lockRecordForRead(fileDescriptor, 2);
    lseek(fileDescriptor, 2 * RECORD_SIZE, SEEK_SET);
    read(fileDescriptor, buffer, RECORD_SIZE);
    printf("Read Record 3: %s\n", buffer);
    unlockRecord(fileDescriptor, 2);

    // Close the file
    close(fileDescriptor);

    return EXIT_SUCCESS;
}
