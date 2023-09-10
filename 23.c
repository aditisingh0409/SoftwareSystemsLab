/*
============================================================================
Name : 23.c
Author : Aditi Singh
Description : Write a program to create a Zombie state of the running program.
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
        printf("In child section PID is: %d\n", child_pid);
        printf("Child process is exiting.\n");
    } 
    else {
        printf("In parent section PID is: %d\n", child_pid);
        printf("Parent process is exiting.\n");
        sleep(20);
    }
    return 0;
}

