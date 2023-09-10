/*
============================================================================
Name : 25.c
Author : Aditi Singh
Description : Write a program to create three child processes. The parent should wait for a particular child (use waitpid system call).
Date: 9th Sept, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int child_pids[3];
    for (int i = 0; i < 3; i++) {
        int pid = fork();

        if (pid == -1) {
            perror("Error forking");
            return 1;
        }

        if (pid == 0) {
            printf("Child %d (PID %d) is running.\n", i + 1, getpid());
            sleep(2);
            printf("Child %d (PID %d) stopped.\n", i + 1, getpid());
            exit(0);
        } 
        else {
            child_pids[i] = pid;
        }
    }
    
    int status;
    int waited_pid = waitpid(child_pids[1], &status, 0);
    if (WIFEXITED(status)) {
        printf("Parent: Child %d (PID %d) has stopped with status %d.\n", 2, waited_pid, WEXITSTATUS(status));
    }
    
    return 0;
}

