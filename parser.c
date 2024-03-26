#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "parser.h"

char    *strtrim(char *str)
{

    while(*str == 32)
        str++;
    return str;
}

char    **parser(char *str) 
{
    char    *str_cp;
    char    delim[] = "<>|";
    char    *token;
    char    **tokens;
    int     qtd_tokens;
    int     i;
    int     j;
    int     k;

    str_cp = malloc(sizeof(char) * strlen(str));
    assert(str_cp != NULL);
    strcpy(str_cp, str); 
    
    qtd_tokens = get_qtd_primitive_tokens(str);
    tokens = malloc(sizeof(char*) * (qtd_tokens * 2));
    assert(tokens != NULL);
    i = 0;
    token = strtok(str, delim);
    while (token != NULL)
    {
        tokens[i] = strtrim(token);
        token = strtok(NULL, delim);
        i += 2;
    }
    tokens[i] = NULL;
    k = 0;
    j = 1;
    while (str_cp[k] != '\0')
    {
        if (str_cp[k] == '>')
        {
            tokens[j] = strdup(">");
            j += 2;
        }
        if (str_cp[k] == '<')
        {
            tokens[j] = strdup("<");
            j += 2;
        }
        if (str_cp[k] == '|')
        {
            tokens[j] = strdup("|");
            j += 2;
        }
        k++;
    }
    free(str_cp);
    return tokens;
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
    return (qtd_tokens);
}

int         get_qtd_primitive_tokens(char *input)
{
    int      qtd_tokens;

    qtd_tokens = 2;
    while (*input != '\0')
    {
        if (*input == '>' || *input == '<' || *input == '|')
            qtd_tokens++;
        input++;
    }
    return (qtd_tokens);
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
