// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such json, much handle!
//___________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include "ask_demeter.h"

int display_log_counter_tab_all_nodes(linked_list_t *host_list, ask_demeter_args_t *demeter_args)
{
    parsed_hostname_json_t *node = NULL;
    linked_list_t *tmp = NULL;
    log_counter_t *log_counter = NULL;

    print_line(87, false);
    printf("│      Hostname     │   Errors   │  Warnings  │    Infos   │   Debugs   │   Fatals   │\n");
    print_line(87, false);
    for (tmp = host_list; tmp && tmp->data; tmp = tmp->next)
    {
        if (!(node = (parsed_hostname_json_t *)tmp->data))
            continue;
        if (!(log_counter = node->log_counter))
            continue;
        if (demeter_args->node_set && !is_in_nodeset(node->hostname, demeter_args->node_set))
            continue;
        printf("│   %14s  │ %10d │ %10d │ %10d │ %10d │ %10d │\n", node->hostname, node->log_counter->errors, node->log_counter->warnings, node->log_counter->infos, node->log_counter->debugs, node->log_counter->fatals);
    }
    print_line(87, false);
    return (0);
}