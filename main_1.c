#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


char        **get_input(char*);
int          cd(char*);
int         check_bkg(char **);
int         len_vec(char**);

int     main(void)
{
    char        **command;
    char        *input;
    pid_t       child_pid;
    int         stat_loc;
    int         bkg;

    bkg =  0;
    while (1) 
    {
        input = readline("psh> ");
        if ((input == NULL) || strlen(input) < 1) continue;
        command = get_input(input);
        bkg = check_bkg(command);
        if (strcmp(command[0], "exit") == 0) return (0);
        if (strcmp(command[0], "cd") == 0)
        {
            if ((cd(command[1])) < 0)
                perror(command[1]);
            continue;
        }
        if ((child_pid = fork()) < 0)
        {
            perror("Fork failed");
            exit(1);
        }
        if (child_pid == 0) 
        {
            if ((execvp(command[0], command)) < 0)
            {
                perror(command[0]);
                exit(1);
            }
            printf("This won't be printed if execvp is successul\n");
        }
        printf("[debug] bkg: %d\n", bkg);
        if (bkg == 0)
            waitpid(child_pid, &stat_loc, WUNTRACED);
        else 
            printf("%d %s\n", child_pid, command[0]);
    }
    free(input);
    free(command);

    return (0);
}

char   **get_input(char *input)
{
    char        **command;
    char        *separator = " ";
    char        *parsed; 
    int         index;

    while ((*input == '\n') || (*input == ' ') || (*input == '\t'))
        input++;
    // printf("[debug] Input: %s\n", input);
    command = malloc(sizeof(char*) * 8);
    parsed = strtok(input, separator);
    index = 0;
    while (parsed != NULL)
    {
        command[index] = parsed;
        index++;
        parsed = strtok(NULL, separator);
    }
    command[index] = NULL;
    return (command);
}

int     cd(char *path)
{
    return chdir(path);
}

int         len_vec(char **vec)
{
    int         i;

    i = 0;
    while (vec[i] != NULL)
        i++;
    return (i);
}

int         check_bkg(char **command)
{
    int         len;

    len = len_vec(command);
    printf("[debug] last [ %s ]\n", command[len-1]);
    if (strcmp(command[len-1], "&") == 0)
    {
        command[len-1] = NULL;
        return (1);
    }
    return (0);
}
