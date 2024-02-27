#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main() {
    int current_policy = sched_getscheduler(0);
    printf("Current Scheduling Policy: %d\n", current_policy);

    // Set scheduling policy to SCHED_RR
    struct sched_param param;
    param.sched_priority = 10;
    sched_setscheduler(0, SCHED_RR, &param);

    // Check modified policy
    current_policy = sched_getscheduler(0);
    printf("Modified Scheduling Policy: %d\n", current_policy);

    return 0;
}
