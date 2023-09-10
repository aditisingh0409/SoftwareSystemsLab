/*
============================================================================
Name : 4.c
Author : Aditi Singh
Description : Write a program to open an existing file with read write mode. Try O_EXCL flag also.
Date: 28th Aug, 2023.
============================================================================
*/
#include <stdio.h>
#include <fcntl.h>

int main()
{ 
  int fd = open("f4.txt", O_EXCL, O_RDWR);
  if(fd == -1)
    perror("Failed\n");
  else
    printf("File Opened\n");
    
  printf("File Descriptor = %d\n", fd);
  return 0;
}
