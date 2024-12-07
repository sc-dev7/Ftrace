/*
** EPITECH PROJECT, 2024
** handle_options_parameter
** File description:
** parameter
*/

#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parameter_options_process(const char *const *argv);

void print_usage_stdout(void);
void print_usage_stderr(void);

int handle_option_p(const char *const *argv);
int handle_option_s(const char *const *argv);
int handle_option_o(const char *const *argv);
int handle_option_help(const char *const *argv);

typedef struct options_handler {
    char *option;
    int (*handler)(const char *const *);
} options_handler_t;

static const options_handler_t options_handlers[] = {
    {"-s", handle_option_s},
    {"-p", handle_option_p},
    {"-o", handle_option_o},
    {"--help", handle_option_help},
    {"-h", handle_option_help},
    {NULL, NULL},
};
