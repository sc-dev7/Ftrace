/*
** EPITECH PROJECT, 2024
** handle_options_parameter
** File description:
** help_option
*/

#include <stdio.h>
#include "parameter.h"

int handle_option_help(const char *const *argv)
{
    printf("USAGE: ./strace [-s] [-p <pid>|<command>]\n");
    exit(0);
}
