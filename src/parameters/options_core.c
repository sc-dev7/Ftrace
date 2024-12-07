/*
** EPITECH PROJECT, 2024
** handle_options_parameter
** File description:
** get_options_core
*/

#include "parameter.h"
#include "search_binary.h"
#include "strace_stuff.h"

static int verify_option(const char *const *argv, const char *arg)
{
    for (int j = 0; options_handlers[j].option; j++) {
        if (strcmp(options_handlers[j].option, arg) == 0) {
            return options_handlers[j].handler(argv);
            return (1);
        }
    }
    if (arg[0] == '-') {
        print_usage_stderr();
        exit(84);
    }
    search_binary(argv, arg);
    return (0);
}

void parameter_options_process(const char *const *argv)
{
    strace_t *strace_stf = access_strace_stf();

    for (int i = 1; argv[i]; i++) {
        i += verify_option(argv + i, argv[i]);
        if (strace_stf->argv_options->binary ||
            strace_stf->argv_options->p_option)
            break;
    }
    if (strace_stf->argv_options->binary == NULL &&
        !strace_stf->argv_options->p_option &&
        strace_stf->argv_options->pid_option == 0) {
        printf("Coucou\n");
        print_usage_stderr();
        exit(84);
    }
}
