/*
============================================================================
Name : 20.c
Author : Aditi Singh
Description : Find out the priority of your running program. Modify the priority with nice command.
Date: 9th Sept, 2023.
============================================================================
*/
#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

int main()
{
  int priority = getpriority(PRIO_PROCESS, 0);
  printf("Current priority: %d\n",priority);
  printf("Enter the nice value to change the priority: ");
  
  int inp;
  scanf("%d",&inp);
  int pr = nice(inp);
  printf("Modified priority: %d\n",pr);
  
  return 0;
}
