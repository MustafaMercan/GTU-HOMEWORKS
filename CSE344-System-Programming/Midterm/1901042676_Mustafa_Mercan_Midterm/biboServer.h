#ifndef BIBOSERVER_H
#define BIBOSERVER_H


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


#define BUFFER_SIZE 128
#define PIPE_NAME "my_pipe"


bool check_substr(const char* str, const char* word);
char	**str_split(char const *s, char c);
void write_data_fifo(char* fifo_name,char *data);
void lock_and_write(char* fifo_name,char* path, char** parse_command,bool append);


void append_to_file(int fd, const char* data) ;
void write_line_file(int fd,int line,const char* data);
void queue_connect(int pid);
int shiftArray(int arr[], int size) ;
char* str_trim(char const *s1, char const *set);

void upload_handle(char* command, const char* folder_name, char* client_pipe_name);
void download_handle(char* command, const char* folder_name, char* client_pipe_name);
void writeT_handle(char* command, const char* folder_name, char* client_pipe_name);
void readF_handle(char* command, const char* folder_name, char* client_pipe_name);
void list_command_handle(const char* folder_name, char* client_pipe_name); // global olarak çalışması istendiğinde path değişecek.

#endif