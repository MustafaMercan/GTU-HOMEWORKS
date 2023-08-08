#include "terminal.h"
int main()
{
    char command [MAX_COMMAND_LENGTH];
    bool one_command_or_not;
    pid_t pid;

    char **parse_command;
    int i = 0;
    char *dir_name;


    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
  
    

    printf("\n\nWELCOME MINI TERMINAL\n\n");

    dir_name = create_new_log();

    while(1)
    {
        terminal_prompt();
        fflush(stdout);

        if(fgets(command,MAX_COMMAND_LENGTH,stdin) == NULL)
        {
            perror("fgets error");
            exit(EXIT_FAILURE);
        }
        if(strcmp(command,":q\n") == 0)
        {
            printf("\nTerminal has been terminated.\n");
            free(dir_name);
            exit(EXIT_SUCCESS);
        }
        command[strcspn(command,"\n")] = '\0';
        pid = fork();
        if(pid < 0)
        {
            perror("main fork fail");
            exit(EXIT_FAILURE);
        }
        else if(pid == 0)
        {
            
            one_command_or_not = checks_commands_count(command);
            
            if(one_command_or_not == true)
            {
                parse_command = parse_single_line_input(command);
             
                if(parse_command[0] == NULL)
                {
                    perror("Please enter a command");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    parse_command[0][strcspn(parse_command[0],"\n")] = '\0';
                    if(parse_command[1] != NULL)
                    {
                        parse_command[1][strcspn(parse_command[1],"\n")] = '\0';
                        parse_command[1] = remove_spaces(parse_command[1]);
                        smaller_than_handling(parse_command[0],parse_command[1],dir_name);
                    }
                    if(parse_command[2] != NULL)
                    {
                        parse_command[2][strcspn(parse_command[2],"\n")] = '\0';
                        parse_command[2] = remove_spaces(parse_command[2]);
                        greater_than_handling(parse_command[0],parse_command[2],dir_name);
                    }
                    
                    execute_command(parse_command[0],dir_name);
                }
            }
            else
            {
                pipe_handling(command,dir_name);
            }
            exit(EXIT_SUCCESS);
        }
        else
        {
            int status;
            wait(&status);
            if(WIFEXITED(status))
            {
                //Child process exited normally
            }
            else
                perror("main parent process wait fail");
        }
        i++;
    }
    free(dir_name);
    return 0;
}