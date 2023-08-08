#include "biboServer.h"

int max_client_number = -1;
int current_client_number = 0;
int pid_client[BUFFER_SIZE] = {0};
char path_server [BUFFER_SIZE];

sem_t *sem;

void decrease_client(int pid)
{
    sem_post(sem);
    current_client_number-=1;
}
void quit_signal(int pid)
{
    printf("Terminating the program, child process and clients\n");
    int parent_pid = getpid();
    kill(-parent_pid,SIGTERM);
    for(int i = 0 ; i < current_client_number ; i++)
    {
        kill(pid_client[i],SIGTERM);
    }

    exit(1);
}


int main(int arg, char**args)
{
    int count = 0 ;

    signal(SIGUSR1,decrease_client);
    signal(SIGINT,quit_signal);


    if (arg < 3) {
        printf("Please run the program in the correct format. The correct format is: biboServer <dirname> <max. #ofClients>\n");
        return 1;
    }
    if(arg == 3)
    {
        max_client_number = atoi(args[2]);
        if(max_client_number <= 0)
        {
            printf("Please enter a positive integer value greater than 0.\n");
            exit(1);
        }
        printf("max client number -> %d\n",max_client_number);
    }

    int pipe_fd;
    char server_pid[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    const char *folder_name = args[1]; // TEST

    char log_file_name[BUFFER_SIZE];
    int server_log;
    sprintf(log_file_name,"./logs/server_log_%d.log",getpid());

    server_log = open(log_file_name,O_WRONLY|O_CREAT|O_TRUNC,0644);
    if(server_log == -1)
    {
        perror("Log can't created \n");
        return 1;
    }


    struct stat st;
    sem_t *sem_handler = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); //TEST
    sem = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    int result = stat(folder_name,&st);
    sprintf(server_pid,"%d",getpid());

    sem_init(sem,1,max_client_number);
    sem_init(sem_handler,1,1);

    if (result == 0 && S_ISDIR(st.st_mode)) 
    {
        printf("The directory exists in this path. The server will be started.\n");
    }
    else
    {
        result = mkdir(folder_name,0777);
        if(result == 0)
            printf("The directory has been created.\n");
    }
    printf("The Server Started PID: %d\n", getpid());

    memset(path_server,0,strlen(path_server));
    sprintf(path_server,"/tmp/%s",PIPE_NAME);
    //printf("fifo -> %s\n",path_server);
    mkfifo(path_server, 0666);
    
    while(1)
    {
        bool connect_flag = true;
        memset(buffer,'\0',BUFFER_SIZE);
        pipe_fd = open(path_server,O_RDONLY);

        if (pipe_fd < 0)
        {
            perror("server fifo read fail");
            exit(EXIT_FAILURE);
        }
        int num_size = read(pipe_fd,buffer,BUFFER_SIZE);
        close(pipe_fd);

        char** connect = str_split(buffer,'-'); //TEST
        if(strcmp(connect[1],server_pid) == 0)
        {
            write_data_fifo(path_server,"The client connected to server.");
        }
        else
        {
            write_data_fifo(path_server,"Server PID is invalid");
            connect_flag = false;
        }
        close(pipe_fd);

        if(num_size > 0 && connect_flag == true)
        {
            pid_client[current_client_number] = atoi(connect[0]);
            current_client_number++;
            char log_information[BUFFER_SIZE];
            sprintf(log_information,"Client_%s connected the server.\n",connect[0]);
            write(server_log,log_information,strlen(log_information));
            memset(log_information,0,strlen(log_information));

            int pid = fork();
            if(pid == -1)
            {
                perror("Fork error");
            }
            else if(pid == 0)
            {

                sleep(1);
                if(current_client_number > max_client_number)
                    kill(atoi(connect[0]),SIGUSR1);

                sem_wait(sem);
                kill(atoi(connect[0]),SIGUSR2);

                printf("Client PID %s connected.\n",connect[0]);

                char client_pipe_name[BUFFER_SIZE + 20];
                char command[BUFFER_SIZE];
                int client_pipe_fd;
                
                char path_client[BUFFER_SIZE];
                sprintf(path_client,"/tmp/client_%s",connect[0]);
                mkfifo(path_client,0666);

                while(1)
                {
                    memset(command,0,strlen(command));
                    client_pipe_fd = open(path_client,O_RDONLY);

                    if(client_pipe_fd < 0)
                    {
                        perror("read error");
                        exit(1);
                    }
                    read(client_pipe_fd,command,BUFFER_SIZE);
                    close(client_pipe_fd);

                    char** parse_command = str_split(command,' ');//TEST
                    //printf("command -> %s\n",parse_command[0]);
                    if(strcmp(parse_command[0],"help") == 0)
                    {
                        char availableComments[] = "Available comments are :\nhelp, list, readF, writeT, upload, download, quit, killServer";
                        write_data_fifo(path_client,availableComments);
                    }
                    else if(strcmp(parse_command[0],"list") == 0)
                    {
                        list_command_handle(folder_name,path_client);
                    }
                    else if(strcmp(parse_command[0],"quit") == 0)
                    {
                        sprintf(log_information,"Client_%s disconnected the server.\n",connect[0]);
                        write(server_log,log_information,strlen(log_information));
                        
                        sem_post(sem);
                        unlink(path_client);
                        exit(EXIT_SUCCESS);
                    }
                    else if(strcmp(parse_command[0],"readF") == 0)
                    {
                        printf("A request for processing has arrived, waiting for the operation to complete.\n");
                        sem_wait(sem_handler);
                        readF_handle(command,folder_name,path_client);
                        printf("The operation has been completed.");
                        sem_post(sem_handler);
                        
                    
                    }
                    else if(strcmp(parse_command[0],"writeT") == 0)
                    {
                        printf("A request for processing has arrived, waiting for the operation to complete.\n");
                        sem_wait(sem_handler);
                        writeT_handle(command,folder_name,path_client);
                        sem_post(sem_handler);
                        printf("The operation has been completed.");

                    }
                    else if(strcmp(parse_command[0],"upload") == 0)
                    {
                        printf("A request for processing has arrived, waiting for the operation to complete.\n");
                        sem_wait(sem_handler);
                        upload_handle(command,folder_name,path_client);
                        sem_post(sem_handler);
                        printf("The operation has been completed.");

                    }
                    else if(strcmp(parse_command[0],"download") == 0)
                    {
                        printf("A request for processing has arrived, waiting for the operation to complete.\n");
                        sem_wait(sem_handler);
                        download_handle(command,folder_name,path_client);
                        sem_post(sem_handler);
                        printf("The operation has been completed.");   
                    }
                    else
                    {
                        
                        write_data_fifo(path_client,"The command was not found. Use the 'help' command to see all available commands.");
                    }
                }
            }
            else
            {
                 int status;
                 waitpid(pid, &status, WNOHANG);
            }

        }
    }
    unlink(path_server);

    return 0;
}
