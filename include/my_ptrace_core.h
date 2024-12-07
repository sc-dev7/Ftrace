/*
** EPITECH PROJECT, 2024
** B-PSU-400-NCY-4-1-strace-teo.franoux
** File description:
** my_ptrace_core
*/

#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>

int my_ptrace_core(void);
