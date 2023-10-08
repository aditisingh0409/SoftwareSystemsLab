/*
============================================================================
Name : 14.c
Author : Aditi Singh
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
Date: 8th Oct, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    char writeMsg[] = "Saying Hello from the PIPE!";
    char readMsg[30]; 

    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
    }

    // Writing to the pipe
    if (write(pipefd[1], writeMsg, strlen(writeMsg) + 1) == -1) 
        perror("Write to pipe failed");

    // Reading from the pipe
    if (read(pipefd[0], readMsg, sizeof(readMsg)) == -1) 
        perror("Read from pipe failed");

    close(pipefd[0]);
    close(pipefd[1]);

    printf("Read from pipe: %s\n", readMsg);

    return 0;
}

