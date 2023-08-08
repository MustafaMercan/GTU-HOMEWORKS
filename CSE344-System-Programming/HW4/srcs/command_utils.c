#include "../biboServer.h"

void lock_and_write(char* path,client_request data)
{

    int fd = open(path,O_WRONLY);
    if(fd < 0)
    {
        perror("server fifo can't found!");
        exit(1);
    }

    char buffer[sizeof(client_request)];
    memcpy(buffer,&data,sizeof(client_request));


    struct flock lock;
    lock.l_type = F_WRLCK; // Yazma kilidi
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;


    if (fcntl(fd, F_SETLKW, &lock) == -1) 
    {
        printf("The file can't locked\n");
        close(fd);
        return ;
    }

    write(fd,&data,sizeof(client_request));

    lock.l_type = F_UNLCK;
    
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        printf("The file locked can't be freed\n");
        close(fd);
        return;
    }

    close(fd);
}
void log_info(client_request client,char *data)
{
    char log_information[BUFFER_SIZE];
    char log_path[BUFFER_SIZE];
    
    sprintf(log_path,"./logs/%d_server.log",client.target_pid);

    int fd = open(log_path,O_WRONLY | O_CREAT | O_APPEND, 0644);
    if(fd == -1)
    {
        perror("Log can't created \n");
        return;
    }
    if(strcmp(data,"connect") == 0)
    {
        sprintf(log_information,"Client_%d connected the server.\n",client.pid);
        write(fd,log_information,strlen(log_information));
    }
    else if(strcmp(data,"disconnect") == 0)
    {
        sprintf(log_information,"Client_%d disconnected the server.\n",client.pid);
        write(fd,log_information,strlen(log_information));
    }
    close(fd);



}
void write_file(char *path, char **parse_command, bool append)
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
        free(clear_str);
    }
    else
    {
        char *clear_str = str_trim(parse_command[3],"\"");
        write_line_file(fd,atoi(parse_command[2]),clear_str);
        free(clear_str);
    }
    close(fd);

}
void append_to_file(int fd, const char* data) 
{
    write(fd,"\n",1);
    int write_size = write(fd,data,strlen(data));
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




