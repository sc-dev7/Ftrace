/*
** EPITECH PROJECT, 2024
** B-PSU-400-NCY-4-1-ftrace-sofiane.chabane
** File description:
** elf_symbols
*/

#include "ftrace.h"

Symbol symbols[MAX_SYMBOLS];
int total_symbols = 0;

void process_symbols(Elf64_Sym *symtab, char *strtab, unsigned long long base, Elf64_Word num_symbols)
{
    for (int i = 0; i < num_symbols; i++, total_symbols++)
    {
        unsigned long long addr = base + symtab[i].st_value;
        char *name = strtab + symtab[i].st_name;
        Symbol symbol_register = {addr, strdup(name)};
        symbols[total_symbols] = symbol_register;
    }
}

Elf64_Word get_num_symbols(Elf64_Shdr *section_header)
{
    if (section_header->sh_size % sizeof(Elf64_Sym) != 0)
        return 0;
    return section_header->sh_size / sizeof(Elf64_Sym);
}

void process_elf_file(MemoryRegion *elf_file)
{
    struct stat file_stat;
    if (stat(elf_file->filename, &file_stat) == -1)
    {
        perror("Error getting file size");
        exit(EXIT_FAILURE);
    }

    int fd = open(elf_file->filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening ELF file");
        exit(EXIT_FAILURE);
    }

    off_t length = file_stat.st_size;
    void *mapping = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapping == MAP_FAILED)
    {
        perror("Error mapping ELF file into memory");
        close(fd);
        exit(EXIT_FAILURE);
    }
    Elf64_Ehdr *header = (Elf64_Ehdr *)mapping;

    if (header->e_ident[EI_MAG0] != ELFMAG0 ||
        header->e_ident[EI_MAG1] != ELFMAG1 ||
        header->e_ident[EI_MAG2] != ELFMAG2 ||
        header->e_ident[EI_MAG3] != ELFMAG3)
    {
        fprintf(stderr, "Not an ELF file\n");
        munmap(mapping, length);
        close(fd);
        return;
    }

    Elf64_Off sh_offset = header->e_shoff;
    Elf64_Half sh_size = header->e_shentsize;

    Elf64_Sym *symtab = NULL;
    char *strtab = NULL;
    Elf64_Sym *dynsym = NULL;
    char *dynstr = NULL;
    Elf64_Word num_symbols = 0;
    Elf64_Word num_dyn_symbols = 0;

    Elf64_Shdr *sec_header = (Elf64_Shdr *)(mapping + header->e_shoff);
    char *section_names = (char *)(mapping + sec_header[header->e_shstrndx].sh_offset);

    for (int i = 0; i < header->e_shnum; i++)
    {
        Elf64_Shdr *section_header = (Elf64_Shdr *)((char *)mapping + sh_offset + i * sh_size);
        Elf64_Off symtab_offset = section_header->sh_offset;
        char *section_name_select = section_names + section_header->sh_name;
        if (strcmp(section_name_select, ".symtab") == 0) {
            symtab = (Elf64_Sym *)((char *)mapping + symtab_offset);
            num_symbols = get_num_symbols(section_header);
        } else if (strcmp(section_name_select, ".dynsym") == 0) {
            dynsym = (Elf64_Sym *)((char *)mapping + symtab_offset);
            num_dyn_symbols = get_num_symbols(section_header);
        } else if (strcmp(section_name_select, ".strtab") == 0) {
            strtab = (char *)mapping + symtab_offset;
        } else if (strcmp(section_name_select, ".dynstr") == 0) {
            dynstr = (char *)mapping + symtab_offset;
        }
    }
    if (symtab && strtab)
        process_symbols(symtab, strtab, elf_file->start_addr + elf_file->offset, num_symbols);
    if (dynsym && dynstr)
        process_symbols(dynsym, dynstr, elf_file->start_addr + elf_file->offset, num_dyn_symbols);
    munmap(mapping, length);
    close(fd);
}
