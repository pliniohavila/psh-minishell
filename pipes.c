#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define MAX_LINE 1024

int     main(void)
{
    // int     n;
    int     fd[2];
    pid_t   pid;
    char    line[MAX_LINE];

    if ((pipe(fd)) < 0)
    {
        perror(strerror(errno));
        return (1);
    }

    if ((pid = fork()) < 0)
    {
        perror(strerror(errno));
        return (1);
    }

    if (pid == 0)
    {
        close(fd[1]);
        read(fd[0], line, MAX_LINE);
        printf("Read from child: %s\n", line);
    }
    else 
    {
        close(fd[0]);
        write(fd[1], "Hey baby!!!", 12);
    }
    return (0);
}