/*
============================================================================
Name : 31.c
Author : Aditi Singh
Description : Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore
Date: 9th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int main() {
    sem_t binary_semaphore;
    if (sem_init(&binary_semaphore, 0, 1) == -1) {
        perror("sem_init");
        return 1;
    }
    
    printf("Binary semaphore initialized.\n");
    if (sem_destroy(&binary_semaphore) == -1) {
        perror("sem_destroy");
        return 1;
    }
    printf("Binary semaphore destroyed.\n");
    
    sem_t counting_semaphore;
    if (sem_init(&counting_semaphore, 0, 5) == -1) {
        perror("sem_init");
        return 1;
    }
    
    printf("Counting semaphore initialized.\n");
    if (sem_destroy(&counting_semaphore) == -1) {
        perror("sem_destroy");
        return 1;
    }
    printf("Counting semaphore destroyed.\n");
    
    return 0;
}
