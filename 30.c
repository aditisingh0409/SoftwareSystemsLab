/*
============================================================================
Name : 30.c
Author : Aditi Singh
Description : Write a program to run a script at a specific time using a Daemon process.
Date: 9th Sept, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main() 
{
  if (!fork()) 
  {
    setsid();
    chdir("/");
    umask(0);
    while(1)
    {
      sleep(10);
      printf("\nChild PID: %d\n", getpid());
      printf("Daemon Process Running \n");
    }
  }
  else
    exit(0);
}

