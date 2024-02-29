#include <stdio.h>
#include <string.h>


int     main(void)
{
    char    *str;
    char    *delim;
    char    *token;
    int     i;

    str = strdup("Acabei de passar um café, oba.");
    delim = " ";
    i = 0;
    token = strtok(str, delim);
    while (token != NULL) 
    {
        printf("Token [%d] = %s\n", i, token);
        token = strtok(NULL, delim);
        i++;
    }
    return (0);
}