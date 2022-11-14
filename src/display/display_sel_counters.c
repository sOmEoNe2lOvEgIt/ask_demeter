// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such json, much handle!
//___________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include "gather_ib.h"
#include "ask_demeter.h"

static perf_data_t *get_sel_from_json(char *json)
{
    perf_data_t *perf_data = NULL;
    json_object *parsed_json = NULL, *hits = NULL;

    printf ("json: %s\n", json);
    if (!(parsed_json = json_tokener_parse(json)))
        return (NULL);
    if (!(perf_data = malloc(sizeof(perf_data_t))))
        return (NULL);
    if (!(hits = json_object_object_get(parsed_json, "hits")))
        return (NULL);
    printf ("Hits: %s\n", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
    return (perf_data);
} 

int display_sel_counters_tab_all_nodes(linked_list_t *host_list, ask_demeter_args_t *demeter_args)
{
    parsed_hostname_json_t *node = NULL;
    linked_list_t *tmp = NULL;
    perf_data_t *perf_data = NULL;
    char *perf_data_str = NULL;

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
        if (!(perf_data_str = node->sel_counters))
            continue;
        else
            get_sel_from_json(perf_data_str);
    }
    print_line(87, false);
    return (0);
}