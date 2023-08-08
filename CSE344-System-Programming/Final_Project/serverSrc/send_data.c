#include "dropbox.h"

void clear_path(FileInfo *fileInfo,int current_client)
{
    FileInfoNode *iter = fileInfo->root;
    while(iter != NULL)
    {

        if(iter->deleted_or_not)
        {
                remove_node_file_info(fileInfo,iter->file_path);            
        }
        iter = iter->next;
    }
}

void    update_other_side(FileInfo *fileInfo,int sockfd,int current_client)
{
    FileInfoNode *iter;
    iter = fileInfo-> root;

    while(iter != NULL)
    {
        if(iter->modified_flag || iter->deleted_or_not || iter->added_new_or_not)
        {
            //printf("modified -> %d deleted -> %d added new -> %d\n",iter->modified_flag,iter->deleted_or_not,iter->added_new_or_not);

            FileInfoNode received_data;
            char serialized_data[sizeof(*iter)];
            memset(&received_data,0,sizeof(received_data));
            memset(serialized_data,0,sizeof(serialized_data));
            memcpy(serialized_data,iter,sizeof(serialized_data));
            
            
            send(sockfd,serialized_data,sizeof(serialized_data),0);
            recv(sockfd,&received_data,sizeof(received_data),0);

            //printf("received data -> %s\n",received_data.file_path);
            

            if(strcmp(received_data.file_path,"file content request") == 0)
            {

                //printf("\n\n\nfile content request geldi \n\n");
                int fd = open(iter->file_path,O_RDONLY);
                sendDataInfoNode send_file_data;
                sendDataInfoNode received_file_data;
                char serialized_file_data[sizeof(send_file_data)];
                
                memset(serialized_file_data,0,sizeof(serialized_file_data));
                memset(&send_file_data,0,sizeof(send_file_data));
                memset(&received_file_data,0,sizeof(received_file_data));
                if(fd < 0)
                {
                    //printf("file open error update other side\n");
                }
                while(read(fd,send_file_data.buffer,sizeof(send_file_data.buffer)) > 0)
                {
                    snprintf(send_file_data.path,sizeof(send_file_data.path),"%s",iter->file_path);
                    send_file_data.done = false;
                    memcpy(serialized_file_data,&send_file_data,sizeof(serialized_file_data));
                    send(sockfd,serialized_file_data,sizeof(serialized_file_data),0);
                    recv(sockfd,&received_file_data,sizeof(received_file_data),0);
                    //printf("file content response -> %s\n",received_file_data.buffer);
                    
                    memset(serialized_file_data,0,sizeof(serialized_file_data));
                    memset(&send_file_data,0,sizeof(send_file_data));
                    memset(&received_file_data,0,sizeof(received_file_data));
                }

                send_file_data.done = true;
                memcpy(serialized_file_data,&send_file_data,sizeof(serialized_file_data));
                send(sockfd,serialized_file_data,sizeof(serialized_file_data),0);
                recv(sockfd,&received_file_data,sizeof(received_file_data),0);
                //printf("file bitti response -> %s\n",received_file_data.buffer);
                
                iter->modified_flag = false;
                iter->modified_count += 1;
            }
            else if(strcmp(received_data.file_path,"dosya olusturuldu") == 0)
            {
                //printf("response -> %s\n",received_data.file_path);
                iter->added_new_or_not = false;
            }
            else if(strcmp(received_data.file_path,"dosya silindi") == 0)
            {
                //printf("response -> %s\n",received_data.file_path);
                
                remove_node_file_info(fileInfo,iter->file_path);

            }
        }
        iter = iter->next;
    }
    
    FileInfoNode send_data;
    FileInfoNode received_data;
    char serialized_data[sizeof(send_data)];
    
    memset(&send_data,0,sizeof(send_data));
    memset(serialized_data,0,sizeof(serialized_data));
    memset(&received_data,0,sizeof(received_data));
    
    snprintf(send_data.file_path,sizeof(send_data.file_path),"process done");
    memcpy(serialized_data,&send_data,sizeof(serialized_data));
    send(sockfd,serialized_data,sizeof(serialized_data),0);

    recv(sockfd,&received_data,sizeof(received_data),0);
    //printf("dosya islemi yapildi response -> %s\n",received_data.file_path);

    

}
void detect_delete_file(FileInfo *fileInfo,char *path) //kullaniliyor
{
    FileInfoNode *iter = fileInfo->root;
    while(iter != NULL)
    {
        if(access(iter->file_path,F_OK) != -1)
        {
            //printf("dosya var\n");
        }
        else
        {
            //printf("dosya silinmis\n");
            //printf("iter path -> %s\n",iter->file_path);
            iter->deleted_or_not = true;
        }
        iter = iter->next;
    }
}

void listen_dir(FileInfo *fileInfo,int clientSocket,char *path,bool flag,int current_client)
{
    struct dirent* entry;
    DIR *dir;
    dir = opendir(path);
    if(dir == NULL)
    {
        perror("dizin acilmadi\n");
        exit(1);
    }
    while((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        if(entry->d_type == DT_DIR)
        {           
            char sub_path[PATH_MAX_LENGTH];
            snprintf(sub_path,sizeof(sub_path),"%s/%s",path,entry->d_name);
            FileInfoNode *tmp_node = find_node(fileInfo,sub_path);
            if(tmp_node == NULL)
            {
                //printf("dosya olusmus\n");
                add_node_file_info(fileInfo,sub_path,true);
                tmp_node = find_node(fileInfo,sub_path);
                tmp_node->added_new_or_not = true;
            }
            else
            {
                if(tmp_node->deleted_or_not != true)
                    tmp_node->deleted_or_not = false;
            }
            listen_dir(fileInfo,clientSocket,sub_path,false,current_client);
        }
        else
        {
            struct stat file_info;
            char sub_path[PATH_MAX_LENGTH];
            snprintf(sub_path,sizeof(sub_path),"%s/%s",path,entry->d_name);
            FileInfoNode *tmp_node = find_node(fileInfo,sub_path);
            
            if(tmp_node == NULL)
            {
                add_node_file_info(fileInfo,sub_path,false);
                tmp_node = find_node(fileInfo,sub_path);
                tmp_node->added_new_or_not = true;
            }
            else
            {
                if(tmp_node->deleted_or_not != true)
                    tmp_node->deleted_or_not = false;

                if(stat(sub_path, &file_info) == 0)
                {
                    time_t modified_time = file_info.st_mtime;
                    time_t current_time = time(NULL);
                    double elapsed_seconds = difftime(current_time, modified_time);
                    //time_t initial_modified_time = file_info.st_mtime;
                    //usleep(500);
                    //time_t current_modified_time = file_info.st_mtime;
                    if(elapsed_seconds < 4)
                    {
                        //printf("dosya aslşfkaşlfkaslşk\n");
                        //printf("path -> %s dosya degistirilmis \n",sub_path);
                        FileInfoNode *tmp_node = find_node(fileInfo,sub_path);
                        if(tmp_node != NULL)
                        {
                            //modified_flag = true;
                            tmp_node->modified_flag = true;
                        }
                    }
                }
            }

        }
    }
    closedir(dir);
}

void delete_dir(char *path)
{
    DIR *dir;
    struct dirent *entry;
    if( (dir = opendir(path)) == NULL)
    {
        //printf("dosya acilamadi\n");
        return;
    }
    while((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) 
        {
            continue;
        }

        char sub_path[BUFFER_SIZE];
        snprintf(sub_path,sizeof(sub_path),"%s/%s",path,entry->d_name);
        if(entry->d_type == DT_DIR)
        {
            delete_dir(sub_path);
        }
        else
        {
            remove(sub_path);
        }
    }
    closedir(dir);
    rmdir(path);
}

void str_replace(char *str, const char *subStr, const char *replaceStr) 
{
    int subStrLen = strlen(subStr);
    int replaceStrLen = strlen(replaceStr);
    char *pos = strstr(str, subStr);

    while (pos != NULL) {
        memmove(pos + replaceStrLen, pos + subStrLen, strlen(pos + subStrLen) + 1);
        memcpy(pos, replaceStr, replaceStrLen);
        pos = strstr(pos + replaceStrLen, subStr);
    }
}

void read_data(int clientSocket,char *path)
{

    //printf("\n\nread data function\n\n");

    FileInfoNode received_data;
    FileInfoNode send_data;
    char serialized_data[sizeof(send_data)];

    memset(serialized_data,0,sizeof(serialized_data));
    memset(&received_data,0,sizeof(received_data));
    memset(&send_data,0,sizeof(send_data));

    while(recv(clientSocket,&received_data,sizeof(received_data),0) > 0)
    {
        if(strcmp(received_data.file_path,"process done") != 0)
        {
            
            if(received_data.deleted_or_not && received_data.dir_or_not)
            {
                //delete file
                snprintf(send_data.file_path,sizeof(send_data.file_path),"dosya silindi");
                str_replace(received_data.file_path,"client_file",path);
                delete_dir(received_data.file_path);
                memcpy(serialized_data,&send_data,sizeof(serialized_data));
                send(clientSocket,serialized_data,sizeof(serialized_data),0);
            }
            if(received_data.deleted_or_not && received_data.dir_or_not == false)
            {
                snprintf(send_data.file_path,sizeof(send_data.file_path),"dosya silindi");
                str_replace(received_data.file_path,"client_file",path);
                //delete_dir(received_data.file_path);
                remove(received_data.file_path);
                memcpy(serialized_data,&send_data,sizeof(serialized_data));
                send(clientSocket,serialized_data,sizeof(serialized_data),0);
            }
            else if(received_data.added_new_or_not && received_data.dir_or_not == true)
            {
                snprintf(send_data.file_path,sizeof(send_data.file_path),"dosya olusturuldu");
                str_replace(received_data.file_path,"client_file",path);
                int result = mkdir(received_data.file_path, 0777);
                memcpy(serialized_data,&send_data,sizeof(serialized_data));
                send(clientSocket,serialized_data,sizeof(serialized_data),0);
            }
            else if(received_data.deleted_or_not == false && received_data.dir_or_not == false)
            {   
                //printf("\n\nim here\n\n");
                //printf("path -> %s\n",received_data.file_path);
                snprintf(send_data.file_path,sizeof(send_data.file_path),"file content request");
                str_replace(received_data.file_path,"client_file",path);
                memcpy(serialized_data,&send_data,sizeof(serialized_data));
                send(clientSocket,serialized_data,sizeof(serialized_data),0);

                sendDataInfoNode send_file_data;
                sendDataInfoNode received_file_data;
                char serialized_file_data[sizeof(send_file_data)];

                memset(serialized_file_data,0,sizeof(serialized_file_data));
                memset(&send_file_data,0,sizeof(send_file_data));
                memset(&received_file_data,0,sizeof(received_file_data));

                int fd;
                while(recv(clientSocket,&received_file_data,sizeof(received_file_data),0) > 0)
                {
                    if(received_file_data.done == true)
                    {
                        close(fd);
                        snprintf(send_file_data.path,sizeof(send_file_data.path),"ok");
                        memcpy(serialized_file_data,send_file_data.path,sizeof(serialized_data));
                        send(clientSocket,serialized_file_data,sizeof(serialized_file_data),0);   
                        break;
                    }
                    str_replace(received_file_data.path,"client_file",path);

                    fd = open(received_file_data.path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if(fd < 0)
                    {
                        //printf("fd path -> %s\n",received_file_data.path);
                        //printf("fd acma hatasi :8 \n");
                    }
                    else
                    {
                        //printf("path-> %s\n",received_file_data.path);
                        //printf("content -> %s\n",received_file_data.buffer);
                        write(fd,received_file_data.buffer,strlen(received_file_data.buffer));
                    }

                    snprintf(send_file_data.buffer,sizeof(send_file_data.buffer),"okundu");
                    
                    memcpy(serialized_file_data,&send_file_data,sizeof(serialized_file_data));
                    send(clientSocket,serialized_file_data,sizeof(serialized_file_data),0);

                    memset(serialized_file_data,0,sizeof(serialized_file_data));
                    memset(&send_file_data,0,sizeof(send_file_data));
                    memset(&received_file_data,0,sizeof(received_file_data));
                    
                }


                
            }

        }
        else if(strcmp(received_data.file_path,"process done") == 0)
        {
            memset(&send_data,0,sizeof(send_data));
            memset(serialized_data,0,sizeof(serialized_data));
            snprintf(send_data.file_path,sizeof(send_data.file_path),"devam et");
            memcpy(serialized_data,&send_data,sizeof(serialized_data));
            send(clientSocket,serialized_data,sizeof(serialized_data),0);
            break;
        }
        memset(serialized_data,0,sizeof(serialized_data));
        memset(&received_data,0,sizeof(received_data));
        memset(&send_data,0,sizeof(send_data));
    }

        

    
}


void listen_client_side(FileInfo *fileInfo,int clientSocket,char *path)
{
    read_data(clientSocket,path);
}

void init_other_side(FileInfo *fileInfo, RequestQueueNode *currentNode)
{

    //printf("\n\n init other size \n\n");
    FileInfoNode *iter = fileInfo->root;
    FileInfoNode received_data;
    
    while(iter != NULL)
    {
        if(iter->dir_or_not == true)
        {
            char serialized_data[sizeof(*iter)];
            memcpy(serialized_data,iter,sizeof(serialized_data));
            send(currentNode -> sockfd,serialized_data,sizeof(serialized_data),0);
            recv(currentNode -> sockfd, &received_data,sizeof(received_data),0);

            //printf("client response -> %s\n",received_data.file_path);
            memset(&received_data,0,sizeof(received_data));
        }
        iter = iter->next;
    }

    memset(&received_data,0,sizeof(received_data));
    snprintf(received_data.file_path,sizeof(received_data.file_path),"dosya aktarimi tamamlandi");
    char serialized_data[sizeof(received_data)];
    memset(serialized_data,0,sizeof(serialized_data));

    memcpy(serialized_data,&received_data,sizeof(serialized_data));
    send(currentNode->sockfd,serialized_data,sizeof(serialized_data),0);

    memset(&received_data,0,sizeof(received_data));    
    recv(currentNode -> sockfd, &received_data,sizeof(received_data),0);
    //printf("client response -> %s\n",received_data.file_path);

    memset(&received_data,0,sizeof(received_data));
    memset(serialized_data,0,sizeof(serialized_data));

    iter = fileInfo->root;
    bool file_flag = false;
    
    while(iter != NULL)
    {
        if(iter -> dir_or_not == false)
        {
            //printf("txt test path -> %s\n",iter->file_path);
            send_file_content(iter,currentNode->sockfd);
            file_flag = true;
        }
        iter = iter->next;
        usleep(500);
    }
    sendDataInfoNode received_info_node;
    sendDataInfoNode send_info_node;

    char serialized_data_2[sizeof(send_info_node)];
        
    memset(&received_info_node,0,sizeof(received_info_node));
    memset(&send_info_node,0,sizeof(send_info_node)); 
    memset(serialized_data_2,0,sizeof(serialized_data_2));

    snprintf(send_info_node.path,sizeof(send_info_node.path),"all_files_done");

    memcpy(serialized_data_2,&send_info_node,sizeof(send_info_node));

    send(currentNode->sockfd,serialized_data_2,sizeof(serialized_data_2),0);
    recv(currentNode->sockfd,&received_info_node,sizeof(received_info_node),0);

    //printf("init other side response -> %s\n",received_info_node.path);
    
}


void send_file_content(FileInfoNode *currentElement,int sockfd)
{

    //printf("send file content\n");
    sendDataInfoNode send_data;
    sendDataInfoNode received_data;

    memset(&send_data,0,sizeof(send_data));
    memset(&received_data,0,sizeof(received_data));

    int fd = open(currentElement->file_path,O_RDONLY);
    if(fd < 0)
    {
        //clienti bilgilendirme mesajı yollıcaksın unutma
        printf("file fd error");
        exit(1);
    }

    snprintf(send_data.path,sizeof(send_data.path),"%s",currentElement->file_path);
    while(read(fd,send_data.buffer,sizeof(send_data.buffer)) > 0)
    {

        snprintf(send_data.path,sizeof(send_data.path),"%s",currentElement->file_path);


        
        char serialized_data[sizeof(send_data)];
        memcpy(serialized_data,&send_data,sizeof(serialized_data));
        send(sockfd,serialized_data,sizeof(serialized_data),0);
        recv(sockfd,&received_data,sizeof(received_data),0);


        memset(serialized_data,0,sizeof(serialized_data));
        memset(&send_data,0,sizeof(send_data));
        memset(&received_data,0,sizeof(received_data));

        snprintf(send_data.path,sizeof(send_data.path),"%s",currentElement->file_path);
    }
    char serialized_data[sizeof(send_data)];
    memset(serialized_data,0,sizeof(serialized_data));
    memset(&received_data,0,sizeof(received_data));
    send_data.done = true;

    memcpy(serialized_data,&send_data,sizeof(send_data));

    send(sockfd,serialized_data,sizeof(serialized_data),0);
    recv(sockfd,&received_data,sizeof(received_data),0);

    //printf("1 files aktarma sonucu response -> %s\n",received_data.path);
    close(fd);
}