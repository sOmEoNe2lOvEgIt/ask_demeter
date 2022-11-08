// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such get, much hostname, very first!
//___________________________________________________________________________________________________________________________________________


#include <stdio.h>
#include <json-c/json.h>
#include "ask_demeter.h"

linked_list_t *get_first_host_after_hostname(linked_list_t *list, char *best_hostname)
{
    linked_list_t *tmp = NULL, *tmp_best = NULL;

    if (!list || !best_hostname)
        return (NULL);
    for (tmp = list; tmp && tmp->data; tmp = tmp->next){
        if (((parsed_hostname_json_t *)tmp->data)->hostname &&
        strcmp(best_hostname, ((parsed_hostname_json_t *)tmp->data)->hostname) < 0){
            if (!tmp_best)
                tmp_best = tmp;
            if (tmp_best && ((parsed_hostname_json_t *)tmp_best->data)->hostname &&
            strcmp(((parsed_hostname_json_t *)tmp_best->data)->hostname,
            ((parsed_hostname_json_t *)tmp->data)->hostname) > 0)
                tmp_best = tmp;
        }
    }
    return (tmp_best);
}
