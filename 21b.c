/*
============================================================================
Name : 21.c
Author : Aditi Singh
Description : Write two programs so that both can communicate by FIFO -Use two way communication.
Date: 10th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    char buff1[30], buff2[30];
    int fd1 = open("myfifo1", O_RDONLY);
    int fd2 = open("myfifo2", O_WRONLY);
    read(fd1, buff1, sizeof(buff1));
    
    printf("Received message: %s\n", buff1);\
    
    printf("Enter data to send: ");
    scanf("%[^\n]", buff2);
    write(fd2, buff2, sizeof(buff2));

    close(fd1);
    close(fd2);

    return 0;
}
 
