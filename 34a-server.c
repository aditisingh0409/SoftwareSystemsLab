/*
============================================================================
Name : 34.c
Author : Aditi Singh
Description : Write a program to create a concurrent server.
a. use fork
b. use pthread_create
Date: 10th Oct, 2023.
============================================================================
*/

#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <stdio.h>      
#include <unistd.h>     

void main()
{
    int socketFD, connectionFD, bindStatus, listenStatus, clientSize;
    struct sockaddr_in address, client;
    ssize_t readBytes, writeBytes;
    char buffer[100];

    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD == -1)
    {
        perror("Error while creating socket!");
        _exit(0);
    }
    printf("Server side socket successfully created!\n");

    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    bindStatus = bind(socketFD, (struct sockaddr *)&address, sizeof(address));
    if (bindStatus == -1)
    {
        perror("Error while binding name to socket!");
        _exit(0);
    }
    printf("Binding to socket was successful!\n");

    listenStatus = listen(socketFD, 2);
    if (listenStatus == -1)
    {
        perror("Error while trying to listen for connections!");
        _exit(0);
    }
    printf("Now listening for connections on a socket!\n");
    while (1)
    {
        clientSize = (int)sizeof(client);
        connectionFD = accept(socketFD, (struct sockaddr *)&client, &clientSize);
        if (connectionFD == -1)
            perror("Error while accepting a connection!");
        else
        {
            // Server - Client Communication
            if (fork() == 0)
            {
                // Child
                writeBytes = write(connectionFD, "I'm the server!", 15);
                if (writeBytes == -1)
                    perror("Error while writing to network via socket!");
                else
                    printf("Data sent to client!\n");

                readBytes = read(connectionFD, buffer, 100);
                if (readBytes == -1)
                    perror("Error while reading from network via socket!");
                else
                    printf("Data from client: %s\n", buffer);
            }
            else
            {
                // Parent
                close(connectionFD);
            }
        }
    }
    close(socketFD);
}
