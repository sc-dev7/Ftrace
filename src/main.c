/*
** EPITECH PROJECT, 2024
** handle_options_parameter
** File description:
** main
*/

#include <stdio.h>
#include "parameter.h"
#include "my_ptrace_core.h"

int main(const int argc, const char *const argv[])
{
    if (argc < 2) {
        print_usage_stderr();
        return (84);
    }
    parameter_options_process(argv);
    my_ptrace_core();
    return (0);
}
