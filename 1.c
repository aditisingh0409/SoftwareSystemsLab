/*
============================================================================
Name : 1.c
Author : Aditi Singh
Description : Create the following types of a files using (i) shell command (ii) system call
a. soft link (symlink system call)
b. hard link (link system call)
c. FIFO (mkfifo Library Function or mknod system call)
Date: 28th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
  int v = symlink("f1.txt","destSL.txt");
  if(v < 0)
  {
    perror("Failed");
    return 1;
  }
  if(v == 0)
    printf("Soft Link Created\n");

  int f = link("f1.txt","destHL.txt");
  if(f < 0)
  {
    perror("Failed");
    return 1;
  }
  if(f == 0)
    printf("Hard Link Created\n");

  int e = mknod("destFIFO", S_IFIFO | 0666, 0);  
  if(e < 0)
    perror("Failed");
  if(e == 0)
    printf("FIFO created\n");

  return 0;
}
