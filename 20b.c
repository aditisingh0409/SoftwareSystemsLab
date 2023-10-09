/*
============================================================================
Name : 20.c
Author : Aditi Singh
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 8th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char buff[30];
    
    int fd = open("myfifo", O_RDONLY);
    read(fd, buff, sizeof(buff));
    close(fd);

    printf("Received message from FIFO file: %s\n", buff);
    return 0;
}

