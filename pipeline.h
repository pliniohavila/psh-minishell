#ifndef PIPELINE_H
#define PIPELINE_H

#define MAX_COMMANDS 8
typedef struct command_s
{
    char    **cmd; 
    int     PIPE; 
    int     INFILE; 
	int     OUTFILE; 
    char    *infile; 
    char    *outfile;
}               CMD_S;

void        pipeline(char**);
CMD_S       *prepare_commands(char**);
CMD_S       init_command_s(char*);
void        error_exit(char*);
void        print_cmd(char**);

void        free_commands(CMD_S[]);
void        free_primitive_tokens(char**);
void        free_tokens(char**);
void        free_redirects(char*);

#endif