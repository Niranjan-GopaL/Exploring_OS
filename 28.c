#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    // Get current priority
    int priority = getpriority(PRIO_PROCESS, 0);
    printf("Current Priority: %d\n", priority);

    // Modify priority using nice command
    nice(5);

    // Check modified priority
    priority = getpriority(PRIO_PROCESS, 0);
    printf("Modified Priority: %d\n", priority);

    return 0;
}
