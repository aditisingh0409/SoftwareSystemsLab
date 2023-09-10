/*
============================================================================
Name : 29.c
Author : Aditi Singh
Description : Write a program to get scheduling policy and modify the scheduling policy (SCHED_FIFO, SCHED_RR).
Date: 9th Sept, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

int main() {
    int pid = getpid();
    int old_policy, new_policy;
    struct sched_param param;

    old_policy = sched_getscheduler(pid);
    if (old_policy == -1) {
        perror("Error getting scheduling policy");
        return 1;
    }

    char *c;
    if(old_policy == SCHED_FIFO)
      c = "SCHED_FIFO";
    else if(old_policy == SCHED_RR)
      c = "SCHED_RR";
    else if(old_policy == SCHED_OTHER)
      c = "SCHED_OTHER";
    else
      c = "Unknown";
      
    printf("Current scheduling policy for PID %d: %s\n", pid, c);

    new_policy = SCHED_RR;
    param.sched_priority = 50;
    if (sched_setscheduler(pid, new_policy, &param) == -1) {
        perror("Error setting scheduling policy");
        return 1;
    }
    printf("Changed scheduling policy to SCHED_RR.\n");

    return 0;
}

