#ifndef PARSER_H
#define PARSER_H

#define MAX_LINE 1024

char        **parser(char*);
char        *get_input(void);
char        **get_inputs(char*);
char        **get_tokens(char*);
int         get_qtd_tokens(char*);
int         get_qtd_primitive_tokens(char*);
char        *strtrim(char*);

#endif
