/*
============================================================================
Name : 27.c
Author : Aditi Singh
Description : Write a program to execute ls -Rl by the following system calls
a. execl
b. execlp
c. execle
d. execv
e. execvp
Date: 9th Sept, 2023.
============================================================================
*/
#include <unistd.h>
#include <stdio.h>

int main() 
{
  char n;
  printf("Choose from options:\na. Using execl()\nb. Using execlp()\nc. Using execle()\nd. Using execv()\ne. Using execvp()\n");
  scanf("%c", &n);
  
  switch(n) 
  {   
    case 'a': printf("Using execl()\n");
              execl("/usr/bin/ls"  ,"ls",  "-Rl", (char *)NULL);
    case 'b': printf("Using execlp()\n");
              execlp("ls","ls", "-Rl", (char *)NULL);
    case 'c': printf("Using execle()\n");
              char *env[] = { "HOME=/usr/home", "LOGNAME=home", (char *)0 };
              execle ("/bin/ls", "ls", "-Rl", (char *)0, env);
    case 'd': printf("Using execv()\n");
              char *cmd1[] = { "ls", "-Rl", (char *)0 };
              execv ("/bin/ls", cmd1);
    case 'e': printf("Using execvp()\n");
              char *cmd[] = { "ls", "-Rl", (char *)0 };
              execvp ("ls", cmd);
    default: printf("Enter correct option\n");
  }
  return 0;
}
