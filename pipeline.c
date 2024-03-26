#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <assert.h>

#include "pipeline.h"
#include "parser.h"

CMD_S       *prepare_commands(char **primitive_tokens) 
{
    CMD_S       *commands;
    int         i;
    int         k;

    commands = malloc(sizeof(CMD_S) * MAX_COMMANDS);
    i = 0;
    k = 0;
    while (primitive_tokens[i] != NULL)
    {
        commands[k] = init_command_s(primitive_tokens[i]);
        if (primitive_tokens[i + 1] != NULL)
        {
            if (strcmp(primitive_tokens[i + 1], ">") == 0)
            {
                commands[k].OUTFILE = 1;
                commands[k].outfile = strtok(strdup(primitive_tokens[i + 2]), " ");
                i += 2;
            }
            else if (strcmp(primitive_tokens[i + 1], "<") == 0)
            {
                commands[k].INFILE = 1;
                commands[k].infile = strtok(strdup(primitive_tokens[i + 2]), " ");
                i += 2;
            }
            if (primitive_tokens[i + 1] != NULL)
            {
                if (strcmp(primitive_tokens[i + 1], "|") == 0)
                {
                    commands[k].PIPE = 1;
                    i += 1;
                }
            }
        }
        i++;
        k++;
    }
    return (commands);
}

void        pipeline(char **primitive_tokens) 
{
    CMD_S       *commands;
	pid_t       pid;
    int         i;
	int         fdd;	
    int         fd[2];
    int         redirect_fd;

    i = 0;
    fdd = 0;
    commands = prepare_commands(primitive_tokens);
    assert(commands != NULL);
    free(primitive_tokens);

    // printf("\n[DEBUG SHOW COMMANDS]\n");
    // while (commands[i].cmd != NULL)
    // {
    //     printf("bin: ");
    //     print_cmd(commands[i].cmd);
    //     printf("\tPipe: %d - INFILE: %d - OUTFILE: %d - infile: %s - outfile %s\n",
    //         commands[i].PIPE, commands[i].INFILE, commands[i].OUTFILE, commands[i].infile, commands[i].outfile);
    //     i++;
    // }
    // printf("\n\n");
    i = 0;
    while (commands[i].cmd != NULL)
    {
        pipe(fd);
        if ((pid = fork()) == -1) 
        {
			perror("fork");
			exit(1);
		}
        else if (pid == 0)
        {
            if (commands[i].PIPE)
            {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]); 
            }
            else
            {
                close(fd[0]);
                close(fd[1]);
            }
            dup2(fdd, 0);
            if (commands[i].OUTFILE == 1)
            {
                redirect_fd = open(commands[i].outfile, O_WRONLY | O_CREAT, 0666);
                assert(redirect_fd != -1);
                dup2(redirect_fd, STDOUT_FILENO);
            }
            else if (commands[i].INFILE == 1)
            {
                redirect_fd = open(commands[i].infile, O_RDONLY);
                assert(redirect_fd != -1);
                dup2(redirect_fd, STDIN_FILENO);
            }
			close(fd[0]);
			execvp(commands[i].cmd[0], commands[i].cmd);
			exit(1);
        }
        else {
			wait(NULL);
			close(fd[1]);
			fdd = fd[0];
			i++;
		}
    }
    free(commands);
}

CMD_S       init_command_s(char *input)
{
    CMD_S       command;

    command.cmd = get_tokens(input);
    assert(command.cmd != NULL);
    command.PIPE = 0;
    command.INFILE = 0;
    command.OUTFILE = 0;
    command.infile = NULL;
    command.outfile = NULL;
    return (command);
}

// int         main(void)
// {
//     // char    str[] = "cat < ls.log | rev | nl > nl.log";
//     // char    str[] = "cat < ls.log ";
//     char    str[] = "cat < ls.log | rev | nl > nl.log";
//     char    **primitive_tokens;

//     primitive_tokens = parser(str);
//     pipeline(primitive_tokens);
//     return (0);
// }

void        free_commands(CMD_S commands[]) 
{
    int     i;

    i = 0;
    while (commands[i].cmd != NULL)
    {
        free_tokens(commands[i].cmd);
        free_redirects(commands[i].infile);
        free_redirects(commands[i].outfile);
        i++;
    }
}

void        free_primitive_tokens(char **primitive_tokens)
{
    int     i;

    i = 0;
    while(primitive_tokens[i] != NULL)
        free(primitive_tokens[i++]);
}

void        free_tokens(char **tokens)
{
    int         i;

    if (tokens != NULL) 
    {
        i = 0;
        while (tokens[i] != NULL) 
        {
            free(tokens[i]);
            i++;
        }
        free(tokens);
    }
}

void        free_redirects(char *redirect)
{
    if (redirect)
        free(redirect);
}

void        error_exit(char *msg)
{
    printf("[debug] %s\n", msg);
    exit(EXIT_SUCCESS);
}

void        print_cmd(char **cmd)
{
    int         i;
    
    i = 0;
    while (cmd[i])
    {
        printf("%s ", cmd[i]);
        i++;
    }
}
