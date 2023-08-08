#include "../biboServer.h"

void write_data_fifo(char* fifo_name,char *data)
{
	int fifo_fd;
	fifo_fd = open(fifo_name,O_WRONLY);
    //printf("fifo name -> %s\n",fifo_name);
	if(fifo_fd < 0)
	{
		perror("write data fifo function was failed\n");
		exit(1);
	}
	write(fifo_fd,data,strlen(data));

	close(fifo_fd);
}



void append_to_file(int fd, const char* data) 
{
    int write_size = write(fd,data,strlen(data));
    write(fd,"\n",1);
}

void write_line_file(int fd, int line, const char* data) 
{
    char buffer[1000];
    int current_line = 1;
    int offset = 0;
    int bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) 
    {
        for (int i = 0; i < bytes_read; i++) 
        {
            if (buffer[i] == '\n') 
            {
                current_line++;
            }
            if (current_line == line) 
            {
                int remaining_bytes = bytes_read - i;
                lseek(fd, offset + i, SEEK_SET);
                write(fd,"\n",1);
                write(fd, data, strlen(data));
                write(fd, buffer + i, remaining_bytes);
                return;
            }
        }
        offset += bytes_read;
    }
}


void lock_and_write(char* fifo_name,char* path, char** parse_command,bool append)
{
    int fd;
    if(append)
    {
        fd = open(path,O_WRONLY | O_CREAT | O_APPEND);

        if (fd == -1) 
        {
            printf("open error");
            return;
        }
    }
    else
    {
        fd = open(path,O_RDWR);
        if (fd == -1) 
        {
            printf("open error");
            return;
        }
    }
    if(append)
    {
        char *clear_str = str_trim(parse_command[2],"\"");
        append_to_file(fd,clear_str);
        write_data_fifo(fifo_name,"The operation has been completed.");
        free(clear_str);
    }
    else
    {
        char *clear_str = str_trim(parse_command[3],"\"");
        write_line_file(fd,atoi(parse_command[2]),clear_str);
        write_data_fifo(fifo_name,"The operation has been completed.");
        free(clear_str);
    }
    close(fd);
}

