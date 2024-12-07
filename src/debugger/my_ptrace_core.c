/*
** EPITECH PROJECT, 2024
** B-PSU-400-NCY-4-1-strace-teo.franoux
** File description:
** my_ptrace_core
*/

#include "my_ptrace_core.h"
#include "strace_stuff.h"
#include "handle_syscall_display.h"
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include "ftrace.h"

static void attach_pid_processus(pid_t child)
{
    int attach_result = ptrace(PTRACE_ATTACH, child, NULL, NULL);

    if (attach_result == -1) {
        if (errno == EPERM) {
            fprintf(stderr, "Vous n'avez pas les privilèges nécessaires "
                            "pour attacher le processus.\n");
        } else {
            fprintf(stderr, "strace: attach: ptrace(PTRACE_SEIZE, %d): "
                            "No such process\n", child);
        }
        free_strace_stf();
        exit(84);
    }
}

int extract_register_values(pid_t child)
{
    int status = 0;
    long rip_value = 0;
    strace_t *strace_stf = access_strace_stf();

    ptrace(PTRACE_GETREGS, child, NULL, &strace_stf->regs);
    rip_value = ptrace(PTRACE_PEEKDATA, child, strace_stf->regs.rip, NULL);
    if ((rip_value & 0xFFFF) == 0x050F && strace_stf->regs.rax != -1) {
        handle_syscall_display(child);
        display_return_value(child, &status);
    } else if ((rip_value & 0xFF) == 0xE8) {
        for (int i = 0; i < total_symbols; i++) {
            printf("symbol name: [%s] & global addr: %llx & rip_value: %lx\n", symbols[i].name, symbols[i].addr, rip_value);
            if (symbols[i].addr == strace_stf->regs.rax) {
                printf("Entering function %s at %llx\n", symbols[i].name, symbols[i].addr);
            }
        }
        ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
        waitpid(child, &status, 0);
    } else {
        ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
        waitpid(child, &status, 0);
    }
    if (WIFEXITED(status))
        return (-1);
    return (0);
}

static void run_ptrace_debugger(pid_t child)
{
    int status = 0;
    strace_t *strace_stf = access_strace_stf();

    if (strace_stf->argv_options->p_option)
        attach_pid_processus(child);
    waitpid(child, &status, 0);
    if (!WIFEXITED(status) && strace_stf->argv_options->p_option)
        printf("strace: Process %d attached\n", child);
    while (WIFSTOPPED(status)) {
        if (extract_register_values(child) < 0)
            break;
    }
    ptrace(PTRACE_DETACH, child, NULL, NULL);
}

void option_o_checker(void)
{
    strace_t *strace_stf = access_strace_stf();
    FILE *fichier = NULL;
    char *filename = strace_stf->argv_options->o_option_file;
    int fd = 0;

    if (strace_stf->argv_options->o_option) {
        fichier = fopen(filename, "w");
        if (fichier == NULL) {
            perror("-o error");
            exit(84);
        }
        fd = fileno(fichier);
        dup2(fd, STDOUT_FILENO);
    }
}

void ftrace_logic(pid_t child)
{
    int count = 0;
    MemoryRegion **exec_regions = get_executable_memory_regions(child, &count);

    if (!exec_regions) {
        printf("Aucune région de mémoire exécutable trouvée.\n");
        return;
    }
    for (int i = 0; i < count; ++i) {
        process_elf_file(exec_regions[i]);
    }
}

int my_ptrace_core(void)
{
    pid_t child = 0;
    strace_t *strace_stf = access_strace_stf();
    char *command = strace_stf->argv_options->binary;
    char **arguments = strace_stf->argv_options->b_arguments;
    
    if (strace_stf->argv_options->p_option)
        child = strace_stf->argv_options->pid_option;
    else
        child = fork();
    if (child == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        kill(getpid(), SIGSTOP);
        execvp(command, arguments);
        perror("execl");
        exit(1);
    } else {
        ftrace_logic(child);
        option_o_checker();
        run_ptrace_debugger(child);
    }
    return (0);
}
