#include "biboServer.h"
int server_pid = -1;
char connect_type[BUFFER_SIZE]; 

void quit_signal(int signal)
{
    printf("Ctrl+C signal received. Terminating the program.\n");
    if(server_pid != -1)
    {
        kill(server_pid,SIGUSR1);
    }
    exit(1);
}

void queue_connect(int pid)
{
    if(pid == SIGUSR1)
    {
        if(strcmp(connect_type,"connect") == 0)
        {
            printf("The queue is full. Waiting for the queue to be available.\n");
            pause();
        }
        else if(strcmp(connect_type,"tryConnect") == 0)
        {
            printf("The queue is full.The client is terminating.\n");
            exit(1);
        }
        else
        {
            printf("Please enter connect/tryConnect\n");
            exit(1);
        }
    }
    else if(pid == SIGUSR2)
    {
        printf("Connection established.\n");
    }
}
int main(int arg, char**args)
{


    int server_pipe_fd;
    int client_pipe_fd;

    char client_pipe_name[BUFFER_SIZE];
    char client_pid[BUFFER_SIZE];



    char buffer[BUFFER_SIZE];

    char path[BUFFER_SIZE];

    signal(SIGUSR1,queue_connect);
    signal(SIGUSR2,queue_connect);

    signal(SIGINT,quit_signal);

    if(arg < 2)
    {
        printf("true format : ./client connect <server_pid>\n");
        exit(1);
    }

    printf("The Client has been started.\n");
    printf("Client PID -> %d\n",getpid());
    sleep(2);

    sprintf(path,"/tmp/%s",PIPE_NAME);
    //server_pipe_fd = open(PIPE_NAME,O_WRONLY);
    server_pipe_fd = open(path,O_WRONLY);
    sprintf(buffer,"%d-%s",getpid(),args[2]);
    
    sprintf(client_pid,"%d",getpid());

    if(server_pipe_fd < 0)
    {
        perror("fail");
        exit(EXIT_FAILURE);
    }

    write(server_pipe_fd,buffer,strlen(buffer));
    close(server_pipe_fd);

    server_pipe_fd = open(path,O_RDONLY);

    if(server_pipe_fd < 0)
    {
        perror("fail");
        exit(EXIT_FAILURE);
    }

    memset(buffer,0,strlen(buffer));


    read(server_pipe_fd,buffer,BUFFER_SIZE);
    close(server_pipe_fd);


    if(strcmp(buffer,"Server PID is invalid") == 0)
    {
        printf("%s\n",buffer);
        exit(1);
    }
    else
        printf("%s\n",buffer);
    server_pid = atoi(args[2]);
    strcpy(connect_type,args[1]);    
    
    sprintf(client_pipe_name,"/tmp/client_%d",getpid());

    char input[BUFFER_SIZE];
    char output[BUFFER_SIZE];

    sleep(1);
    while (1)
    {
        usleep(1000);
        memset(input,'\0',strlen(input));
        memset(output,'\0',strlen(output));
        printf("Enter input: ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) != NULL)
        {

            
            input[strcspn(input, "\n")] = '\0';
            client_pipe_fd = open(client_pipe_name,O_WRONLY);
            if(client_pipe_fd < 0)
            {
                perror("pipe client fail");
                exit(1);
            }

            write(client_pipe_fd,input,strlen(input)+1);
            close(client_pipe_fd);

            usleep(500);

            if (strcmp(input, "quit") == 0)
            {
                kill(atoi(args[2]),SIGUSR1);
                printf("quit function is start\n");
                break;
            }
            else if(strcmp(input,"killServer") == 0)
            {
                kill(atoi(args[2]),SIGINT);
                printf("Server is being terminated\n");
                return 1;
            }
            client_pipe_fd = open(client_pipe_name, O_RDONLY);
            
            while(read(client_pipe_fd,output,BUFFER_SIZE) > 0)
            {
                printf("%s",output);
                usleep(500);    
                memset(output,0,strlen(output));        
            }
            printf("\n");
            close(client_pipe_fd);
        }
        else
        {
            perror("fgets error");
            exit(EXIT_FAILURE);
        }
    }
    sleep(2);
    return 0;
}
