#include "pipeline.h"
#include "parser.h"
// #include "helpers.c"

int         main(void)
{
    // char    str[] = "cat < ls.log | rev | nl > nl.log";
    // char    str[] = "cat < ls.log ";
    char    str[] = "cat < ls.log | rev | nl > nl.log";
    char    **primitive_tokens;

    primitive_tokens = parser(str);
    // print_cmd(primitive_tokens);
    pipeline(primitive_tokens);
    return (0);
}