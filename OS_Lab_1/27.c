#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sched.h>


int main() {
    int max_priority = sched_get_priority_max(SCHED_FIFO);
    int min_priority = sched_get_priority_min(SCHED_FIFO);

    printf("Maximum Real-Time Priority: %d\n", max_priority);
    printf("Minimum Real-Time Priority: %d\n", min_priority);

    return 0;
}
