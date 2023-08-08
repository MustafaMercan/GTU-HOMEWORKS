#include "../biboServer.h"


void download_handle(client_request client)
{
    char** parse_command; 
    int i = 0; 
    parse_command = str_split(client.request, ' ');
    int argumant_number = 0; 


    while(parse_command[argumant_number] != 0)
        argumant_number++;

    char ch[1];


    while(parse_command[argumant_number] != 0)
        argumant_number++;

    if(argumant_number < 2)
    {
        char tmp_str[BUFFER_SIZE];
        sprintf(tmp_str,"Please use the correct format: upload <file>\n");
        memcpy(client.response,tmp_str,sizeof(client.response));
        lock_and_write(client.path,client);
        return;
    }
    char *path = (char*)malloc(sizeof(char)*strlen(parse_command[1]) + strlen(client.folder_path)+3);
    sprintf(path,"./%s/%s",client.folder_path,parse_command[1]);
    int tmp_fd = open(path,O_RDONLY);
    
    if(tmp_fd < 0)
    {
        char tmp_str[BUFFER_SIZE];
        sprintf(tmp_str,"The file could not be found.\n");
        memcpy(client.response,tmp_str,sizeof(client.response));
        lock_and_write(client.path,client);

        close(tmp_fd);

        int clear = 0;

        while(parse_command[clear] != 0)
        {
            free(parse_command[clear]);
            clear++;
        }
        free(parse_command);
        free(path);
        return;
    }
    close(tmp_fd);

    int src = open(path,O_RDONLY);
    int dest = open(parse_command[1],O_WRONLY | O_CREAT,0644);


    if(src < 0 || dest < 0)
    {
        perror("download\n");
        char buff[] = "download error";
        memcpy(client.response,buff,sizeof(client.response));
        lock_and_write(client.path,client);
        int clear = 0;
        while(parse_command[clear] != 0)
        {
            free(parse_command[clear]);
            clear++;
        }
        free(parse_command);
        free(path);

        return;
    }
    ssize_t bytes_read;

    while((bytes_read = read(src,ch,sizeof(ch))) > 0)
    {
        write(dest,ch,bytes_read);
    }
    char buff[] = "download success";

    memcpy(client.response,buff,sizeof(client.response));
    lock_and_write(client.path,client);
    
    int clear =0 ;
    while(parse_command[clear] != 0)
    {
        free(parse_command[clear]);
        clear++;
    }
    free(parse_command);
    free(path);
    close(src);
    close(dest);
    
}
void upload_handle(client_request client)
{
    char **parse_command;
    int argumant_number = 0;
    int i = 0;
    char ch[1];

    parse_command = str_split(client.request, ' ');

    while(parse_command[argumant_number] != 0)
        argumant_number++;
    if(argumant_number < 2)
    {
        char tmp_str[BUFFER_SIZE];
        sprintf(tmp_str,"Please use the correct format: upload <file>\n");
        memcpy(client.response,tmp_str,sizeof(client.response));
        lock_and_write(client.path,client);
        return;
    }
    char *path = (char*)malloc(sizeof(char)*strlen(parse_command[1]) + strlen(client.folder_path)+3);
    sprintf(path,"./%s/%s",client.folder_path,parse_command[1]);
    
    int tmp_fd = open(path,O_RDONLY);
    if(tmp_fd > 0)
    {
        char tmp_str[BUFFER_SIZE];
        sprintf(tmp_str,"The server does not contain such a file.\n");
        printf("The server does not contain such a file.\n");
        memcpy(client.response,tmp_str,sizeof(client.response));
        lock_and_write(client.path,client);
        close(tmp_fd);
        free(path);
        
        int clear = 0;
        while(parse_command[clear] != 0)
        {
            free(parse_command[clear]);
            clear++;
        }
        free(parse_command);
    
        return;
    }
    close(tmp_fd);
    tmp_fd = open(parse_command[1],O_RDONLY);
    if(tmp_fd < 0)
    {
        char tmp_str[BUFFER_SIZE];
        sprintf(tmp_str,"The file could not be found.\n");
        memcpy(client.response,tmp_str,sizeof(client.response));
        lock_and_write(client.path,client);

        close(tmp_fd);

        int clear = 0;

         while(parse_command[clear] != 0)
        {
            free(parse_command[clear]);
            clear++;
        }
        free(parse_command);
        free(path);
        return;
    }
    close(tmp_fd);

    int src = open(parse_command[1],O_RDONLY);
    int dest = open(path,O_WRONLY | O_CREAT,0644);

    if(src < 0 || dest < 0)
    {
        perror("upload error\n");
        char buff[] = "upload error";
        memcpy(client.response,buff,sizeof(client.response));
        lock_and_write(client.path,client);

        return;
    }
    ssize_t bytes_read;
    while((bytes_read = read(src,ch,sizeof(ch))) > 0)
    {
        write(dest,ch,bytes_read);
    }
    char buff[] = "upload success";

    memcpy(client.response,buff,sizeof(client.response));
    lock_and_write(client.path,client);
    close(src);
    close(dest);

}
void writeT_handle(client_request client)
{
    char** parse_command;
    int argumant_number = 0;

    parse_command = str_split(client.request,' ');
    char tmp_str[BUFFER_SIZE];
    
    while(parse_command[argumant_number] != 0)
        argumant_number++;
    if(argumant_number == 1 || argumant_number == 2)
    {   
        
        sprintf(tmp_str,"Please use the correct format: readF <file> <line#> \" input \"\n");
        memcpy(client.response,tmp_str,sizeof(client.response));
        lock_and_write(client.path,client);
        return;
    }
    else if(argumant_number == 3)
    {
        char path[BUFFER_SIZE + 4];
        sprintf(path,"./%s/%s",client.folder_path,parse_command[1]);
        write_file(path,parse_command,true);
    }
    else if(argumant_number == 4)
    {
        char *path = (char*)malloc(sizeof(char)*strlen(parse_command[1]) + strlen(client.folder_path)+3);
        sprintf(path,"./%s/%s",client.folder_path,parse_command[1]);
        write_file(path,parse_command,false);
    }
    strcpy(tmp_str,"operation is done!\n");
    memcpy(client.response,tmp_str, sizeof(client.response));
    lock_and_write(client.path,client);

}



void list_command_handle(client_request client)
{
    struct dirent *entry;


    DIR *dir = opendir(client.folder_path);


    if(dir == NULL)
    {
        printf("Failed to open work directory!\n");
        return ;
    }

    while((entry = readdir(dir)) != NULL)
    {
        char tmp_str[strlen(entry->d_name) + 1];
        
        sprintf(tmp_str,"%s\n",entry->d_name);
        strcpy(client.response,tmp_str);

        lock_and_write(client.path,client);
    }
}

void readF_handle(client_request client)
{
    char **parse_command;
    int argumant_number = 0;


    parse_command = str_split(client.request,' ');
    while(parse_command[argumant_number] != 0)
        argumant_number++;

    if(argumant_number < 2)
    {
        printf("Invalid format\n");
        return;
    }
    else if(argumant_number == 2)
    {
        char buffer[50];
        int file_fd;
        char *target_path = (char*)malloc( sizeof(char) * (strlen(parse_command[1]) + strlen(client.folder_path)+3));
        int index = 0;
        sprintf(target_path,"./%s/%s",client.folder_path,parse_command[1]);
        
        file_fd = open(target_path, O_RDONLY);
        if (file_fd < 0) 
        {
            printf("Failed to open directory!\n");
            return;
        }
        while(read(file_fd,buffer,50) > 0)
        {
            memcpy(client.response,buffer, sizeof(client.response));
            lock_and_write(client.path,client);
        }
        close(file_fd);
        free(target_path);
    }
    else if(argumant_number == 3)
    {

        int file_fd;
        char *target_path = (char*)malloc( sizeof(char) * (strlen(parse_command[1]) + strlen(client.folder_path)+3));
        
        sprintf(target_path,"./%s/%s",client.folder_path,parse_command[1]);
        char ch;
        char buffer[50];
        
        int index = 0;
        int line_count = 0;
        int target_line = atoi(parse_command[2]);

        file_fd= open(target_path, O_RDONLY);

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
        while(read(file_fd,&ch,1) > 0 && ch != '\n')
        {
            printf("%c\n ",ch);
            client.response[index] = ch;
            index++;

            if(index == RESPONSE_SIZE - 1)
            {
                lock_and_write(client.path,client);
                memset(client.response,0,RESPONSE_SIZE);
                index = 0;
            }
        }
        lock_and_write(client.path,client);
        close(file_fd);
        free(target_path);
    }

    int clear = 0;
    while(parse_command[clear] != 0)
    {
        free(parse_command[clear]);
        clear++;
    }
    free(parse_command);



}