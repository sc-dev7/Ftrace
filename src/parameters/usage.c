/*
** EPITECH PROJECT, 2024
** handle_options_parameter
** File description:
** usage
*/

#include "strace.h"
#include "strace_stuff.h"

void print_usage_stdout(void)
{
    printf("USAGE: ftrace <command>\n");
}

void print_usage_stderr(void)
{
    fprintf(stderr, "USAGE: ftrace <command>\n");
    free_strace_stf();
}
