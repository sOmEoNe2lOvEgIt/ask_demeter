// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such line, much print!
//___________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void print_line(int len, bool tab)
{
    char *line = NULL;

    if (!(line = malloc(sizeof(char) * len)))
        return;
    memset(line, '_', len - 1);
    line[len - 1] = '\n';
    line[len] = '\0';
    if (tab)
        printf("\t%s", line);
    else
        printf("%s", line);
    free(line);
}