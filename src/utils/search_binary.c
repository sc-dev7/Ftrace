/*
** EPITECH PROJECT, 2024
** handle_options_parameter
** File description:
** search_binary
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "strace_stuff.h"
#include "parameter.h"

static char *search_binary_current_directory(const char *filename)
{
    struct stat sb = {0};

    if (strchr(filename, '/') != NULL) {
        if (stat(filename, &sb) == -1) {
            print_usage_stderr();
            exit(84);
        }
        return (strdup(filename));
    }
    return (NULL);
}

char *search_binary_path(const char *filename)
{
    char *path = getenv("PATH");
    char bin_path[1024];
    struct stat sb = {0};
    char *dir = NULL;

    if (path == NULL)
        return (NULL);
    dir = strtok(path, ":");
    while (dir != NULL) {
        memset(bin_path, 0, sizeof(bin_path));
        snprintf(bin_path, sizeof(bin_path), "%s/%s", dir, filename);
        if (stat(bin_path, &sb) == 0 && S_ISREG(sb.st_mode) &&
            (sb.st_mode & S_IXUSR)) {
            return (strdup(bin_path));
        }
        dir = strtok(NULL, ":");
    }
    return (NULL);
}

int search_binary(const char *const *argv, const char *filename)
{
    char *binary_directory = search_binary_current_directory(filename);
    char *binary_in_path = search_binary_path(filename);
    strace_t *strace_stf = access_strace_stf();

    if (binary_in_path != NULL || binary_directory != NULL) {
        if (binary_in_path)
            strace_stf->argv_options->binary = binary_in_path;
        else
            strace_stf->argv_options->binary = binary_directory;
        strace_stf->argv_options->b_arguments = (char **)argv;
        return (1);
    }
    printf("strace: Can't stat '%s': No such file or directory\n", filename);
    exit(84);
    return (0);
}
