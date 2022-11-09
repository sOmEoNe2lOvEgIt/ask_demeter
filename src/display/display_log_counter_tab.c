// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such json, much handle!
//___________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include "ask_demeter.h"

int display_log_counter_tab_all_nodes(linked_list_t *host_list, ask_demeter_args_t *demeter_args, bool is_syslog)
{
    parsed_hostname_json_t *node = NULL;
    linked_list_t *tmp = NULL;
    log_counter_t *log_counter = NULL;
    int size = 0;

    print_line(87, false);
    printf("│      Hostname     │   Errors   │  Warnings  │    Infos   │   Debugs   │   Fatals   │\n");
    print_line(87, false);
    size = get_list_size(host_list);
    for (int i = 0; i < size; i++)
    {
        if (!(tmp = get_first_host_after_hostname(host_list, node ? node->hostname : "")))
            continue;
        if (!(node = (parsed_hostname_json_t *)tmp->data))
            continue;
        if (is_syslog)
            log_counter = node->sys_log_counter;
        else
            log_counter = node->slurm_log_counter;
        if (!log_counter)
            continue;
        printf("│   %14s  │ %10d │ %10d │ %10d │ %10d │ %10d │\n", node->hostname, log_counter->errors, log_counter->warnings, log_counter->infos, log_counter->debugs, log_counter->fatals);
    }
    print_line(87, false);
    return (0);
}