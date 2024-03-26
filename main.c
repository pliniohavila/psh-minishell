#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <assert.h>
#include <errno.h>
#include <readline/readline.h>

#include "helpers.h"
#include "parser.h"
#include "pipeline.h"

void        exec_cmd(char**);
int         cd(char*);

int     main(void)
{
    char        *input;
    char        **inputs;
    char        **primitive_tokens;
    char        **cmd;
    int         i;

    while (1) 
    {
        input = readline("psh> ");
        if (strcmp(input, "exit") == 0) 
        {
            free(input);
            exit(EXIT_SUCCESS);
        }
        inputs = get_inputs(input); // separate by ';'
        i = 0;
        while (inputs[i] != NULL)
        {
            if ((inputs[i][0] == 'c') && inputs[i][1] == 'd')
            { 
                  cmd = get_tokens(inputs[i]); // {"ls", "-l", "-r"}
                  if (cd(cmd[1]) != 0)
                    perror(strerror(errno));
            }
            else 
            {
                primitive_tokens = parser(inputs[i]);
                print_cmd(primitive_tokens);
                pipeline(primitive_tokens); 
            }
            i++;
        }
        free(input);
    }
    return (EXIT_SUCCESS);
}

void        exec_cmd(char **cmd)
{
    int         status;
    pid_t       pid;

    if ((pid = fork()) < 0)
    {
        perror("Fork failed");
        return;
    }
    if (pid == 0) // Child 
    {
        if ((execvp(cmd[0], cmd)) < 0)
        {
            perror(strerror(errno));
            printf("[debug] execvp erro %d\n", errno);
            exit(errno);
        }
    }
    if (waitpid(pid, &status, 0) < 0)
    {
        perror(strerror(errno));
        return;
    }
}

int     cd(char *path)
{
    return chdir(path);
}