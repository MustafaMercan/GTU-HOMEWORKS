#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
int main (int arg, char** args)
{

    char *file_name;
    int num_bytes;
    int fd;
    int file_flags;
    int i = 0;

    if(arg < 3 || arg > 4)
    {
        printf("Incorrect usage format.\n");
        printf("Usage should be as follows: %s <filename> <num-bytes> [x]\n",args[0]);
        return 1;
    }
    
    file_name = args[1];
    num_bytes = atoi(args[2]);
    file_flags = O_WRONLY | O_CREAT;

    if(!(arg == 4 && (args[3][0] == 'x' || args[3][0] == 'X')))
        file_flags |= O_APPEND;

    fd = open(file_name,file_flags,0644);

    if(fd == -1)
    {
        perror("File could not be opened\n");
        return 0;
    }

    while(i < num_bytes)
    {
        if(arg == 4 && (args[3][0] == 'x' || args[3][0] == 'X'))
        {
            if(lseek(fd,0,SEEK_END) == -1)
            {
                perror("An error occured in the lseek function.");
                close(fd);
                return 1;
            }
        }
        if(write(fd," ", 1) == -1)
        {
            perror("An error occured in the write function.");
            close(fd);
            return 1;
        }
        i++;
    }
    close(fd);
    return 0;
}

