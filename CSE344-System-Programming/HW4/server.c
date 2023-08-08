#include "biboServer.h"

int pool_size;
int max_client_number;


int current_process;
int current_client = 0;


pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;

client_request task_queue[256];
client_request clients[256];
client_request client_queue_wait[256];

int queue_size = 0;
int task_count = 0;
int client_index = 0;

int server_log;

void decrease_client(int pid)
{
    if(queue_size != 0)
    {
        kill(client_queue_wait[0].pid,SIGUSR1);
        int i = 0;
        for(i = 0; i < queue_size - 1; i++)
        {
            client_queue_wait[i] = client_queue_wait[i+1];
        }
        queue_size--;
    }
    printf("Client disconnect\n");

    current_client-=1;
}

void quit_signal(int pid)
{

    if(client_index != 0)
    {
        int i;
        for(i = 0 ; i < client_index ; i++)
        {
            kill(clients[i].pid,SIGTERM);
            unlink(clients[i].path);
        }
    }
    usleep(500);
    unlink(SERVER_NAME);

    exit(1);


}

void execute_task(client_request client)
{

    char **commands = str_split(client.request,' ');

    if(strcmp(client.request,"help") == 0)
    {
        char availableComments[] = "Available comments are :help, list, readF, writeT, upload, download, quit, killServer\n";
        strcpy(client.response,availableComments);
        lock_and_write(client.path,client);
    }
    else if(strcmp(client.request,"list") == 0)
    {
        list_command_handle(client);
    }
    else if(strcmp(commands[0],"readF") == 0)
    {
        readF_handle(client);
    }
    else if(strcmp(commands[0],"writeT") == 0)
    {
        writeT_handle(client);
    }
    else if(strcmp(commands[0],"upload") == 0)
    {
        upload_handle(client);
    }
    else if(strcmp(commands[0],"download") == 0)
    {
        download_handle(client);
    }
    else if(strcmp(commands[0],"quit") == 0)
    {
        log_info(client,"disconnect");

        if(queue_size != 0)
        {
            kill(client_queue_wait[0].pid,SIGUSR1);
            int i = 0;
            for(i = 0; i < queue_size - 1; i++)
            {
                client_queue_wait[i] = client_queue_wait[i+1];
            }
            queue_size--;
        }
        current_client--;
        printf("client %d is disconnected server\n",client.pid);
    }
    else
    {
        char availableComments[] = "The command was not found. Use the 'help' command to see all available commands.";
        strcpy(client.response,availableComments);
        lock_and_write(client.path,client);
    }

}

void *process(void *args)
{
    while(1)
    {
        client_request client;
        pthread_mutex_lock(&mutexQueue);
        while(task_count == 0)
        {
            pthread_cond_wait(&condQueue,&mutexQueue);

        }
        client = task_queue[0];
        int i = 0;
        for(i = 0; i < task_count - 1; i++)
        {
            task_queue[i] = task_queue[i+1];
        }
        task_count--;

        pthread_mutex_unlock(&mutexQueue);
        execute_task(client);
    }
}

int main(int arg, char **args)
{
    current_process = 0;

    signal(SIGUSR1,decrease_client);
    signal(SIGUSR2,quit_signal);
    signal(SIGINT, quit_signal);




    client_request client_data;
    if (arg < 4) {
        printf("Please run the program in the correct format. The correct format is: biboServer <dirname> <max. #ofClients> <pool size>\n");

        return 1;
    }
    max_client_number = atoi(args[2]);



   
    pool_size = atoi(args[3]);
    if(pool_size <= 0 || max_client_number <= 0)
    {
            printf("Please enter a positive integer value greater than 0.\n");
            exit(1);
    }

    struct stat st;
    const char* folder_name = args[1];
    int result = stat(folder_name, &st);
    if (result == 0 && S_ISDIR(st.st_mode)) {
        printf("The directory exists in this path. The server will be started.\n");
    }
    else {
        result = mkdir(folder_name, 0777);
        if (result == 0)
            printf("The directory has been created.\n");
    }

    printf("Server started PID :%d\n",getpid());

    pthread_t threads[pool_size];

    pthread_mutex_init(&mutexQueue, NULL);
    pthread_cond_init(&condQueue, NULL);




    
    mkfifo(SERVER_NAME, 0666);


    int i;
    for(i = 0 ; i < pool_size; i++)
    {
        pthread_create(&threads[i],NULL,process,NULL);
    }

    while(1)
    {
        int server_fifo_fd = open(SERVER_NAME,O_RDONLY);
        if(server_fifo_fd < 0 )
        {
            perror("server fifo cant open!\n");
            return 1;
        }
        read(server_fifo_fd, &client_data,sizeof(client_request));
        close(server_fifo_fd);
        usleep(500);

        if(client_data.connection == false)
        {
            mkfifo(client_data.path,0666);

        }
        if(client_data.target_pid == getpid() && client_data.connection == false)
        {
            
            usleep(500);
            if(current_client >= max_client_number)
            {
                if(strcmp(client_data.connect_type,"connect") == 0 || strcmp(client_data.connect_type,"tryConnect") == 0)
                {
                    client_data.connection = false;
                    strcpy(client_data.response,"queue");
                    sprintf(client_data.folder_path,"./%s",folder_name);
                    printf("Queue is full.\n");
                    lock_and_write(client_data.path,client_data);
                    client_queue_wait[queue_size] = client_data;

                    queue_size++;
                }
            }
            else
            {
                
                current_client++;
                client_data.connection = true;
                strcpy(client_data.response,"connected"); 
                sprintf(client_data.folder_path,"./%s",folder_name);
                lock_and_write(client_data.path,client_data);
                printf("client PID: %d connected\n",client_data.pid);
                clients[client_index] = client_data;
                client_index++;

                log_info(client_data,"connect");
            }


        }
        else if (client_data.target_pid != getpid())
        {
            usleep(200);
            client_data.connection = false;
            strcpy(client_data.response,"not connected");
            lock_and_write(client_data.path,client_data);
        }
        else if(client_data.target_pid == getpid() && client_data.connection == true)
        {
            task_queue[task_count] = client_data;
            task_count++;
            if(task_count != 0)
            {
                pthread_cond_signal(&condQueue);
            }
        }
    }

    







    return 0;
}