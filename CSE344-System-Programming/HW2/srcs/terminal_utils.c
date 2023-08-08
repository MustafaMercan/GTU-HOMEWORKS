#include "../terminal.h"

void terminal_prompt()
{
    char cwd[1024];
    char user_name[1024];
    char host_name[1024];

    if(getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
    if(gethostname(host_name,sizeof(host_name)) != 0)
    {
        perror("gethostname() error");
        exit(EXIT_FAILURE);
    }
    if(getlogin_r(user_name,sizeof(user_name)) != 0)
    {
        perror("getlogin_r() error");
        exit(EXIT_FAILURE);
    }

    printf("%s@%s:%s ",user_name,host_name,cwd);
}


bool    checks_commands_count(char *command)
{
    int i;
    i = 0;
    while(command[i] != '\0')
    {
        if(command[i] == '|')
        {
            return false;
        }
        i++;
    }
    return true;
}

void    execute_command(char *command,char *dir_name)
{

    FILE *file;

    file = fopen(dir_name,"a");
    if(file == NULL)
    {
        printf("log file cannot opened\n");
    }
    else
    {
        fprintf(file,"Execute %s command in pid -> %d\n",command,getpid());
    }
    fclose(file);

    
    if(execl("/bin/sh","sh","-c",command,NULL) == -1)
    {
        perror("exec fail\n");     
        exit(EXIT_FAILURE);
    }
}

static bool checks_parameter(char *str,char c)
{
    int i;

    i = 0;
    if(str == NULL)
        return false;
    while(str[i] != '\0')
    {
        if(str[i] == c)
            return true;
        i++;
    }
    return false;
}


char **multiple_commend_handling(char* input)
{
    
    char **all_commands;
    int index = 0;
    all_commands = (char**)malloc(sizeof(char*) * 21);
    
    char *token = strtok(input,"|");
    while(token != NULL)
    {
        all_commands[index] = token;
        index++;
        token = strtok(NULL,"|");
    }
    
    all_commands[index] = NULL;
    
    return all_commands;
}
void pipe_handling(char* commands,char *dir_name)
{
    char **all_commands;
    char **my_handle;

    char *command;
    char *input;
    char *output;



    int index = 0;
    int i = 0;

    all_commands = multiple_commend_handling(commands);
    

    int tmp_input = dup(STDIN_FILENO);
    int tmp_output = dup(STDOUT_FILENO);


    while(all_commands[index] != NULL)
    {
        index++;
    }

    int pid[index];
    int pipes[index][2];
    while(i < index)
    {
        if(pipe(pipes[i]) < 0)
        {
            perror("pipe error");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    i = 0;
    while(i < index)
    {
        pid[i] = fork();
        int status;
        
        if(pid[i] == -1)
        {
            perror("pid error");
            exit(EXIT_FAILURE);
        }
        else if(pid[i] == 0)
        {

            
            my_handle = parse_single_line_input(all_commands[i]);
            

            command = my_handle[0];
            input = my_handle[1];
            output = my_handle[2];
            
            if(i != 0)
            {
                if(dup2(tmp_input,STDIN_FILENO) < 0)
                {
                    perror("dup2 error");
                    exit(EXIT_FAILURE);
                }
            }
            if(i != index - 1)
            {
                if(dup2(pipes[i][1],STDOUT_FILENO) < 0)
                {
                    perror("dup2 errro");
                    exit(EXIT_FAILURE);
                }
            }
            close(pipes[i][0]);
            close(pipes[i][1]);
        
            if(input != NULL)
            {
                input = remove_spaces(input);
                smaller_than_handling(command,input,dir_name);
                
            }
            if(output != NULL)
            {
                input = remove_spaces(output);
                greater_than_handling(command,output,dir_name);
            }

            execute_command(command,dir_name);
        }
        else
        {
            if(i != 0)
            {
                close(tmp_input);
            }
            if(i != index - 1)
            {
                tmp_input = pipes[i][0];
                close(pipes[i][1]);
            }
            waitpid(pid[i],&status,0);
        }
        i++;
    }



}
char **parse_single_line_input(char *command)
{
    int index = 0;
    int i = 0;

    char** result;



    result = (char**)malloc(sizeof(char*) * 4);

    int size = strlen(command);
    char *token;
    

    if(!str_chr(command,'<') & !str_chr(command,'>'))
    {
        result[0] = command;
        result[1] = NULL;
        result[2] = NULL;
        result[3] = NULL;
        return result;
    }
    else if(str_chr(command,'<'))
    {
        token = strtok(command, "<");
        while(token != NULL)
        {
            if(i == 0)
                result[0] = token;
            i++;
            if(str_chr(token,'>'))
            {
                token = strtok(token,">");
                
                result[1] = token;
                token = strtok(NULL,">");
                result[2] = token;
            }
            else
            {
                result[1] = token;
                result[2] = NULL;
            }
            token = strtok(NULL,"<");
        }
    }
    else
    {
        token = strtok(command,">");
        if(i == 0)
            result[0] = token;
        i++;
        token = strtok(NULL,">");
        result[2] = token;
        result[1] = NULL;
    }
    return result;

}

/* < operator */
void  smaller_than_handling(char *command,char *input,char *dir_name)
{
    FILE *file;

    file = fopen(dir_name,"a");
    if(file == NULL)
    {
        printf("log file cannot opened\n");
    }
    else
    {
        fprintf(file,"Input redirection has been set up for %s with %s.\"(<) process \" for command -> %s in pid -> %d\n",command,input,command,getpid());
    }
    fclose(file);


    int fd = open(input, O_RDONLY,0666);
    if (fd == -1) 
    {
        perror("file cannot open");
        exit(EXIT_FAILURE);
    }

    int tmp_stdin = dup(STDIN_FILENO);

    if (tmp_stdin == -1) 
    {
        perror("Error: Standard input stream could not be backed up.");
        exit(EXIT_FAILURE);
    }

    if (dup2(fd, STDIN_FILENO) == -1) 
    {
        perror("Error: Could not copy file to standard input stream.");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

void  greater_than_handling(char *command,char *output,char *dir_name)
{   
    FILE *file;

    file = fopen(dir_name,"a");
    if(file == NULL)
    {
        printf("Log file cannot opened\n");
    }
    else
    {
        fprintf(file,"Output redirection has been set up for %s with %s.\"(>) process \" for command -> %s in pid -> %d\n",command,output,command,getpid());
    }
    fclose(file);


    int fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) 
    {
        perror("file cannot open");
        exit(EXIT_FAILURE);
    }

    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2() fail");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

void sigint_handler(int signo)
{
    printf("\nSIGINT signal received!\n");
    terminal_prompt();
}

void sigtstp_handler(int signo)
{
    printf("\nSIGTSTP signal received!\n");
    terminal_prompt();
}
