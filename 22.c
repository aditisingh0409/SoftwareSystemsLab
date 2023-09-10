/*
============================================================================
Name : 22.c
Author : Aditi Singh
Description : Write a program, open a file, call fork, and then write to the file by both the child as well as the parent processes. Check output of the file.
Date: 9th Sept, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd = open("f22.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    pid_t child_pid = fork();
    if (child_pid == 0) {
        const char *child_message = "Child process writing to the file.\n";
        write(fd, child_message, strlen(child_message));
        close(fd);
    } 
    else {
        const char *parent_message = "Parent process writing to the file.\n";
        write(fd, parent_message, strlen(parent_message));
        close(fd);
        printf("Both child and parent have written to the file.\n");
    }
    return 0;
}

