/*
============================================================================
Name : 10.c
Author : Aditi Singh
Description : Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10 bytes (use lseek) and write again 10 bytes.
a. check the return value of lseek
b. open the file with od and check the empty spaces in between the data.
Date: 28th Aug, 2023.
============================================================================
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{ 
  int fd;
  fd = open("f10.txt", O_RDWR | O_CREAT, 0644);
  if(fd == -1)
    perror("Failed to open file\n");
  else
    printf("File has been opened\n");

  char buffer1[10] = "Hello All ";
  int write1 = write(fd, buffer1, 10);
  printf("No. of bytes written first time: %d\n", write1);

  int value = lseek(fd, 10, SEEK_CUR);
  printf("Return value of lseek: %d\n", value);
  
  char buffer2[10] = "I am Aditi";
  int write2 = write(fd, buffer2, 10);
  printf("No. of bytes written second time: %d\n", write2);

  return 0;
}
