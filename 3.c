/*
============================================================================
Name : 3.c
Author : Aditi Singh
Description : Write a program to create a file and print the file descriptor value. Use creat ( ) system call
Date: 28th Aug, 2023.
============================================================================
*/
#include <fcntl.h>
#include<stdio.h>

int main()
{
  int fd1 = creat("f3a.txt",O_RDONLY | O_WRONLY | O_RDWR);
  printf("File Descriptor 1 = %d\n",fd1);
	
  int fd2 = creat("f3b.txt",O_RDONLY | O_WRONLY | O_RDWR);
  printf("File Descriptor 2  = %d\n",fd2);
	
  return 0;
}
