/*
============================================================================
Name : 26.c
Author : Aditi Singh
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 9th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    struct msg_buffer message;

    key_t key = ftok("message_queue_key", 'A');
    int msgqid = msgget(key, IPC_CREAT | 0666);
    
    printf("Enter a message: ");
    fgets(message.msg_text, sizeof(message.msg_text), stdin);
    message.msg_type = 1;

    // Send the message to the queue
    if (msgsnd(msgqid, &message, sizeof(message), 0) == -1) {
        perror("msgsnd");
        return 1;
    }
    printf("Message sent to the queue.\n");

    return 0;
}

