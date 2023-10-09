/*
============================================================================
Name : 27.c
Author : Aditi Singh
Description : Write a program to receive messages from the message queue.
a. with 0 as a flag
b. with IPC_NOWAIT as a flag
Date: 9th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    struct msg_buffer message;

    key_t key = ftok("message_queue_key", 'A');
    int msgqid = msgget(key, IPC_CREAT | 0666);
    
    // Receive the message from the queue with flag 0
    if (msgrcv(msgqid, &message, sizeof(message), 1, 0) == -1) {
        perror("msgrcv");
        return 1;
    }
    printf("Received Message with flag 0: %s", message.msg_text);

    // Receive the message from the queue with IPC_NOWAIT flag
    if (msgrcv(msgqid, &message, sizeof(message), 1, IPC_NOWAIT) == -1) {
        if (errno == ENOMSG) 
            printf("No message available in the queue.\n");
        else 
        {
            perror("msgrcv");
            return 1;
        }
    } 
    else 
        printf("Received Message with IPC_NOWAIT flag: %s", message.msg_text);

    return 0;
}

