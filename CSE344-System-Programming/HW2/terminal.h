#ifndef TERMINAL_H
#define TERMINAL_H


#ifndef MAX_COMMAND_LENGTH
#define MAX_COMMAND_LENGTH 1000
#endif


#ifndef MAX_COMMAND_COUNT
#define MAX_COMMAND_COUNT 20
#endif

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <time.h>


/*===================================================================*/
/*                  ./srcs/termianl_utils.c                         */

void  terminal_prompt();
void pipe_handling(char* commands,char *dir_name);
void    execute_command(char *command,char *dir_name);
void  smaller_than_handling(char *command,char *input,char *dir_name);
void  greater_than_handling(char *command,char *output,char *dir_name);
void sigint_handler(int signo);
void sigtstp_handler(int signo);
bool checks_commands_count(char *command);
char **parse_single_line_input(char *command);
char **multiple_commend_handling(char* input);


/*===================================================================*/
/*                       ./srcs/utils.c                             */

char *remove_spaces(char *str);
bool	str_chr(const char *s, char c);


/*===================================================================*/
/*                    ./srcs/log_utils.c                            */

char *create_new_log();


/*===================================================================*/

#endif