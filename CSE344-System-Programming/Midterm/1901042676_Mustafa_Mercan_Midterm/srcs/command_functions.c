#include "../biboServer.h"
void list_command_handle(const char* folder_name, char* client_pipe_name) 
{
    char folder_path[strlen(folder_name) + 3];

    sprintf(folder_path,"./%s",folder_name); 
    DIR *dir = opendir(folder_path);

    if(dir == NULL)
    {
        printf("Failed to open directory!\n");
        exit(1);
    }

    struct dirent *entry;
    while((entry = readdir(dir)) != NULL)
    {
        char tmp_str[strlen(entry->d_name) + 1];
        
        sprintf(tmp_str,"%s\n",entry->d_name);
        write_data_fifo(client_pipe_name,tmp_str);
    }

    closedir(dir);
}





void writeT_handle(char* command, const char* folder_name, char* client_pipe_name)
{

    char** parse_command;
    int argumant_number = 0;

    parse_command = str_split(command,' ');
    while(parse_command[argumant_number] != 0)
        argumant_number++;

    printf("%d\n",argumant_number);
    if(argumant_number == 1 || argumant_number == 2)
    {   
        char tmp_str[BUFFER_SIZE];
        sprintf(tmp_str,"Please use the correct format: readF <file> <line#> \" input \"\n");
        write_data_fifo(client_pipe_name,tmp_str);
    }
    else if(argumant_number == 3)
    {
        char *path = (char*)malloc(sizeof(char)*strlen(parse_command[1]) + strlen(folder_name)+3);
        sprintf(path,"./%s/%s",folder_name,parse_command[1]);
        lock_and_write(client_pipe_name,path,parse_command,true);
    }
    else if(argumant_number == 4)
    {
        char *path = (char*)malloc(sizeof(char)*strlen(parse_command[1]) + strlen(folder_name)+3);
        sprintf(path,"./%s/%s",folder_name,parse_command[1]);
        lock_and_write(client_pipe_name,path,parse_command,false);
    }
}
void readF_handle(char* command, const char* folder_name, char* client_pipe_name)
{
    printf("readF handle working\n");
    

    char** parse_command; //TEST
    int argumant_number = 0; 
    int initial_size = 100; 
    int i = 0; 
    int client_pipe_fd;
    parse_command = str_split(command,' ');
    while(parse_command[argumant_number] != 0)
        argumant_number++;

    if(argumant_number == 1)
    {
        char tmp_str[BUFFER_SIZE];
        sprintf(tmp_str,"Please use the correct format: readF <file> <line #>\n");
        write_data_fifo(client_pipe_name,tmp_str);
    }
    else if(argumant_number == 2)
    {
        int initial_size = 100;
        int file_fd;
        char *tmp = (char*)malloc(sizeof(char)*initial_size);
        char *path = (char*)malloc(sizeof(char)*strlen(parse_command[1]) + strlen(folder_name)+3);
        sprintf(path,"./%s/%s",folder_name,parse_command[1]);
        int ch;
        int index = 0;
        char chr;

        file_fd = open(path, O_RDONLY);
        if (file_fd < 0) 
        {
            printf("Failed to open directory!\n");
            return;
        }   
        int client_pipe = open(client_pipe_name,O_WRONLY);
        if(client_pipe < 0)
        {
            perror("fifo cant open fail\n");
            return;
        }

        while (read(file_fd, &chr, 1) > 0) 
        {
            write(client_pipe,&chr,1);
        }


        
        close(file_fd);
        close(client_pipe);
        free(tmp);
        free(path);

    }
    else if(argumant_number == 3)
    {   

        int initial_size = 100;
        int file_fd;
        char *tmp = (char*)malloc(sizeof(char)*initial_size);
        char *path = (char*)malloc(sizeof(char)*strlen(parse_command[1]) + strlen(folder_name)+3);
        sprintf(path,"./%s/%s",folder_name,parse_command[1]);
        char ch;
        int index = 0;
        int line_count = 0;
        int target_line = atoi(parse_command[2]);

        file_fd= open(path, O_RDONLY);



        if (file_fd == -1)
        {
            printf("Failed to open directory!\n");
            return;
        }

        if(line_count != target_line - 1)
        {
            while (read(file_fd, &ch, 1) > 0)
            {
                if (ch == '\n' || ch=='\r') 
                {
                    line_count++;
                }
                if (line_count == target_line - 1)
                {
                    break;
                }
            }
        }
 
        printf("\n");
        memset(tmp, 0, initial_size);
        while (read(file_fd, &ch, 1) > 0 && ch != '\n') 
        {
            tmp[index] = ch;
            index++;

            if (index == initial_size) 
            {
                initial_size *= 2;
                tmp = realloc(tmp, initial_size * sizeof(char));
            }
        }
        close(file_fd);
        write_data_fifo(client_pipe_name,tmp);

        free(path);
        free(tmp);
    }
    i = 0;
    while(parse_command[i] != 0)
    {
        free(parse_command[i]);
        i++;
    }
    free(parse_command);

}


void upload_handle(char* command, const char* folder_name, char* client_pipe_name)
{
    printf("upload handle function is starting...\n");
    
    char** parse_command; 
    int argumant_number = 0; 
    int initial_size = 100;
    int i = 0; 
    int client_pipe_fd;
    parse_command = str_split(command,' ');

    while(parse_command[argumant_number] != 0)
        argumant_number++;

    if(argumant_number < 2)
    {
        char tmp_str[BUFFER_SIZE];
        sprintf(tmp_str,"Please use the correct format: upload <file>\n");
        write_data_fifo(client_pipe_name,tmp_str);
        return;
    }
    char *path = (char*)malloc(sizeof(char)*strlen(parse_command[1]) + strlen(folder_name)+3);//TEST
    sprintf(path,"./%s/%s",folder_name,parse_command[1]);
    
    int tmp_fd = open(path,O_RDONLY);
    if(tmp_fd >= 0)
    {
        char tmp_str[BUFFER_SIZE];
        sprintf(tmp_str,"The server does not contain such a file.\n");
        printf("The server does not contain such a file.\n");
        write_data_fifo(client_pipe_name,tmp_str);
        close(tmp_fd);
        return;
    }
    close(tmp_fd);
    tmp_fd = open(parse_command[1],O_RDONLY);
    if(tmp_fd < 0 )
    {
        char tmp_str[BUFFER_SIZE];
        sprintf(tmp_str,"The file could not be found.\n");
        printf("The file could not be found.\n");
        write_data_fifo(client_pipe_name,tmp_str);
        close(tmp_fd);
        return; 
    }
    close(tmp_fd);

  

    int src = open(parse_command[1],O_RDONLY);
    int dest = open(path,O_WRONLY | O_CREAT,0644);
    char ch[1];

    if(src < 0 || dest < 0)
    {
        perror("upload error\n");
        write_data_fifo(client_pipe_name,"upload fail");
        return;
    }

    ssize_t bytes_read;
    while((bytes_read = read(src,ch,sizeof(ch))) > 0)
    {
        write(dest,ch,bytes_read);
    }
    write_data_fifo(client_pipe_name,"upload success");
    close(src);
    close(dest);
}
void download_handle(char* command, const char* folder_name, char* client_pipe_name)
{
    printf("upload handle function is starting...\n");
    
    char** parse_command; 
    int argumant_number = 0; 
    int initial_size = 100;
    int i = 0; 
    int client_pipe_fd;
    parse_command = str_split(command,' ');

    while(parse_command[argumant_number] != 0)
        argumant_number++;

    if(argumant_number < 2)
    {
        char tmp_str[BUFFER_SIZE];
        sprintf(tmp_str,"Please use the correct format: download <file>\n");
        write_data_fifo(client_pipe_name,tmp_str);
        return;
    }
    char *path = (char*)malloc(sizeof(char)*strlen(parse_command[1]) + strlen(folder_name)+3);
    sprintf(path,"./%s/%s",folder_name,parse_command[1]);
    
    int tmp_fd = open(path,O_RDONLY);
    if(tmp_fd < 0)
    {
        char tmp_str[BUFFER_SIZE];
        printf("path -> %s\n",path);
        sprintf(tmp_str,"The server does not contain such a file.\n");
        printf("The server does not contain such a file.\n");
        write_data_fifo(client_pipe_name,tmp_str);
        close(tmp_fd);
        return;
    }
    close(tmp_fd);

    int src = open(path,O_RDONLY);
    int dest = open(parse_command[1],O_WRONLY | O_CREAT,0644);
    char ch[1];

    if(src < 0 || dest < 0)
    {
        perror("upload error\n");
        write_data_fifo(client_pipe_name,"upload fail");
        return;
    }

    ssize_t bytes_read;
    while((bytes_read = read(src,ch,sizeof(ch))) > 0)
    {
        write(dest,ch,bytes_read);
    }
    write_data_fifo(client_pipe_name,"download success");
    close(src);
    close(dest);
}