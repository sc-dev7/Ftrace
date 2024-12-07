/*
** EPITECH PROJECT, 2024
** handle_options_parameter
** File description:
** s_option
*/

#include "strace_stuff.h"

int handle_option_s(const char *const *argv)
{
    strace_t *strace_stf = access_strace_stf();

    strace_stf->argv_options->s_option = true;
    return (0);
}
