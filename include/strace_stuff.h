/*
** EPITECH PROJECT, 2024
** handle_options_parameter
** File description:
** strace_stuff
*/

#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/user.h>
#include <gelf.h>

typedef struct options {
    bool s_option;
    bool p_option;
    bool o_option;
    bool binary_option;
    pid_t pid_option;
    char *binary;
    char *o_option_file;
    char **b_arguments;
} options_t;

typedef struct strace {
    options_t *argv_options;
    struct user_regs_struct regs;
    bool in_main;
} strace_t;

strace_t *access_strace_stf(void);
void free_strace_stf(void);
char *get_symbol_name(const char *executable, Elf64_Addr addr);
