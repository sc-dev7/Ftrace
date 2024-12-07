/*
** EPITECH PROJECT, 2024
** B-PSU-400-NCY-4-1-ftrace-sofiane.chabane
** File description:
** handle_maps
*/

#include "ftrace.h"

MemoryRegion **get_executable_memory_regions(pid_t pid, int *count)
{
    char proc_path[64];
    snprintf(proc_path, sizeof(proc_path), "/proc/%d/maps", pid);

    FILE *file = fopen(proc_path, "r");
    if (!file)
    {
        perror("Error opening maps file");
        return NULL;
    }

    int exec_count = 0;
    MemoryRegion **exec_regions = NULL;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file))
    {
        unsigned long long start, end;
        off_t offset;
        char filename[256];

        if (sscanf(line, "%llx-%llx r-xp %lx %*s %*s %255s", &start, &end, &offset, filename) != 4)
        {
            continue;
        }
        if (strstr(line, "r-x") != NULL && strstr(line, " 0 ") == NULL)
        {
            MemoryRegion *region = malloc(sizeof(MemoryRegion));
            if (!region)
            {
                perror("Error allocating memory");
                fclose(file);
                return NULL;
            }
            region->start_addr = start;
            region->end_addr = end;
            region->offset = offset;
            strncpy(region->filename, filename, sizeof(region->filename));
            exec_regions = realloc(exec_regions, (exec_count + 1) * sizeof(MemoryRegion *));
            if (!exec_regions)
            {
                perror("Error reallocating memory");
                fclose(file);
                return NULL;
            }
            exec_regions[exec_count++] = region;
        }
    }
    fclose(file);
    *count = exec_count;
    return exec_regions;
}
