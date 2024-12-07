/*
** EPITECH PROJECT, 2024
** B-PSU-400-NCY-4-1-strace-teo.franoux
** File description:
** o_options
*/

#include "strace_stuff.h"

int handle_option_o(const char *const *argv)
{
    strace_t *strace_stf = access_strace_stf();

    ++argv;
    strace_stf->argv_options->o_option = true;
    strace_stf->argv_options->o_option_file = (char *)*argv;
    return (1);
}
