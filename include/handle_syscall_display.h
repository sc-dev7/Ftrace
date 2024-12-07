/*
** EPITECH PROJECT, 2024
** B-PSU-400-NCY-4-1-strace-teo.franoux
** File description:
** read_regs
*/

#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>

void handle_syscall_display(pid_t child);
void display_return_value(pid_t child, int *status);
void display_with_their_type(unsigned long long start_adrr, pid_t child,
    int type);
