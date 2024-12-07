/*
** EPITECH PROJECT, 2024
** B-PSU-400-NCY-4-1-ftrace-sofiane.chabane
** File description:
** ftrace
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define MAX_LINE_LENGTH 512
#define MAX_SYMBOLS 5000

typedef struct
{
    unsigned long long start_addr;
    unsigned long long end_addr;
    off_t offset;
    unsigned long long global_addr;
    char filename[256];
} MemoryRegion;

typedef struct
{
    unsigned long long addr;
    char *name;
} Symbol;

extern Symbol symbols[MAX_SYMBOLS];
extern int total_symbols;
void process_elf_file(MemoryRegion *elf_file);
MemoryRegion **get_executable_memory_regions(pid_t pid, int *count);
