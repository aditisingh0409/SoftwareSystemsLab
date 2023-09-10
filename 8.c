/*
============================================================================
Name : 8.c
Author : Aditi Singh
Description : Write a program to open a file in read only mode, read line by line and display each line as it is read. Close the file when end of file is reached.
Date: 28th Aug, 2023.
============================================================================
*/
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  int read_file = open(argv[1], O_RDONLY);
  if(read_file == -1)
  {
    perror("Error opening file");
    return -1;
  }

  int num = 0;
  while(!num)
  {
    char buffer;
    while(1)
    {
      int r_fd = read(read_file, &buffer,1);
      if(r_fd == 0)
      {
        num = 1;
        break;
      }
      else
      {
        printf("%c",buffer);
        if(buffer == '\n')
          break;
      }
    }
  }

  int close_file = close(read_file);
  if(close_file == -1)
    perror("Error closing file");

  return 0;
}
