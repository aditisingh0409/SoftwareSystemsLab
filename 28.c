/*
============================================================================
Name : 28.c
Author : Aditi Singh
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date: 9th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("message_queue_key", 'A');
    int msgqid = msgget(key, IPC_CREAT | 0666);
    
    // Define the new permission using the msqid_ds structure
    struct msqid_ds queue_info;
    if (msgctl(msgqid, IPC_STAT, &queue_info) == -1) {
        perror("msgctl IPC_STAT");
        return 1;
    }

    // Change the permission values
    queue_info.msg_perm.uid = 1000;
    queue_info.msg_perm.gid = 1000;
    queue_info.msg_perm.mode = 0644;

    if (msgctl(msgqid, IPC_SET, &queue_info) == -1) {
        perror("msgctl IPC_SET");
        return 1;
    }
    printf("Message queue permission updated successfully.\n");
    return 0;
}

