/*
============================================================================
Name : 20.c
Author : Aditi Singh
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 8th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    if (mkfifo("myfifo", 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    int fd = open("myfifo", O_WRONLY);
    char msg[30];
    printf("Enter text to send: ");
    scanf("%[^\n]", msg);
    write(fd, msg, strlen(msg));
    close(fd);

    printf("Sender: Message sent to FIFO\n");
    return 0;
}

