

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
