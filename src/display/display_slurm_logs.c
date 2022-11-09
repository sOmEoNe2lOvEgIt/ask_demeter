// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such logs, much display!
//___________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include "ask_demeter.h"

int display_slurm_logs(parsed_hostname_json_t *parsed_json)
{
    if (!parsed_json)
        return (1);
    printf("\n\n\n");
    print_line(100, false);
    printf ("\t\t%s SLURM LOGS:\n", parsed_json->hostname);
    print_line(100, false);
    printf ("%s", parsed_json->slurm_logs);
    print_line(100, false);
    return (0);
}

int display_slurm_logs_all_nodes(linked_list_t *host_list)
{
    parsed_hostname_json_t *parsed_json = NULL;
    linked_list_t *tmp = NULL;
    int size = 0;

    if (!host_list)
        return (1);
    size = get_list_size(host_list);
    for (int i = 0; i < size; i++) {
        if (!(tmp = get_first_host_after_hostname(host_list, parsed_json ? parsed_json->hostname : "")))
            continue;
        if (!(parsed_json = (parsed_hostname_json_t *)tmp->data))
            continue;
        if (display_slurm_logs(parsed_json))
            return (1);
    }
    return (0);
}