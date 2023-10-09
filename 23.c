/*
============================================================================
Name : 23.c
Author : Aditi Singh
Description : Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).
Date: 8th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

int main() {
    long maxFiles = sysconf(_SC_OPEN_MAX);
    printf("Maximum number of files that can be opened within a process: %ld\n", maxFiles);

    // Create a pipe and get its buffer size
    int pipeFd[2];
    int pipeSize = fpathconf(pipeFd[0], _PC_PIPE_BUF);
    printf("Size of a pipe (circular buffer): %d bytes\n", pipeSize);
    close(pipeFd[0]);
    close(pipeFd[1]);

    return 0;
}

