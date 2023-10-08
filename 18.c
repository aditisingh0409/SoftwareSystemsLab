/*
============================================================================
Name : 18.c
Author : Aditi Singh
Description : Write a program to find out total number of directories on the pwd. execute ls -l | grep ^d | wc. Use only dup2.
Date: 8th Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main()
{
    int fd1[2];
    pipe(fd1);

    if(!fork())
    {
        dup2(fd1[1],1);
        close(fd1[0]);
        execlp("ls" , "ls" ,"-l",NULL);
    }
    else{
        int fd2[2];
        pipe(fd2);
        dup2(fd1[0],0);
        close(fd1[1]);

        if(!fork()){
            dup2(fd2[0],0);
            close(fd2[1]);
            execlp("wc","wc",NULL);
        }
        else{
            dup2(fd2[1],1);
            close(fd2[0]);
            execlp("grep","grep","^d",NULL);
        }
    }
    return 0;
}
