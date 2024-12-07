/*
** EPITECH PROJECT, 2024
** B-PSU-400-NCY-4-1-strace-teo.franoux
** File description:
** display_string_arguments
*/

#include "strace_stuff.h"
#include <sys/ptrace.h>
#include "my_syscall.h"

void display_string_format(unsigned long long start_adrr, pid_t child)
{
    long char_value = 0;
    int counter = 0;

    printf("\"");
    while (1) {
        char_value = ptrace(PTRACE_PEEKTEXT, child, start_adrr, NULL);
        if (char_value == -1) {
            perror("ptrace");
            break;
        }
        if ((char)char_value == '\0' || counter == 40) {
            break;
        }
        printf("%c", (char)char_value);
        counter++;
        start_adrr++;
    }
    printf("\"");
}

void display_with_their_type(unsigned long long start_adrr, pid_t child,
    int type)
{
    if (type == STRING) {
        display_string_format(start_adrr, child);
    } else
        printf("0x%llx", start_adrr);
}
