/*
============================================================================
Name : 29.c
Author : Aditi Singh
Description : Write a program to remove the message queue.
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
    
    if (msgctl(msgqid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID");
        return 1;
    }
    printf("Message queue removed successfully.\n");
    return 0;
}

