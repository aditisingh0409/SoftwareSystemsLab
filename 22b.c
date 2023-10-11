/*
============================================================================
Name : 22.c
Author : Aditi Singh
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date: 10th Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(void)
{
    int f1;
    int fd;
    char msg[200];
    fd = open("fifo1",O_WRONLY);
    printf("Enter data: ");
    scanf("%s",msg);
    write(fd,msg,sizeof(msg));
    close(fd);
    return 0;
}

