#include "dropbox.h"

void init_file_info(FileInfo *fileInfo) //kullaniliyor
{
    fileInfo->count = 0;
    fileInfo->root = NULL;
    pthread_mutex_init(&fileInfo->mutex, NULL);
    pthread_cond_init(&fileInfo->empty, NULL);
}

void add_node_file_info(FileInfo *fileInfo, char *file_path, bool dir_or_not) //kullaniliyor
{
    FileInfoNode *new_node = (FileInfoNode*)malloc(sizeof(FileInfoNode));
    if(new_node == NULL)
    {
        printf("New node can't created\n");
        exit(1);
    }
    new_node->modified_count = 0;
    new_node->modified_flag = false;
    new_node->added_new_or_not = false;
    new_node->deleted_count = 0;
    new_node->added_count = 0;
    new_node->other_side = false;
    new_node->deleted_or_not = false;
    new_node->next = NULL;
    snprintf(new_node->file_path,sizeof(new_node->file_path),"%s",file_path);
    new_node->dir_or_not = dir_or_not;
    
    if(fileInfo->count == 0)
    {
        fileInfo->root = new_node;
        fileInfo->count++;
        
        
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
            
            
            return;
        }
    }
    
    
}

void remove_node_file_info(FileInfo *fileInfo, char *file_path)//kullaniliyor
{
    

    if(fileInfo->root == NULL)
    {
        printf("node clear \n");
        
        
        return ;
    }
    FileInfoNode *iter = fileInfo->root;

    if(strcmp(iter->file_path,file_path) == 0)
    {
        if(iter == fileInfo->root)
        {
            fileInfo->root = fileInfo->root->next;
            free(iter);
            
            
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
            printf("node kaldirildi\n");
            
            
            return;
        }
        iter = iter->next;
    }
    if(strcmp(iter->file_path,file_path) == 0)
    {
        free(iter);
        
        
        //printf("node kaldirildi\n");
        return;
    }

    //printf("Node bulunamadi\n");
    
}
FileInfoNode* find_node(FileInfo *fileInfo, char *file_path)//kullaniliyor
{
    

    if(fileInfo->root == NULL)
    {
        
        
        printf("node clear \n");
        return NULL;
    }

    
    FileInfoNode *iter = fileInfo->root;

    while(iter != NULL)
    {
        if(strcmp(iter->file_path,file_path) == 0)
        {
            
            
            return iter;
        }
        iter = iter->next;
    }
    
    
    return NULL;
}






void server_path_init(FileInfo *fileInfo,char *path)
{
    //./server_file
    DIR *dir;
    struct dirent* entry;

    dir = opendir(path);
    if(dir == NULL)
    {
        printf("errpr path -> %s\n",path);
        perror("dizin acilamadi\n");
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
            server_path_init(fileInfo,sub_path);
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
    

    FileInfoNode *iter = fileInfo->root;

    if(iter == NULL)
    {
        //printf("node is clear\n");
        return;
    }
    
    while(iter != NULL)
    {
        printf("file name -> %s dir -> %d deleted -> %d modified - > %d new or not -> %d\n",iter->file_path,iter->dir_or_not,iter->deleted_or_not,iter->modified_flag,iter->added_new_or_not);
        iter = iter->next;
    }
    
    
}