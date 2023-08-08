#include "../terminal.h"

char *create_new_log()
{
    time_t current_time;
    struct tm *local_time;
    int log_fd;


    char time_string[80];
    char dir_name[100] = "./logs/";
    char *result;


    current_time = time(NULL);
    local_time = localtime(&current_time);
    strftime(time_string, sizeof(time_string), "%Y%m%d%H%M%S", local_time);
    

    strcat(dir_name,time_string);

    log_fd = open(dir_name, O_CREAT | O_WRONLY | O_RDONLY, 0666);

    result = (char*)malloc(strlen(dir_name) + 1);
    strcpy(result,dir_name);

    
    if(log_fd == -1)
    {
        printf("Log file cannot created\n");
        return NULL;
    }
    close(log_fd);
    
    return result;
    
}