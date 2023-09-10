/*
============================================================================
Name : 19.c
Author : Aditi Singh
Description : Write a program to find out time taken to execute getpid system call. Use time stamp counter.
Date: 9th Sept, 2023.
============================================================================
*/
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<time.h>

int main(int argc, char* argv[]){
	clock_t start, end;
	start =  clock();
	int pid = getpid();
	end = clock();
	printf("Time Taken: %f\n", ((double)(end-start)/CLOCKS_PER_SEC));
}

