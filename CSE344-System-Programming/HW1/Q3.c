#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int dup (int fd);
int dup2 (int first_fd, int second_fd);
int main() {

    /*--------------------------------------------------------------------------*/
    /* For test With DUP function*/
    int fd1,dup_fd;
    char test_buffer[5];
    

    /* For test With DUP2 function*/
    int fd2,fd3,dup2_fd;
    char test_buffer_dup2[5];
    
    /*--------------------------------------------------------------------------*/
    /* TEST WITH DUP FUNCTION*/

    fd1 = open("file_1.txt", O_RDWR | O_CREAT, 0644);
    printf("---Test with dup function---\n\n");
    if (fd1 == -1) 
    {
        perror("open fail");
        exit(EXIT_FAILURE);
    }

    write(fd1, "test1", 5);

    dup_fd = dup(fd1);
    if (dup_fd == -1) 
    {
        perror("dup error");
        exit(EXIT_FAILURE);
    }

    off_t fd1_offset = lseek(fd1,0,SEEK_CUR);
    off_t dup_fd_offset = lseek(dup_fd,0,SEEK_CUR);
    if (fd1_offset == dup_fd_offset) 
    {
        printf("fd1 and dup_fd have the same file offset.\n");
        printf("fd1 offset-> %ld\ndup_fd offset-> %ld\n",fd1_offset,dup_fd_offset);
    } 
    else 
    {
        printf("File location is different.\n");
    }

    lseek(dup_fd, 0, SEEK_SET);
    write(dup_fd, "test1", sizeof(test_buffer));

    lseek(fd1, 0, SEEK_SET);
    read(fd1, test_buffer, sizeof(test_buffer));
    printf("fd1: %s\n", test_buffer);

    lseek(dup_fd, 0, SEEK_SET);
    read(dup_fd, test_buffer, sizeof(test_buffer));
    printf("dup_fd: %s\n", test_buffer);


    /*--------------------------------------------------------------------------*/
    /* TEST WITH DUP2 FUNCTION*/
    printf("\n---Test with dup2 function---\n\n");

    fd2 = open("file_2.txt", O_RDWR | O_CREAT, 0644);
    fd3 = open("file_3.txt", O_RDWR | O_CREAT, 0644);


    write(fd2,"test2",5);
    write(fd3,"test3",5);

    dup2_fd = dup2(fd2,fd3);

    off_t fd2_offset = lseek(fd2,0,SEEK_CUR);
    off_t fd3_offset = lseek(fd3,0,SEEK_CUR);
    off_t dup2_fd_offset = lseek(dup2_fd,0,SEEK_CUR);

    if(fd2_offset == dup2_fd_offset)
    {
        printf("fd2 and dup2_fd have the same file offset.\n");
        printf("fd2 offset-> %ld\nfd3 offset-> %ld\ndup2_fd offset -> %ld\n", fd2_offset,fd3_offset,dup2_fd_offset);
    }
    else
    {
        printf("fd2 and dup2_fd have the different file offset.\n");
        printf("fd2 offset-> %ld\nfd3 offset-> %ld\ndup2_fd offset -> %ld\n", fd2_offset,fd3_offset,dup2_fd_offset);
    }

    lseek(dup2_fd, 0, SEEK_SET);
    write(dup2_fd, "test2", sizeof(test_buffer_dup2));


    lseek(fd2, 0, SEEK_SET);
    read(fd2, test_buffer_dup2, sizeof(test_buffer_dup2));
    printf("fd2: %s\n", test_buffer_dup2);

    lseek(fd3, 0, SEEK_SET);
    read(fd3, test_buffer_dup2, sizeof(test_buffer_dup2));
    printf("fd3: %s\n", test_buffer_dup2);


    lseek(dup2_fd, 0, SEEK_SET);
    read(dup2_fd, test_buffer_dup2, sizeof(test_buffer_dup2));
    printf("dup2_fd: %s\n", test_buffer_dup2);

    close(fd1);
    close(fd2);
    close(fd3);
    close(dup2_fd);
    close(dup_fd);

    return 0;
}

int dup(int fd) {
    int newfd;
    newfd = fcntl(fd, F_DUPFD);
    if(newfd == -1)
    {
        perror("fcntl error");
        return -1;
    }
    return newfd;
}

int dup2(int first_fd, int second_fd)
{
    if(first_fd == second_fd)
    {
        if(fcntl(first_fd, F_GETFL) == -1)
        {
            errno = EBADF;
            return -1;
        }
        return first_fd;
    }
    
    if (fcntl(second_fd, F_GETFL) != -1)
    {
        if(close(second_fd) == -1)
            return -1;
    }

    int fd = fcntl(first_fd,F_DUPFD,second_fd);
    if(fd == -1)
        return -1;
    return fd;
}