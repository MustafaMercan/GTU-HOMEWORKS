#include "dropbox.h"
void* handleRequest(void *arg)
{
    RequestQueue *requestQueue = (RequestQueue *)arg;

    char buffer[BUFFER_SIZE];
    int readBytes;
    int previous_count = requestQueue->count;
    FileInfo *fileInfo = requestQueue->fileInfo;





    //print_file_info(fileInfo);


    while (1) {

        printf("thread created\n");


        int current_file_count = 0;
        memset(buffer, 0, BUFFER_SIZE);
        //printf("komut bekliyorum\n");
        RequestQueueNode *currentNode;
        currentNode = dequeueRequest(requestQueue);
        if(previous_count >= currentNode->thread_pool_size)
            kill(currentNode->clientCommand.pid,SIGUSR1);
        
        requestQueue->current_client +=1;


    
        FileInfo fileInfo_2;
        init_file_info(&fileInfo_2);//create file info default

        //char path[] = "./server_file";
        server_path_init(&fileInfo_2,requestQueue->file_path);//reads server file
        
        int sockfd = currentNode->sockfd;
        printf("Socket -> %d\n",sockfd);


        init_other_side(&fileInfo_2,currentNode);//files send clients side
        sleep(3);

        //print_file_info(fileInfo);


        
        while(1)
        {
            //recv(sockfd,&buff,sizeof(buff),0);
            

            listen_dir(&fileInfo_2,sockfd,requestQueue->file_path,true,requestQueue->current_client);

            detect_delete_file(&fileInfo_2,requestQueue->file_path);
            
            update_other_side(&fileInfo_2,sockfd,requestQueue->current_client);
            
            clear_path(&fileInfo_2,requestQueue->current_client);



            listen_client_side(&fileInfo_2,sockfd,requestQueue->file_path); // update other side


            printf("All files updated\n");


            
            sleep(4);
        }

        close(sockfd);
        pthread_cond_signal(&requestQueue->empty);
        previous_count = requestQueue->count;
        requestQueue->count = requestQueue->count - 1;
    }

    pthread_exit(NULL);
}
