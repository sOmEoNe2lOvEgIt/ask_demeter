// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such logs, much display!
//___________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include "ask_demeter.h"

int display_slurm_sys_logs(parsed_hostname_json_t *parsed_json)
{
    if (!parsed_json)
        return (1);
    printf ("\n%s LOGS:\n%s\n", parsed_json->hostname, parsed_json->sys_slurm_logs);
    return (0);
}

int display_slurm_sys_logs_all_nodes(linked_list_t *parsed_json_list)
{
    parsed_hostname_json_t *parsed_json = NULL;

    if (!parsed_json_list)
        return (1);
    while (parsed_json_list) {
        parsed_json = (parsed_hostname_json_t *)parsed_json_list->data;
        if (display_slurm_sys_logs(parsed_json))
            return (1);
        parsed_json_list = parsed_json_list->next;
    }
    return (0);
}