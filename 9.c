/*
============================================================================
Name : 9.c
Author : Aditi Singh
Description : Write a program to print the following information about a given file.
a. inode
b. number of hard links
c. uid
d. gid
e. size
f. block size
g. number of blocks
h. time of last access
i. time of last modification
j. time of last change
Date: 28th Aug, 2023.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

int main()
{
  struct stat info;

  if(stat("f9.txt", &info) == -1)
  {
    perror("stat");
    return 0;
  }

  printf("Inode: %lu\n",info.st_ino);
  printf("Number of Hard Links: %lu\n", info.st_nlink);
  printf("UID: %u\n", info.st_uid);
  printf("GID: %u\n", info.st_gid);
  printf("Size: %lld bytes\n", (long long)info.st_size);     	
  printf("Block Size: %ld bytes\n", (long)info.st_blksize);
  printf("Number of blocks: %lld\n", (long long)info.st_blocks);
  printf("Time of last access: %s", ctime(&info.st_atime));
  printf("Time of last modification: %s", ctime(&info.st_mtime));
  printf("Time of last change: %s", ctime(&info.st_ctime));

  return 0;
}
