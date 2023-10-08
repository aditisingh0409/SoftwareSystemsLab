/*
============================================================================
Name : 19.c
Author : Aditi Singh
Description : Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
c. mknod system call
d. mkfifo library function
Date: 8th Oct, 2023.
============================================================================
*/

/*  
The first two methods of creating a FIFO file can be done directly from the shell.
        mknod MYFIFO p
        mkfifo MYFIFO
        
We can use the strace command to trace system calls generated by both mknod and mkfifo:

        strace -e trace=open,openat mknod MYFIFO p
        strace -e trace=open,openat mkfifo MYFIFO

This will show us which system calls each command uses to create the FIFO.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    
    // Create a FIFO file using the mknod system call
    if (mknod("myfifo1", S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        return 1;
    }

    printf("FIFO 'myfifo1' created successfully using mknod system call.\n");
    
    // Create a FIFO file using the mkfifo library function
    if (mkfifo("myfifo2", 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    printf("FIFO 'myfifo2' created successfully using mkfifo library function.\n");
    return 0;
}

