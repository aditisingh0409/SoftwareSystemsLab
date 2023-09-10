/*
============================================================================
Name : 26.c
Author : Aditi Singh
Description : Write a program to execute an executable program.
a. use some executable program
b. pass some input to an executable program. (for example execute an executable of $./a.out name)
Date: 9th Sept, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *program = "./26.out"; 
    char *arguments[] = {"./26.out", "name", NULL};

    int exec_result = execvp(program, arguments);
    if (exec_result == -1) {
        perror("Error executing program");
        return 1;
    }
    printf("This code should not be reached.\n");

    return 0;
}

