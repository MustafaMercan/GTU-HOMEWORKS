#ifndef DROPBOX_H
#define DROPBOX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>
#include <limits.h>
#include <fcntl.h>

//server side
#define BUFFER_SIZE 1024
#define THREAD_POOL_SIZE 2

//client side

#define CLIENT_PATH "./client_file"
#define PATH_MAX_LENGTH 1000




typedef struct{
    int pid;
    char command[BUFFER_SIZE];
    char client[BUFFER_SIZE];
}ClientCommand;


typedef struct FileInfoNode FileInfoNode;

struct FileInfoNode{
    char file_path[1000];
    bool modified_flag;
    bool dir_or_not;
    bool deleted_or_not;
    bool other_side;
    bool added_new_or_not;
    int deleted_count;
    int added_count;
    int modified_count;
    FileInfoNode *next;
};
typedef struct{
    int count;
    FileInfoNode *root;
    pthread_mutex_t mutex;
    pthread_cond_t empty;
}FileInfo;


typedef struct{
    char path[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    bool done;
}sendDataInfoNode;







//server default konumdaki verileri okuyup oluşturcam


//create file



//kullanilanlar
void init_file_info(FileInfo *fileInfo);//+
void add_node_file_info(FileInfo *fileInfo, char *file_path, bool dir_or_not);//+
FileInfoNode* find_node(FileInfo *fileInfo, char *file_path);//+
void remove_node_file_info(FileInfo *fileInfo, char *file_path);//+
void client_path_init(FileInfo *fileInfo,char *path);//+
void print_file_info(FileInfo *fileInfo);//+


void listen_server_side(FileInfo *fileInfo,int clientSocket,char *path,char *server_path);
void read_data(FileInfo *fileInfo,int clientSocket,char *path,char *server_path);//+
void listen_dir(FileInfo *fileInfo,int clientSocket,char *path,bool flag);//+
void str_replace(char *str, const char *subStr, const char *replaceStr) ;//+
bool create_file_path(FileInfoNode clientNode,char *path,char *server_path);//+
void init_server_side(FileInfo *fileInfo,int clientSocket,char *path,char *server_path);//server'de güncel olarak bulunan verileri okur ilk olarak.

bool read_file_content(int clientSocket,char *path,char *server_path);//+
void delete_dir(char *path); //+
void detect_delete_file(FileInfo *fileInfo,char *path);//+
void update_data(FileInfo *fileInfo,char *file_name);
void    update_other_side(FileInfo *fileInfo,int sockfd);


#endif


