

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