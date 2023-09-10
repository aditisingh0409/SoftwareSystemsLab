/*
============================================================================
Name : 7.c
Author : Aditi Singh
Description : Write a program to copy file1 into file2 ($cp file1 file2).
Date: 28th Aug, 2023.
============================================================================
*/
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  if (argc!=3)
  {
    printf("Enter file names for copying from file1 to file2\n");
    return 0;
  }

  int read_file = open(argv[1], O_RDONLY);
  int write_file = open(argv[2], O_WRONLY|O_CREAT);
  if(read_file == -1 || write_file == -1)
    printf("Error reading files or writing in files");
	
  while(1)
  {
    char buffer;
    int read_c = read(read_file, &buffer, 1);
    printf("%d ", read_c);
    if(read_c == 0)
      break;
    int write_c = write(write_file, &buffer, 1);
  }
  printf("\n");
  
  int fd_read = close(read_file);
  int fd_write = close(write_file);
  if(fd_read == -1 || fd_write == -1)
    printf("Error closing files");

  return 0;
}
