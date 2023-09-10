/*
============================================================================
Name : 12.c
Author : Aditi Singh
Description : Write a program to find out the opening mode of a file. Use fcntl.
Date: 28th Aug, 2023.
============================================================================
*/
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
  int fd = open("f12.txt", O_WRONLY);
  int mode = fcntl(fd, F_GETFL);
  switch(mode)
  {
    case 32768 : printf("Read Mode (r)\n"); 
		 break;
    case 32769 : printf("Write Mode (w)\n"); 
		 break;
    case 33793 : printf("Append Mode (a)\n"); 
		 break;
    case 32770 : printf("Read and Write Mode (r+ || w+)\n"); 
		 break;
    case 32794 : printf("Read and Append Mode (a+)\n"); 
		 break;
  }
  
  return 0;
}
