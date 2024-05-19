#include <sys/types.h>
#include <sys/stat.h>
 #include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>


#define MAX_PATH_LEN 1024

void extract_process_info(const char *pid) {
    char proc_path[MAX_PATH_LEN];
    snprintf(proc_path, sizeof(proc_path), "/proc/%s/status", pid);

    FILE *fp = fopen(proc_path, "r");
    if (fp != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), fp)) 
            if (strncmp(line, "Name:", 5) == 0 || strncmp(line, "State:", 6) == 0 || strncmp(line, "Pid:", 4) == 0) {
                printf("%s", line);
        }
        fclose(fp);
    }
}




int main() {
    // Fork off the parent process
    pid_t pid = fork();

    // If we got a good PID, then we can exit the parent process
    if (pid > 0) {
        printf("Background process started with PID: %d\n", pid);
        exit(EXIT_SUCCESS);
    }

    // Change the file mode mask
    umask(0);

    // Create a new session
    pid_t sid = setsid();
    if (sid < 0) {
        perror("Error creating session");
        exit(EXIT_FAILURE);
    }

    // Change the current working directory
    if ((chdir("/")) < 0) {
        perror("Error changing directory");
        exit(EXIT_FAILURE);
    }

    // Close out the standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Infinite loop to traverse /proc directory and extract process info
    while (1) {
        DIR *dir;
        struct dirent *entry;

        if ((dir = opendir("/proc")) != NULL) {
            while ((entry = readdir(dir)) != NULL) {
                // Check if the entry is a directory and its name is a number (PID)
                if (entry->d_type == DT_DIR && strtol(entry->d_name, NULL, 10) != 0) {
                    extract_process_info(entry->d_name);
                }
            }
            closedir(dir);
        } else {
            perror("Error opening /proc directory");
            exit(EXIT_FAILURE);
        }
        sleep(5); // Sleep for 5 seconds before traversing again
    }

    return 0; // This line will never be reached
}

