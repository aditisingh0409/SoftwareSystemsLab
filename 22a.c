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
#include <sys/select.h>

int main(void)
{
    mkfifo("fifo1",0666);
    fd_set rfds;
    struct timeval tv;
    char buff[30];
    int fd = open("fifo1",O_RDONLY);
    
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    
    select(fd + 1, &rfds, NULL, NULL, &tv);

    if (FD_ISSET(fd, &rfds))
    {
        int res = read(fd, buff, sizeof(buff));
	if (res > 0)
            printf("Received data from FIFO: %s\n", buff);
        
    }	
    else
          printf("No data available within 10 seconds\n");

    close(fd);
    return 0;
}

