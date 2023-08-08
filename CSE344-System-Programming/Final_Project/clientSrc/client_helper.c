#include "dropbox.h"

void init_file_info(FileInfo *fileInfo)
{
    fileInfo->count = 0;
    fileInfo->root = NULL;
    pthread_mutex_init(&fileInfo->mutex, NULL);
    pthread_cond_init(&fileInfo->empty, NULL);
}
void add_node_file_info(FileInfo *fileInfo, char *file_path, bool dir_or_not)
{
    FileInfoNode *new_node = (FileInfoNode*)malloc(sizeof(FileInfoNode));
    if(new_node == NULL)
    {
        //printf("New node can't created\n");
        exit(1);
    }
    new_node->modified_flag = false;
    new_node->added_new_or_not = false;
    new_node->deleted_count = 0;
    new_node->added_count = 0;
    new_node->other_side = false;
    new_node->deleted_or_not = false;
    new_node->next = NULL;
    //strncpy(new_node->file_path,strlen(file_path),file_path);
    snprintf(new_node->file_path,sizeof(new_node->file_path),"%s",file_path);
    new_node->dir_or_not = dir_or_not;
    pthread_mutex_lock(&fileInfo->mutex);
    if(fileInfo->count == 0)
    {
        fileInfo->root = new_node;
        fileInfo->count++;
        pthread_cond_signal(&fileInfo->empty);
        pthread_mutex_unlock(&fileInfo->mutex);
        return;
    }
    else
    {
        FileInfoNode *iter;
        iter = fileInfo->root;
        fileInfo->count++;
        while(iter != NULL && iter->next != NULL)
        {
            iter = iter->next;
        }
        if(iter != NULL)
        {
            iter->next = new_node;
            pthread_cond_signal(&fileInfo->empty);
            pthread_mutex_unlock(&fileInfo->mutex);
            return;
        }
    }
    pthread_cond_signal(&fileInfo->empty);
    pthread_mutex_unlock(&fileInfo->mutex);
}

FileInfoNode* find_node(FileInfo *fileInfo, char *file_path)
{
    pthread_mutex_lock(&fileInfo->mutex);

    if(fileInfo->root == NULL)
    {
        pthread_cond_signal(&fileInfo->empty);
        pthread_mutex_unlock(&fileInfo->mutex);
        return NULL;
    }

    
    FileInfoNode *iter = fileInfo->root;

    while(iter != NULL)
    {
        if(strcmp(iter->file_path,file_path) == 0)
        {
            pthread_cond_signal(&fileInfo->empty);
            pthread_mutex_unlock(&fileInfo->mutex);
            return iter;
        }
        iter = iter->next;
    }
    pthread_cond_signal(&fileInfo->empty);
    pthread_mutex_unlock(&fileInfo->mutex);
    return NULL;
}
void remove_node_file_info(FileInfo *fileInfo, char *file_path)
{
    pthread_mutex_lock(&fileInfo->mutex);

    if(fileInfo->root == NULL)
    {
        pthread_cond_signal(&fileInfo->empty);
        pthread_mutex_unlock(&fileInfo->mutex);
        return ;
    }
    FileInfoNode *iter = fileInfo->root;

    if(strcmp(iter->file_path,file_path) == 0)
    {
        if(iter == fileInfo->root)
        {
            fileInfo->root = fileInfo->root->next;
            free(iter);
            pthread_cond_signal(&fileInfo->empty);
            pthread_mutex_unlock(&fileInfo->mutex);
            return;
        }
    }

    while(iter->next != NULL)
    {
        if(strcmp(iter->next->file_path,file_path) == 0)
        {
            FileInfoNode *tmp;
            tmp = iter->next;
            iter->next = iter->next->next;
            fileInfo->count--;
            free(tmp);
            pthread_cond_signal(&fileInfo->empty);
            pthread_mutex_unlock(&fileInfo->mutex);
            return;
        }
        iter = iter->next;
    }
    if(strcmp(iter->file_path,file_path) == 0)
    {
        free(iter);
        pthread_cond_signal(&fileInfo->empty);
        pthread_mutex_unlock(&fileInfo->mutex);
        return;
    }

    pthread_cond_signal(&fileInfo->empty);
    pthread_mutex_unlock(&fileInfo->mutex);


}
void client_path_init(FileInfo *fileInfo,char *path)
{
    //./client_file
    DIR *dir;
    struct dirent* entry;

    dir = opendir(path);
    if(dir == NULL)
    {
        //printf("errpr path -> %s\n",path);
        //perror("dizin acilamadi\n");
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
            add_node_file_info(fileInfo,sub_path,true);
            client_path_init(fileInfo,sub_path);
        }
        else
        {
            char sub_path[PATH_MAX_LENGTH];
            snprintf(sub_path,sizeof(sub_path),"%s/%s",path,entry->d_name);
            add_node_file_info(fileInfo,sub_path,false);
        }
    }
}
void print_file_info(FileInfo *fileInfo)
{
    pthread_mutex_lock(&fileInfo->mutex);

    FileInfoNode *iter = fileInfo->root;

    if(iter == NULL)
    {
        printf("node is clear\n");
        pthread_cond_signal(&fileInfo->empty);
        pthread_mutex_unlock(&fileInfo->mutex);
        return;
    }
    
    while(iter != NULL)
    {
        printf("file name -> %s dir -> %d deleted -> %d new or not -> %d\n",iter->file_path,iter->dir_or_not,iter->deleted_or_not,iter->added_new_or_not);
        iter = iter->next;
    }
    pthread_cond_signal(&fileInfo->empty);
    pthread_mutex_unlock(&fileInfo->mutex);
}
