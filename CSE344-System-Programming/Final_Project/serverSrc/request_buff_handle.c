#include "dropbox.h"

void initializeRequestBuffer(RequestQueue *requestQueue,FileInfo *fileInfo,char *path)
{
    snprintf(requestQueue->file_path,sizeof(requestQueue->file_path),"%s",path);
    requestQueue->current_client = 0;
    requestQueue->fileInfo = fileInfo;
    requestQueue->front = NULL;
    requestQueue->rear = NULL;
    requestQueue->count = 0;
    pthread_mutex_init(&requestQueue->mutex, NULL);
    pthread_cond_init(&requestQueue->empty, NULL);
}

void enqueueRequest(RequestQueue *requestQueue,ClientCommand clientCommand,int socked, struct sockaddr_in client_address,char *path,int pool_size)
{
    RequestQueueNode* newNode = (RequestQueueNode*) malloc(sizeof(RequestQueueNode));
    
    strncpy(newNode->clientCommand.command, clientCommand.command, BUFFER_SIZE);
    newNode->clientCommand.pid = clientCommand.pid;
    newNode->thread_pool_size = pool_size;
    newNode->next = NULL;
    newNode->sockfd = socked;
    newNode->client_address = client_address;

    sendDataInfoNode send_data;
    char serialized_data[sizeof(send_data)];
    memset(&send_data,0,sizeof(send_data));
    memset(serialized_data,0,sizeof(serialized_data));

    snprintf(send_data.path,sizeof(send_data.path),"%s",path);


    pthread_mutex_lock(&requestQueue->mutex);

    if (requestQueue->front == NULL) {
        requestQueue->front = newNode;
        requestQueue->rear = newNode;
    } else {
        requestQueue->rear->next =(struct RequestQueueNode *)  newNode;
        requestQueue->rear = newNode;
    }
    requestQueue->count++;
    
    if(requestQueue->count > pool_size )
    {
        snprintf(send_data.buffer,sizeof(send_data.buffer),"Thread pool is full. Please wait.");
        memcpy(serialized_data,&send_data,sizeof(serialized_data));
        send(newNode->sockfd, serialized_data, sizeof(serialized_data), 0);
    }
    else
    {
        snprintf(send_data.buffer,sizeof(send_data.buffer),"Connection is success.");
        memcpy(serialized_data,&send_data,sizeof(serialized_data));
        send(newNode->sockfd, serialized_data, sizeof(serialized_data), 0);
    }

    pthread_cond_signal(&requestQueue->empty);
    pthread_mutex_unlock(&requestQueue->mutex);
}

RequestQueueNode* dequeueRequest(RequestQueue *requestQueue) 
{
    pthread_mutex_lock(&requestQueue->mutex);

    while (requestQueue->front == NULL) {
        pthread_cond_wait(&requestQueue->empty, &requestQueue->mutex);
    }

    RequestQueueNode* frontNode = requestQueue->front;
    requestQueue->front =  (RequestQueueNode*) requestQueue->front->next;

    pthread_mutex_unlock(&requestQueue->mutex);

    return frontNode;
}