/*
============================================================================
Name : 21.c
Author : Aditi Singh
Description : Write two programs so that both can communicate by FIFO -Use two way communication.
Date: 10th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    char buff1[30], buff2[30];
    
    int fd1 = open("myfifo1", O_WRONLY);
    if (fd1 == -1) {
        perror("open (receiver)");
        exit(1);
    }
 
    int fd2 = open("myfifo2", O_RDONLY);
    if (fd2 == -1) {
        perror("open (sender)");
        exit(1);
    }
    
    printf("Enter data to send: ");
    scanf("%[^\n]", buff1);
    write(fd1, buff1, sizeof(buff1));
    
    read(fd2, buff2, sizeof(buff2));
    printf("Received message: %s\n", buff2);

    close(fd1);
    close(fd2);

    return 0;
}

