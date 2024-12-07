/*
** EPITECH PROJECT, 2024
** handle_options_parameter
** File description:
** p_option
*/

#include "strace_stuff.h"
#include "parameter.h"
#include <ctype.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <errno.h>

static bool check_validity_argument(const char *argument)
{
    if (argument)
        return (true);
    return (false);
}

static void check_pid_valid(const char *next_argv)
{
    strace_t *strace_stf = access_strace_stf();

    for (int i = 0; next_argv[i]; i++) {
        if (!isdigit(next_argv[i])) {
            fprintf(stderr, "strace: pid must be only digit\n");
            exit(84);
        }
    }
    strace_stf->argv_options->pid_option = atoi(next_argv);
    strace_stf->argv_options->p_option = true;
}

int handle_option_p(const char *const *argv)
{
    const char *next_argv = *(argv + 2);

    ++argv;
    if (*argv != NULL &&
        next_argv == NULL &&
        check_validity_argument(*argv)) {
        check_pid_valid(*argv);
        return (1);
    } else {
        print_usage_stderr();
        exit(84);
    }
    return (0);
}
