#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

void            error_exit(char *msg)
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