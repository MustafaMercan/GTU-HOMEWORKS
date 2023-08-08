#include "biboServer.h"
pthread_mutex_t mutex;
client_request client_data;
void queue_connect(int pid)
{
    client_data.connection = true;
}
void sigint_signal(int pid)
{
    if(client_data.connection == false)
    {
        printf("Client is terminating.\n");
        exit(1);
    }
    if(client_data.connection == true)
    {
        printf("Client is terminating... (in 3s)\n");
        kill(client_data.target_pid,SIGUSR1);
        sleep(3);
        exit(1);
    }
}

int main(int arg, char**args)
{


    printf("client pid -> %d\n",getpid());

    signal(SIGUSR1,queue_connect);
    signal(SIGINT, sigint_signal);

    if(arg < 2)
    {
        printf("invalid format\n");
        exit(1);
    }


    

    char client_fifo_path[BUFFER_SIZE];

    sprintf(client_fifo_path,"/tmp/client_%d",getpid()); //degiscek


    memcpy(client_data.connect_type,args[1],sizeof(client_data.connect_type));
    client_data.pid = getpid();
    client_data.connection = false;
    client_data.target_pid = atoi(args[2]);
    strcpy(client_data.path,client_fifo_path);



    char buffer[sizeof(client_request)];
    memcpy(buffer,&client_data,sizeof(client_request));
    // SERVER_NAME server fifo name
    lock_and_write(SERVER_NAME,client_data);

    sleep(1);

    int client_fifo_fd = open(client_fifo_path,O_RDONLY);
    if(client_fifo_fd < 0)
    {
        perror("client fifo error\n");
        exit(1);
    }

    read(client_fifo_fd,&client_data,sizeof(client_request));
    close(client_fifo_fd);

    if(strcmp(client_data.response,"connected") == 0)
    {
        printf("Client %s\n",client_data.response);
    }
    else if(strcmp(client_data.response,"queue") == 0)
    {
        printf("queue is full.\n");
        if(strcmp(client_data.connect_type,"tryConnect") == 0)
        {
            printf("client will be close\n");
            exit(1);
        }
        else if(strcmp(client_data.connect_type,"connect") == 0)
        {
            printf("Please wait.\n");
            pause();
        }
    }
    else
    {
        printf("Client %s\n",client_data.response);
        exit(1);
    }
    
    




    while(1)
    {
        usleep(1000);
        printf("Enter input: ");
        fflush(stdout);
    
        if (fgets(client_data.request, sizeof(client_data.request), stdin) != NULL)
        {
            client_data.request[strcspn(client_data.request, "\n")] = '\0';

            if(strcmp(client_data.request,"killServer") == 0)
            {
                printf("Server is terminating...\n");
                kill(client_data.target_pid,SIGUSR2);
            }
            lock_and_write(SERVER_NAME,client_data);
            
            if(strcmp(client_data.request,"quit") == 0)
            {        
                printf("Client is terminating... (in 3s)\n");
                //kill(client_data.target_pid,SIGUSR1);
                sleep(3);
                exit(1);
            }

            client_fifo_fd = open(client_fifo_path,O_RDONLY);
            
            printf("Waiting for process...\n");
            while(read(client_fifo_fd,&client_data,sizeof(client_data)) > 0)
            {
                printf("%s",client_data.response);
                usleep(10000);    
            }
            close(client_fifo_fd);
        }
    }



    return 0;
}