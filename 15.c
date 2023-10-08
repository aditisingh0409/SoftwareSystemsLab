/*
============================================================================
Name : 15.c
Author : Aditi Singh
Description : Write a simple program to send some data from parent to the child process.
Date: 8th Oct, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    char msg[] = "Hello Child!  - From Parent."; 
    if (pipe(pipefd) == -1) 
        perror("Pipe creation failed");

    pid_t child_pid = fork(); 
    if (child_pid == -1) 
        perror("Fork failed");

    if (child_pid == 0) 
    { 
        close(pipefd[1]); 
        char msgReceived[30]; 
        
        // Read data from the parent through the pipe
        if (read(pipefd[0], msgReceived, sizeof(msgReceived)) == -1) 
            perror("Read from pipe failed in child");

        printf("Child received: %s\n", msgReceived);

        close(pipefd[0]); 
    } 
    else 
    { 
        close(pipefd[0]); 

        // Send data to the child through the pipe
        if (write(pipefd[1], msg, strlen(msg) + 1) == -1)
            perror("Write to pipe failed in parent");

        close(pipefd[1]);
        printf("Parent sent: %s\n", msg);
    }

    return 0;
}

