#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


static int pipefd1[2], pipefd2[2];


void TELL_WAIT(void){
    if(pipe(pipefd1)<0 || pipe(pipefd2)<0){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}

void TELL_PARENT(void){
  /* send parent a message through pipe, need you to complete*/
    printf("Child send message to parent!\n");
}

void WAIT_PARENT(void){
  /* read message sent by parent from pipe, need you to complete*/
    printf("Child receive message from parent!\n");
}

void TELL_CHILD(void){
  /* send child a message through pipe, need you to complete*/
    printf("Parent send message to child!\n");
}

void WAIT_CHILD(void){
  /* read the message sent by child from pipe, need you to complete*/
    printf("Parent receive message from child!\n");
}

int main(void)
{
    pid_t       pid;
    char        buf[10];
    // char        buf2[10];

    TELL_WAIT();
    pid = fork();
    alarm(10);
    memset(buf, 0, 10);
    // memset(buf2, 0, 10);
    if (pid == 0)
    {
        while(1)
        {
            sleep((rand() % 2) + 1);        
            TELL_CHILD();
            write(pipefd2[1], "Paiiee", 6);
            WAIT_CHILD();
            read(pipefd1[0], buf, 8);
            printf("\nCHILD read from pipe: %s\n", buf);
            // write(pipefd1[1], "Filhooo", 8);
        }
    }
    else
    {
        while(1)
        {
            sleep(rand()%2+1);
            WAIT_PARENT();
            read(pipefd2[0], buf, 6);
            printf("\nPARENT read from pipe: %s\n", buf);
            TELL_PARENT();
            write(pipefd1[1], "Filhooo", 8);
        }
      }
    return (0);
}