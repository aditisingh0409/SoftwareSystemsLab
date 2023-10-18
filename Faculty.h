#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/socket.h>

int viewOffC(int clientSocket,char* auth) {
    char duff[1024];
    int fd = open("Courses.txt", O_RDONLY);
    if (fd == -1) 
    {
        perror("Error opening the file");
        return false;
    }
    
    int found = 0;
    char loginID[10];
    char courseID[10];
    struct course c;

    memset(loginID,0,sizeof(loginID)); 
    strcpy(loginID,auth);
 
    send(clientSocket, "Enter the Course ID\n", strlen("Enter the Course ID\n"), 0);
    int bytesRead = recv(clientSocket, courseID, sizeof(courseID) - 1, 0);
    if (bytesRead <= 0) 
    {
        perror("Error while receiving Login Id");
        return false;
    }
    courseID[bytesRead] = '\0';

    // Search for the course with the matching login ID
    while (read(fd, &c, sizeof(struct course)) > 0) 
    {
        if (strcmp(courseID,c.course_id) == 0) 
        {
            if(strcmp(loginID, c.prof_id)==0)
                found = 1;
            break;
        }
    }
    memset(duff,0,sizeof(duff));

    if(found)
    {
        // construct detailed message
        sprintf(duff,"\n--Required Details of course--\nCourse ID:%s\nCourse Name:%s\nDept:%s\nCourse Credit:%s\nTotal Seats:%s\nAvailable seats:%s\n",c.course_id,c.course_name,c.dept,c.course_credit,c.total_seats,c.avail_seats);
        send(clientSocket, duff, strlen(duff),0);
        close(fd);        
    }
    else
    {
        send(clientSocket, "Course not found..\n", strlen("Course not found..\n"), 0);
        close(fd);   
    }   
}

int addNewC(int clientSocket,char* auth) {
    struct course c;

    // Prompt and receive the course Id
    send(clientSocket, "Enter Course ID\n", strlen("Enter Course ID\n"), 0);
    int bytesRead = recv(clientSocket, c.course_id, sizeof(c.course_id) - 1, 0);
    if (bytesRead <= 0) {
        perror("Error while receiving Login Id");
        return false;
    }
    c.course_id[bytesRead] = '\0';
   
    strcpy(c.prof_id,auth);
    
    send(clientSocket, "Enter Course Name\n", strlen("Enter Course Name\n"), 0);
    bytesRead = recv(clientSocket, c.course_name, sizeof(c.course_name) - 1, 0);
    if (bytesRead <= 0) 
    {
        perror("Error while receiving Department");
        return false;
    }
    c.course_name[bytesRead] = '\0';

    // Prompt and receive Dept
    send(clientSocket, "Enter Department\n", strlen("Enter Department\n"), 0);
    bytesRead = recv(clientSocket, c.dept, sizeof(c.dept) - 1, 0);
    if (bytesRead <= 0) 
    {
        perror("Error while receiving Name");
        return false;
    }
    c.dept[bytesRead] = '\0';

    // Prompt and receive course credit
    send(clientSocket, "Enter Credit for the Course\n", strlen("Enter Credit for the Course\n"), 0);
    bytesRead = recv(clientSocket, c.course_credit, sizeof(c.course_credit) - 1, 0);
    if (bytesRead <= 0) 
    {
        perror("Error while receiving Age");
        return false;
    }
    c.course_credit[bytesRead] = '\0';

    // Prompt and receive total seats
    send(clientSocket, "Enter Total No. of Seats for the Course\n", strlen("Enter Total No. of Seats for the Course\n"), 0);
    bytesRead = recv(clientSocket, c.total_seats, sizeof(c.total_seats) - 1, 0);
    if (bytesRead <= 0) 
    {
        perror("Error while receiving Email");
        return false;
    }
    c.total_seats[bytesRead] = '\0';

    // Prompt and receive total seats
    send(clientSocket, "Enter Available No. of Seats for the Course\n", strlen("Enter Available No. of Seats for the Course\n"), 0);
    bytesRead = recv(clientSocket, c.avail_seats, sizeof(c.avail_seats) - 1, 0);
    if (bytesRead <= 0) 
    {
        perror("Error while receiving Email");
        return false;
    }
    c.avail_seats[bytesRead] = '\0';

    // Open the file to enter this data in the database
    int fd = open("Courses.txt", O_WRONLY | O_APPEND | O_CREAT, 0666); // Open the file in append mode
    if (fd == -1) 
    {
        perror("Error opening the file");
        return false;
    }

    // Use flock to apply a mandatory lock
    if (flock(fd, LOCK_EX) == -1) 
    {
        perror("Error applying lock");
        close(fd);
        return false;
    }

    // Write the structure data to the file
    if (write(fd, &c, sizeof(struct course)) == -1) 
    {
        perror("Error writing to the file");
        flock(fd, LOCK_UN); // Release the lock before closing the file
        close(fd);
        send(clientSocket, "Failed to add Course\n", strlen("Failed to add Course\n"), 0);
    }
    else
    {
        flock(fd, LOCK_UN); // Release the lock
        close(fd);          // Close the file
        send(clientSocket, "Course adeed successfully\n", strlen("Course adeed successfully\n"), 0);
    }
}

int updateCrsDtls(int clientSocket,char* auth){
    struct course my_course, temp;
    int fd = open("Courses.txt", O_RDWR, 0644); // Open in read-only mode
    struct flock lock;
    if (fd == -1)
    {
        perror("Error opening file");
        return 0;
    }
    bool found = false; // Initialize found to false
    char buffer[1024];  // Declare buffer for sending data
    send(clientSocket, "Enter Course ID for updation of details: ", strlen("Enter Course ID for updation of details: "), 0);
    int readResult = read(clientSocket, my_course.course_id, sizeof(my_course.course_id) - 1);

    if (readResult <= 0)
    {
        send(clientSocket, "Error receiving student ID from server", strlen("Error receiving student ID from server"), 0);
        return 0;
    }
    my_course.course_id[readResult] = '\0';

    // Reset the file pointer to the beginning of the file
    lseek(fd, 0, SEEK_SET);

    // Loop to search for the Course in the file
    while (read(fd, &temp, sizeof(temp)) > 0)
    {
        if (strcmp(my_course.course_id, temp.course_id) == 0)
        { // Compare the Course IDs
            found = true;
            
            lock.l_type = F_WRLCK;  // Write (exclusive) lock
            lock.l_whence = SEEK_SET;
            lock.l_start = lseek(fd, 0, SEEK_CUR) - sizeof(struct course); // Position lock at the current record
            lock.l_len = sizeof(struct course);

            if (fcntl(fd, F_SETLKW, &lock) == -1)
            {
                perror("Error locking file");
                lock.l_type = F_UNLCK;
                fcntl(fd, F_SETLK, &lock);
                close(fd);
                return 0;
            }
            break;
        }
    }
    if (found)
    {
        // Construct the details message
        sprintf(buffer, "...................Course..................\n...................Original Details ..................\nCourse ID:%s\nCourse Name:%s\nDept:%s\nCourse Credit:%s\nTotal Seats:%s\nAvailable seats:%s\n.............................................\n",
        temp.course_id,temp.course_name,temp.dept,temp.course_credit,temp.total_seats,temp.avail_seats );

        // Send the details to the client
        send(clientSocket, buffer, strlen(buffer), 0);
        
        struct course up_crs;
        strcpy(up_crs.course_id, temp.course_id);

        strcpy(up_crs.prof_id, temp.prof_id);


        send(clientSocket, "Enter Course Name to update: ", strlen("Enter Course Name to update: "), 0);
        readResult = read(clientSocket, up_crs.course_name, sizeof(up_crs.course_name) - 1);
        up_crs.course_name[readResult]='\0';

        send(clientSocket, "Enter Department to update: ", strlen("Enter Department to update: "), 0);
        readResult = read(clientSocket, up_crs.dept, sizeof(up_crs.dept) - 1);
        up_crs.dept[readResult]='\0';

        send(clientSocket, "Enter Credit to update: ", strlen("Enter Credit to update: "), 0);
        readResult = read(clientSocket, up_crs.course_credit, sizeof(up_crs.course_credit) - 1);
        up_crs.course_credit[readResult]='\0';

        send(clientSocket, "Enter Total Seats to update: ", strlen("Enter Total Seats to update: "), 0);
        readResult = read(clientSocket, up_crs.total_seats, sizeof(up_crs.total_seats) - 1);
        up_crs.total_seats[readResult]='\0';

        send(clientSocket, "Enter Available Seats to update: ", strlen("Enter Available Seats to update: "), 0);
        readResult = read(clientSocket, up_crs.avail_seats, sizeof(up_crs.avail_seats) - 1);
        up_crs.avail_seats[readResult]='\0';

        lseek(fd,-sizeof(struct course),SEEK_CUR); //// Move the file pointer back to the beginning of the current record
        write(fd,&up_crs,sizeof(up_crs));// Overwrite the entire record with the updated data

        sprintf(buffer, "...................Course..................\n...................Updated Details ..................\nCourse ID:%s\nCourse Name:%s\nDept:%s\nCourse Credit:%s\nTotal Seats:%s\nAvailable seats:%s\n.............................................",
                up_crs.course_id,up_crs.course_name,up_crs.dept,up_crs.course_credit,up_crs.total_seats,up_crs.avail_seats );
       
        // Send the details to the client
        send(clientSocket, buffer, strlen(buffer), 0);
        //struct flock unlock;
        lock.l_type = F_UNLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = lock.l_start;
        lock.l_len = lock.l_len;
        fcntl(fd, F_SETLK, &lock);
        close(fd);
        send(clientSocket, "Course Updated Successfully\n", strlen("Course Updated Successfully\n"), 0);
    }
    else
    {
        send(clientSocket, "Course not found\n", strlen("Course not found\n"), 0);
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        close(fd);       
    }
    close(fd);
}

int updatePass(int clientSocket,char* auth) {
    char buff[1024];
    int fd = open("Faculties.txt", O_RDWR); // Open the file for both reading and writing
    if (fd == -1) 
    {
        perror("Error opening the file");
        return false;
    }

    int found = 0;
    char loginID[50];
    char newPass[10];
    struct faculty f;

    memset(loginID, 0, sizeof(loginID));

    strcpy(loginID,auth);

    // Search for the faculty with the matching login ID
    while (read(fd, &f, sizeof(struct faculty)) > 0) 
    {
        if (strcmp(loginID, f.login_id) == 0) 
        {
            found = 1;
            break;
        }
    }

    if (found) 
    {
        // Send a prompt for the new password
        send(clientSocket, "Enter New Password: ", strlen("Enter New Password: "), 0);
        int bytesRead = recv(clientSocket, newPass, sizeof(newPass) - 1, 0);
        if (bytesRead <= 0) 
        {
            perror("Error while receiving new password");
            close(fd); // Close the file
            return false;
        }
        newPass[bytesRead] = '\0';

        // Update the faculty's password
        strcpy(f.password, newPass);

        // Seek back to the beginning of the faculty record
        lseek(fd, -sizeof(struct faculty), SEEK_CUR);

        // Write the updated faculty data to the file
        if (write(fd, &f, sizeof(struct faculty)) == -1) 
        {
            perror("Error writing to the file");
            send(clientSocket, "Failed to update Password.\n", strlen("Failed to update Password.\n"), 0);
            close(fd); // Close the file           
        }
        close(fd); // Close the file
        send(clientSocket, "Password updated successfully.\n", strlen("Password updated successfully.\n"), 0);       
    } 
    else 
    {
        send(clientSocket, "Faculty not found.\n", strlen("Faculty not found.\n"), 0);
        close(fd); 
    }
}

char* faculty_Authentication(int client_socket) {
    char loginId[100];
    char pass[100];

    // Send a prompt for the username
    const char *uname_msg = "\nEnter loginID of Professor: ";
    send(client_socket, uname_msg, strlen(uname_msg), 0);

    // Receive the username from the client
    ssize_t bytesRead = recv(client_socket, loginId, sizeof(loginId), 0);
    if (bytesRead <= 0) 
    {
        close(client_socket);
        return false;
    }
    if (loginId[bytesRead - 1] == '\n') 
        loginId[bytesRead - 1] = '\0';
    else 
        loginId[bytesRead] = '\0';

    // Send a prompt for the password
    const char *pswd_msg = "\nEnter password of the Professor: ";
    send(client_socket, pswd_msg, strlen(pswd_msg), 0);

    // Receive the password from the client
    bytesRead = recv(client_socket, pass, sizeof(pass), 0);
    if (bytesRead <= 0) 
    {
        close(client_socket);
        return false;
    }
    if (pass[bytesRead - 1] == '\n') 
        pass[bytesRead - 1] = '\0';
    else
        pass[bytesRead] = '\0';

    struct faculty f;
    int fd = open("Faculties.txt", O_RDONLY);
    if (fd == -1) 
    {
        perror("Error opening the file");
        return false;
    }
    int found = 0;
    while (read(fd, &f, sizeof(struct faculty)) > 0) 
    {
        if (strcmp(loginId, f.login_id) == 0) 
        {
            if(strcmp(pass,f.password ) ==0)
            {
                char* loginIdCopy = (char*)malloc(strlen(loginId) + 1);
                if (loginIdCopy != NULL) 
                {
                    strcpy(loginIdCopy,loginId);
                    close(fd);
                    return loginIdCopy;
                }
            }
        }
    }
    return NULL;    
}

int removeCourse(int clientSocket,char* auth) {
    struct course my_course, temp;
    int openFD = open("Courses.txt", O_RDWR, 0644); // Open in read-only mode

    if (openFD == -1)
    {
        perror("Error opening file");
        return 0;
    }
    bool found = false; // Initialize found to false
    char buffer[1024];  // Declare buffer for sending data
    send(clientSocket, "Enter Course ID to Remove: ", strlen("Enter Course ID to Remove: "), 0);
    int readResult = read(clientSocket, my_course.course_id, sizeof(my_course.course_id) - 1);
    
    if (readResult <= 0)
    {
        send(clientSocket, "Error receiving faculty ID from server", strlen("Error receiving faculty ID from server"), 0);
        return 0;
    }
    my_course.course_id[readResult] = '\0';
    
    // Reset the file pointer to the beginning of the file
    lseek(openFD, 0, SEEK_SET);
    strcpy(my_course.prof_id,auth);
    // Loop to search for the student in the file
    while (read(openFD, &temp, sizeof(temp)) > 0)
    {
        if((strcmp(my_course.course_id, temp.course_id) == 0) && (strcmp(my_course.prof_id, temp.prof_id) == 0))
        { 
            // Compare the student IDs
            found = true;            
            break;
        }
    }
    
    lseek(openFD,-sizeof(struct course),SEEK_CUR);
    size_t bytesWrite=write(openFD,&temp,sizeof(temp));
    if(bytesWrite==-1)
    {
        perror("Error while removing course");
        close(openFD);
        return 0;
    }
    if (found)
    {
        send(clientSocket, "Removed the course from catalog\n", strlen("Removed the course from catalog\n"), 0);
        close(openFD);
        return 1;
    }
    else
    {
        send(clientSocket, "Course not found\n", strlen("Course not found\n"), 0);
        close(openFD);
        return 0;
    }
    return 0; 
}

int faculty_Fun(int client_socket, char* auth) {
    char faculty_Menu[] = "\nFaculty Menu:\n1. Add New Course\n2. View Offering Course\n3. Update Course Details\n4. Change Password\n5. Remove Course\n6. Exit\nEnter Choice\n";

    while (1) 
    {
        send(client_socket, faculty_Menu, strlen(faculty_Menu), 0);
        char choice_buffer[10];
        ssize_t bytesRead = recv(client_socket, choice_buffer, sizeof(choice_buffer), 0);

        if (bytesRead <= 0) 
        {
            perror("Error receiving admin menu choice");
            close(client_socket);
            return false;
        }

        int choice = atoi(choice_buffer);
        switch (choice) 
        {
            case 1:
                addNewC(client_socket,auth);
                break;
            case 2:
                viewOffC(client_socket,auth); 
                break;
            case 3:
                updateCrsDtls(client_socket,auth);
                break;
            case 4:
                updatePass(client_socket,auth);
                break;
            case 5:
                removeCourse(client_socket,auth);
                break;
            case 6:
                return true;
            default:
                send(client_socket, "Invalid choice. Try again.\n", strlen("Invalid choice. Try again.\n"), 0);
                break;
        }
    }
}


