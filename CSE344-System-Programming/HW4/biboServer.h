#ifndef BIBOSERVER_H
#define BIBOSERVER_H

#define SERVER_NAME "/tmp/server_fifo"
#define BUFFER_SIZE 100
#define RESPONSE_SIZE 500


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <stdbool.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct{
    int target_pid; // server pid
    char path[BUFFER_SIZE]; // client fifo path 
    int pid; // client pid
    char request[BUFFER_SIZE]; // requst command
    bool connection;// connect or not connect
    char response[RESPONSE_SIZE]; // reponse buff
    char folder_path[BUFFER_SIZE]; // execute folder path
    char connect_type[BUFFER_SIZE]; // connect type

}client_request;





void lock_and_write(char* path,client_request data);
void execute_task(client_request client);

void list_command_handle(client_request client);

void readF_handle(client_request client);


void writeT_handle(client_request client);
void upload_handle(client_request client);
void download_handle(client_request client);
char	**str_split(char const *s, char c);
void write_file(char *path, char **parse_command, bool append);

void append_to_file(int fd, const char* data) ;
void write_line_file(int fd, int line, const char* data) ;
char* str_trim(char const *s1, char const *set);
void log_info(client_request client,char *data);

#endif
