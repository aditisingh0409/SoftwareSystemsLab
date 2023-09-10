/*
============================================================================
Name : 17a.c
Author : Aditi Singh
Description : Write a program to simulate online ticket reservation. Implement write lock
Write a program to open a file, store a ticket number and exit. Write a separate program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.
Date: 28th Aug, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{	
  int fd = open("f17.txt", O_RDWR | O_CREAT, 0644);
  if(fd==-1)
  {
    printf("Failed to open the file");
    return 1;
  }

  struct flock write_lock;
  memset(&write_lock, 0, sizeof(struct flock));
  write_lock.l_type = F_WRLCK; 
  write_lock.l_whence = SEEK_SET;
  write_lock.l_start = 0;
  write_lock.l_len = 0;
  
  char buffer[16];
  int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
  if (bytes_read == -1) 
  {
    perror("Error reading ticket number");
    close(fd);
    return 1;
  }
  buffer[bytes_read] = '\0';

  int ticket_number = atoi(buffer);
  ticket_number++;
  snprintf(buffer, sizeof(buffer), "%d", ticket_number);

  lseek(fd, 0, SEEK_SET);
  int bytes_written = write(fd, buffer, strlen(buffer));
  if (bytes_written == -1) 
  {
    perror("Error writing ticket number");
    close(fd);
    return 1;
  }
  printf("Ticket number stored and updated: %d\n", ticket_number);

  write_lock.l_type = F_UNLCK;
  
    close(fd);
    return 0;
}

