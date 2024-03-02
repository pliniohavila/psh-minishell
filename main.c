#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <assert.h>
#include <errno.h>


#define MAX_LINE 1024

char        **get_tokens(char*);
int         get_qtd_tokens(char*);
void        m_exit(char*);
void        print_cmd(char**);
char        *get_input(void);
char        **get_inputs(char*);
void        exec_cmd(char**);
int         cd(char*);


int     main(void)
{
    char        *input;
    char        **inputs;
    char        **cmd;
    int         i;

    while (1) 
    {
        printf("psh > ");
        fflush(stdout);      
        input = get_input();
        if (strcmp(input, "exit") == 0) 
        {
            free(input);
            exit(EXIT_SUCCESS);
        }
        inputs = get_inputs(input);
        // print_cmd(inputs);
        i = 0;
        while (inputs[i] != NULL)
        {
            cmd = get_tokens(inputs[i]);
            // print_cmd(cmd);
            if (strcmp(cmd[0], "cd") == 0)
            {
                 if (cd(cmd[1]) != 0)
                    perror(strerror(errno));
            }
            else 
                exec_cmd(cmd);
            free(cmd);
            i++;
        }
        free(input);
        free(inputs);
    }
    // free(input);
    // free(inputs);
    // free(cmd);
    return (EXIT_SUCCESS);
}

char        *get_input(void)
{
    char        *input;
    size_t      len_line;
    size_t      len_input;
    
    input = NULL;
    len_line = MAX_LINE;
    len_input = getline(&input, &len_line, stdin);  
    input[len_input - 1] = '\0';
    if (feof(stdin))
    {
        free(input);
        exit(EXIT_SUCCESS);
    }
    return (input);
}

char        **get_inputs(char *input)
{
    char        **vec_inputs;
    char        *input_parsed;
    int         i;
    int         l;

    vec_inputs = calloc(sizeof(char*), 6);
    assert(vec_inputs != NULL);
    i = 0;
    l = 0;
    input_parsed = strtok(input, ";");
    while ((input_parsed != NULL) && (i < 5))
    {
        while (*input_parsed == ' ')
            input_parsed++;
        l = strlen(input_parsed);
        input_parsed[l] = '\0';
        vec_inputs[i] = input_parsed;
        input_parsed = strtok(NULL, ";");
        i++;
    }
    vec_inputs[i] = NULL;
    return (vec_inputs);
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
    // printf("waitpid status => %d\n", status);
}


int         get_qtd_tokens(char *input)
{
    int      qtd_tokens;

    // Case has one token plus null terminator 
    qtd_tokens = 2;
    while (*input != '\0')
    {
        if (*input == 32)
            qtd_tokens++;
        input++;
    }
    return(qtd_tokens);
}

char        **get_tokens(char *input)
{
    char        **tokens;
    char        *token;
    int         qtd_tokens;
    int         i;
   

    while ((*input == ' ') || (*input == '\t'))
        input++;
    qtd_tokens = get_qtd_tokens(input);
    tokens = malloc(sizeof(char*) * qtd_tokens);
    assert(tokens != NULL);
    token = strtok(input, " ");
    i = 0;
    while (token != NULL)
    {
        tokens[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    tokens[i] = NULL;
    return (tokens);
}

int     cd(char *path)
{
    return chdir(path);
}

void            m_exit(char *msg)
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
        printf("[debug] cmd[%d] = %s\n", i, cmd[i]);
        i++;
    }
}