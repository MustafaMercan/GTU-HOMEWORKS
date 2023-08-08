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
#include <fcntl.h>

#include <stdbool.h>
#include <sys/stat.h>


//server side
#define BUFFER_SIZE 1024
#define PATH_MAX_LENGTH 1000



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
    char path[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    bool done;
}sendDataInfoNode;

typedef struct{
    int count;
    char file_path[1000];
    FileInfoNode *root;
    pthread_mutex_t mutex;
    pthread_cond_t empty;
}FileInfo;

typedef struct{
    int pid;
    char command[BUFFER_SIZE];
    char client[BUFFER_SIZE];
}ClientCommand;

typedef struct {
    ClientCommand clientCommand;
    int sockfd;
    int thread_pool_size;
    struct sockaddr_in client_address;
    struct RequestQueueNode* next;
} RequestQueueNode;


typedef struct {
    int current_client;
    int count;
    FileInfo *fileInfo;
    char file_path[1000];
    RequestQueueNode* front;
    RequestQueueNode* rear;
    pthread_mutex_t mutex;
    pthread_cond_t empty;
} RequestQueue;


//detect delete file güncellenecek fd kontrol edilecek
void detect_delete_file(FileInfo *fileInfo,char *path);


//File information staff
void init_file_info(FileInfo *fileInfo);//++

void server_path_init(FileInfo *fileInfo,char *path);//++

void add_node_file_info(FileInfo *fileInfo, char *file_path, bool dir_or_not);//++

void remove_node_file_info(FileInfo *fileInfo, char *file_path);//++

FileInfoNode* find_node(FileInfo *fileInfo, char *file_path);//++

void print_file_info(FileInfo *fileInfo);//++


//check directory
//void check_directory(FileInfo *fileInfo, int sockfd,char *path, int* current_file_count,bool flag,int client_count);


//send data staff
void init_other_side(FileInfo *fileInfo, RequestQueueNode *currentNode);//++

// Request Staff
void enqueueRequest(RequestQueue *requestQueue,ClientCommand clientCommand,int socked, struct sockaddr_in client_address,char *path,int pool_size);
void initializeRequestBuffer(RequestQueue *requestQueue,FileInfo *fileInfo,char *path);
RequestQueueNode* dequeueRequest(RequestQueue *requestQueue);

// Thread Handle
void* handleRequest(void *arg);

void listen_dir(FileInfo *fileInfo,int clientSocket,char *path,bool flag,int current_client);//++
void clear_path(FileInfo *fileInfo,int current_client);



//send file content
void send_file_content(FileInfoNode *iter,int sockfd);


void    update_other_side(FileInfo *fileInfo,int sockfd,int current_client);



void listen_client_side(FileInfo *fileInfo,int clientSocket,char *path);

void read_data(int clientSocket,char *path);

void str_replace(char *str, const char *subStr, const char *replaceStr);
void delete_dir(char *path); 


#endif