/*
============================================================================
Name : 16.c
Author : Aditi Singh
Description : Write a program to perform mandatory locking.
a. Implement write lock
b. Implement read lock
Date: 28th Aug, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    const char *filename = argv[1];
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) 
    {
        perror("Error opening file");
        return 1;
    }

    struct flock write_lock;
    memset(&write_lock, 0, sizeof(struct flock));
    write_lock.l_type = F_WRLCK;
    write_lock.l_whence = SEEK_SET;
    write_lock.l_start = 0;
    write_lock.l_len = 0;

    if (fcntl(fd, F_SETLKW, &write_lock) == -1) 
    {
        perror("Error setting write lock");
        close(fd);
        return 1;
    }

    printf("Write lock acquired. Press Enter to release the lock...\n");
    getchar();

    write_lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &write_lock) == -1) 
    {
        perror("Error releasing write lock");
        close(fd);
        return 1;
    }
    printf("Write lock released.\n");

    struct flock read_lock;
    memset(&read_lock, 0, sizeof(struct flock));
    read_lock.l_type = F_RDLCK;

    if (fcntl(fd, F_SETLKW, &read_lock) == -1) 
    {
        perror("Error setting read lock");
        close(fd);
        return 1;
    }

    printf("Read lock acquired. Press Enter to release the lock...\n");
    getchar();
    read_lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &read_lock) == -1) 
    {
        perror("Error releasing read lock");
        close(fd);
        return 1;
    }
    printf("Read lock released.\n");
    close(fd);
    
    return 0;
}


