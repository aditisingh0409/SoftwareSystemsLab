/*
============================================================================
Name : 6.c
Author : Aditi Singh
Description : Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls
Date: 28th Aug, 2023.
============================================================================
*/
#include <unistd.h>

int main() 
{
  char buff[10];
  read(0, &buff, 10);
  write(1, &buff, 10);
  
  return 0;
}
