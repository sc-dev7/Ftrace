/*
** EPITECH PROJECT, 2024
** my_strace
** File description:
** handle_syscall_display
*/

/*
** EPITECH PROJECT, 2024
** B-PSU-400-NCY-4-1-strace-teo.franoux
** File description:
** read_regs
*/

#include "handle_syscall_display.h"
#include "my_syscall.h"
#include "strace_stuff.h"

void display_return_value(pid_t child, int *status)
{
    struct user_regs_struct regs = {0};

    ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
    waitpid(child, status, 0);
    ptrace(PTRACE_GETREGS, child, NULL, &regs);
    printf(": 0x%llx\n", regs.rax);
}

void display_syscall_argument(struct user_regs_struct *regs, pid_t child)
{
    unsigned long long reg[] = {regs->rdi, regs->rsi, regs->rdx, regs->r10,
        regs->r8, regs->r9};
    int arg_type[] = {table[regs->rax].arg1_type, table[regs->rax].arg2_type,
        table[regs->rax].arg3_type, table[regs->rax].arg4_type,
        table[regs->rax].arg5_type, table[regs->rax].arg6_type};
    int number_args = table[regs->rax].total_arguments;
    bool s_option = access_strace_stf()->argv_options->s_option;

    for (int i = 0; i < number_args; i++) {
        if (s_option) {
            display_with_their_type(reg[i], child, arg_type[i]);
        } else {
            printf("0x%llx", reg[i]);
        }
        if (i + 1 < number_args)
            printf(", ");
    }
}

void handle_syscall_display(pid_t child)
{
    strace_t *strace_stf = access_strace_stf();
    struct user_regs_struct *regs = &strace_stf->regs;

    for (int i = 0; table[i].syscall_name; i++) {
        if (table[i].syscall_id == regs->rax) {
            printf("%s(", table[i].syscall_name);
            display_syscall_argument(regs, child);
            printf(")");
            return;
        }
    }
    printf("Unknow ");
}
