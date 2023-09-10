/*
============================================================================
Name : 5.c
Author : Aditi Singh
Description : Write a program to create five new files with infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd.
Date: 28th Aug, 2023.
============================================================================
*/
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
  while(1)
  {     
    for (int i = 1; i <= 5; ++i) 
    {
      char fname[20];
      snprintf(fname, sizeof(fname), "File%d.txt", i);
      int fd = creat(fname, O_RDWR);
  
      if (fd == -1) 
      {
        perror("Error creating file");
        return 1;
      }

      printf("Created file: %s\n", fname);
     sleep(5);
    }
  }
  
  return 0;
}
