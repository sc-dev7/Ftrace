/*
** EPITECH PROJECT, 2024
** handle_options_parameter
** File description:
** strace_stuff
*/

#include "strace_stuff.h"

static strace_t *init_strace_stuff(void)
{
    strace_t *strace_stf = malloc(sizeof(strace_t));

    strace_stf->argv_options = malloc(sizeof(options_t));
    strace_stf->argv_options->p_option = false;
    strace_stf->argv_options->o_option = false;
    strace_stf->argv_options->s_option = false;
    strace_stf->argv_options->binary_option = false;
    strace_stf->argv_options->binary = NULL;
    strace_stf->argv_options->b_arguments = NULL;
    strace_stf->argv_options->o_option_file = NULL;
    strace_stf->in_main = false;
    return (strace_stf);
}

strace_t *access_strace_stf(void)
{
    static strace_t *strace_stf = NULL;

    if (strace_stf == NULL)
        strace_stf = init_strace_stuff();
    return (strace_stf);
}

void free_strace_stf(void)
{
    strace_t *strace_stf = access_strace_stf();

    if (strace_stf == NULL)
        return;
    free(strace_stf);
}
