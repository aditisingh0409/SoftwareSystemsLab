/*
============================================================================
Name : 24.c
Author : Aditi Singh
Description : Write a program to create an orphan process.
Date: 9th Sept, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int child_pid = fork();

    if (child_pid == 0) {
        printf("Child process is running.\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
        sleep(5);
        printf("Parent PID after child becomes orphan: %d\n", getppid());
        printf("Child process stopped.\n");
    } 
    else {
        printf("Parent PID in parent section: %d\n", getpid());
        printf("Parent process stopped, leaving the child as an orphan.\n");
    }

    return 0;
}

