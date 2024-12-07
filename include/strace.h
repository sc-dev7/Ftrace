/*
** EPITECH PROJECT, 2024
** strace_bootstrap
** File description:
** strace
*/

#pragma once

#include <stdbool.h>
#include <sys/types.h>

typedef struct syscall {
    unsigned long long syscall_id;
    char *syscall_name;
    int total_arguments;
    int return_value_type;
    int arg1_type;
    int arg2_type;
    int arg3_type;
    int arg4_type;
    int arg5_type;
    int arg6_type;
} syscall_t;

