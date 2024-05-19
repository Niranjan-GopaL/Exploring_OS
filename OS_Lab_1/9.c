#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#define ll long


int main() {
    char *filename = "file1.txt"; 
    struct stat file_property;

    if (stat(filename, &file_property) == -1) {
        perror("Error");
        return 1;
    }

    printf("File: %s\n", filename);
    printf("Inode: %ld\n", (ll)file_property.st_ino);
    printf("Number of hard links: %ld\n", (ll)file_property.st_nlink);
    printf("UID: %d\n", file_property.st_uid);
    printf("GID: %d\n", file_property.st_gid);
    printf("Size: %ld bytes\n", (ll)file_property.st_size);
    printf("Block size: %ld bytes\n", (ll)file_property.st_blksize);
    printf("Number of blocks: %ld\n", (ll)file_property.st_blocks);
    printf("Time of last access: %s", ctime(&file_property.st_atime));
    printf("Time of last modification: %s", ctime(&file_property.st_mtime));
    printf("Time of last change: %s", ctime(&file_property.st_ctime));

    return 0;
}
