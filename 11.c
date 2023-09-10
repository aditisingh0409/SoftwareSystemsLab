/*
============================================================================
Name : 11.c
Author : Aditi Singh
Description : Write a program to open a file, duplicate the file descriptor and append the file with both the descriptors and check whether the file is updated properly or not.
a. use dup
b. use dup2
c. use fcntl
Date: 28th Aug, 2023.
============================================================================
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
  int fd1, fd2;
  char text[20] = "Aditi Singh";
  fd1 = open("f11.txt", O_RDWR|O_CREAT, 0777);
  fd2 = dup(fd1);
  
  write(fd1, text, sizeof(text));
  write(fd2, text, sizeof(text));
  printf("File descriptor fd1 = %d and fd2(using dup()) = %d\n", fd1, fd2);
  close(fd1);
  
  int fd3;
  fd3 = dup2(fd2, 10);
  write(fd3, text, sizeof(text));
  int fd4 = fcntl(fd3, F_DUPFD);
  printf("File descriptor fd1 = %d, fd2 = %d and fd3(using dup2()) = %d\n", fd1, fd2, fd3);
  write(fd4, text, sizeof(text));
  printf("File descriptor fd1 = %d, fd2 = %d, fd3 = %d and fd4(using fcntl()) = %d\n", fd1, fd2, fd3, fd4);
  return 0;
}
  
