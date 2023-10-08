#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe1[2]; 
    int pipe2[2]; 
    
    char childmsg[] = "Hello Child! -From Parent";
    char parentmsg[] = "Hello Parent! -From Child";

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
        perror("Pipe creation failed");

    pid_t child_pid = fork();

    if (child_pid == -1) 
        perror("Fork failed");

    if (child_pid == 0) 
    { 
        // Child Process
        close(pipe1[1]); 
        close(pipe2[0]); 
        char receivedmsg[30]; 

        // Read from parent through pipe1
        if (read(pipe1[0], receivedmsg, sizeof(receivedmsg)) == -1) 
            perror("Read from pipe1 failed in child");

        printf("Child received from parent: %s\n", receivedmsg);

        // Send a message to parent through pipe2
        if (write(pipe2[1], parentmsg, strlen(parentmsg) + 1) == -1)
            perror("Write to pipe2 failed in child");

        close(pipe1[0]);
        close(pipe2[1]);
    } 
    else 
    {
        // Parent Process
        close(pipe1[0]); 
        close(pipe2[1]);

        // Send a message to child through pipe1
        if (write(pipe1[1], childmsg, strlen(childmsg) + 1) == -1)
            perror("Write to pipe1 failed in parent");

        char receivedmsg[30]; 

        // Read from child through pipe2
        if (read(pipe2[0], receivedmsg, sizeof(receivedmsg)) == -1)
            perror("Read from pipe2 failed in parent");

        printf("Parent received from child: %s\n", receivedmsg);

        close(pipe1[1]); 
        close(pipe2[0]);
    }

    return 0;
}

