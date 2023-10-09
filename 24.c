/*
============================================================================
Name : 24.c
Author : Aditi Singh
Description : Write a program to create a message queue and print the key and message queue id.
Date: 8th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key = ftok("message_queue_key", 'A');
    int msgqid = msgget(key, IPC_CREAT | 0666);
    printf("Message Queue Key: %d\n", (int)key);
    printf("Message Queue ID: %d\n", msgqid);

    return 0;
}

