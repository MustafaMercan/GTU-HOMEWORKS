#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
int dup (int fd);
int dup2 (int first_fd, int second_fd);


int main() {

    /*--------------------------------------------------------------------------*/

    char file_name_1 [] = "test1.txt";
    char file_name_2 [] = "test2.txt";
    char file_name_3 [] = "test3.txt";
    char buffer_dup_test [20];
    char buffer_dup2_test [20];


    int fd_1 = open(file_name_1, O_CREAT | O_RDWR | O_APPEND | O_TRUNC, 0644);
    int fd_2 = open(file_name_2, O_CREAT | O_RDWR | O_APPEND | O_TRUNC, 0644);
    int fd_3 = open(file_name_3, O_CREAT | O_RDWR | O_APPEND | O_TRUNC, 0644);


    write(fd_1,"test1\n",6);
    write(fd_2,"test2\n",6);
    write(fd_3,"test3\n",6);

    /*--------------------------------------------------------------------------*/

    printf("before nothing use function fd values:\n");

    printf("fd_1 -> %d\n",fd_1);
    printf("fd_2 -> %d\n",fd_2);
    printf("fd_3 -> %d\n",fd_3);

    /*--------------------------------------------------------------------------*/
    /*DUP FUNCTIONS TEST*/
    printf("\nDup Function\n\n");

    int dup_fd = dup(fd_1);
    
    write(dup_fd,"I'm dup fd\n",11);
    
    printf("dup_fd -> %d\n\n",dup_fd);
    
    lseek(dup_fd,0,SEEK_SET);
    
    read(dup_fd,buffer_dup_test,sizeof(buffer_dup_test));
    
    printf("test1.txt -> %s\n",buffer_dup_test);

    /*--------------------------------------------------------------------------*/

    /*DUP2 FUNCTIONS TEST*/
    printf("\nDup2 Function\n\n");

    int dup2_fd = dup2(fd_2,fd_3);
    
    write(dup2_fd,"I'm dup2 fd\n",12);
    
    printf("dup2_fd -> %d\n",dup2_fd);
    
    lseek(dup2_fd,0,SEEK_SET);
    
    read(dup2_fd,buffer_dup2_test,sizeof(buffer_dup2_test));
    
    printf("test2.txt -> %s\n",buffer_dup2_test);
    
/*--------------------------------------------------------------------------*/
    close(fd_1);
    close(fd_2);
    close(fd_3);
    close(dup_fd);
    close(dup2_fd);
    
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
