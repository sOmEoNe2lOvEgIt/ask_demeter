// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such get, much list, such size!
//___________________________________________________________________________________________________________________________________________


#include <stdio.h>
#include "ask_demeter.h"

uint get_list_size (linked_list_t *list)
{
    int size = 0;

    for (; list; list = list->next)
        size++;
    return (size);
}