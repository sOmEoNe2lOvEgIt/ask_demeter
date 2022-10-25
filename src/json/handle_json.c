// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such json, much handle!
//___________________________________________________________________________________________________________________________________________

#define _GNU_SOURCE
#include <stdio.h>
#include <json-c/json.h>
#include "ask_demeter.h"

static int freeturn_json_object(struct json_object *obj, int ret, char *step_key)
{
    while (json_object_put(obj) != 1);
    if (step_key)
        free(step_key);
    return (ret);
}

static int handle_json_hosts(char *raw_json, ask_demeter_args_t *ask_demeter_conf, linked_list_t **list)
{
    json_object *parsed_json = NULL, *hits = NULL,
    *hits_array = NULL, *array_hit = NULL;
    parsed_hostname_json_t *parsed_json_struct = NULL;
    char *output_str = NULL;
    int ret = 0;

    if (!(parsed_json = json_tokener_parse(raw_json)))
        return (1);
    if (!(hits = json_object_object_get(parsed_json, "hits")))
        return (freeturn_json_object(parsed_json, 1, NULL));
    if (!(hits_array = json_object_object_get(hits, "hits")))
        return (freeturn_json_object(parsed_json, 1, NULL));
    for (int i = 0; (array_hit = json_object_array_get_idx(hits_array, i)) && !ret; i++) {
        (*list) = add_to_list((*list), init_parsed_hostname_json());
        parsed_json_struct = (parsed_hostname_json_t *)(*list)->data;
        switch(parse_json_str(array_hit, ask_demeter_conf, &output_str)) {
            case 0:
                break;
            case 1:
                fprintf(stderr, "Error while parsing json.\n");
                ret = 1;
            default:
                ret = 1;
        }
        if (output_str){
            if (parse_json_host(output_str, ask_demeter_conf, parsed_json_struct))
               ret = 1;
            free(output_str);
        }
    }
    return (freeturn_json_object(parsed_json, ret, NULL));
}

void display_json(linked_list_t *list, ask_demeter_args_t *ask_demeter_conf)
{
    parsed_hostname_json_t *parsed_json_struct = NULL;
    linked_list_t *tmp = NULL;

    if (!ask_demeter_conf->node_set) {
        printf ("Cgroup data for each node:\n");
        if (display_cgroup_tab_all_nodes(list, ask_demeter_conf))
            fprintf(stderr, "Error while displaying cgroup data.\n");
        if (!ask_demeter_conf->hide_log_counters) {
            printf ("\nLog counter for each node:\n");
            if (display_log_counter_tab_all_nodes(list))
                fprintf(stderr, "Error while displaying log counter data.\n");
        }
        if (ask_demeter_conf->slurmsys_logs) {
            printf ("\nSlurm logs for each node:\n");
            if (display_slurm_sys_logs_all_nodes(list))
                fprintf(stderr, "Error while displaying slurm logs.\n");
        }
        if (ask_demeter_conf->infiniband_logs) {
            printf ("\nInfiniband logs for each node:\n");
            if (display_ib_logs_all_nodes(list))
                fprintf(stderr, "Error while displaying infiniband logs.\n");
        }
    } else {
        for (tmp = list; tmp; tmp = tmp->next) {
            parsed_json_struct = (parsed_hostname_json_t *)tmp->data;
            if (!parsed_json_struct->hostname)
                continue;
            printf("\nHOST %s:\n", parsed_json_struct->hostname);
            if (display_cgroup_tab(parsed_json_struct->cgroup_data, ask_demeter_conf))
                fprintf(stderr, "Error while displaying cgroup data.\n");
            if (!ask_demeter_conf->hide_log_counters && display_log_counter_tab(parsed_json_struct->log_counter))
                fprintf(stderr, "Error while displaying log counter data.\n");
            if (ask_demeter_conf->slurmsys_logs && display_slurm_sys_logs(parsed_json_struct))
                fprintf(stderr, "Error while displaying slurm sys logs.\n");
        }
    }
}  

void free_parsed_hostname_json_list(linked_list_t *list)
{
    parsed_hostname_json_t *parsed_json_struct = NULL;
    linked_list_t *tmp = NULL, *old = NULL;

    for (tmp = list; tmp; tmp = tmp->next) {
        if (old)
            free(old);
        parsed_json_struct = (parsed_hostname_json_t *)tmp->data;
        free_parsed_hostname_json(parsed_json_struct);
        old = tmp;
    }
    if (old)
        free(old);
}

int handle_json(char *raw_json, ask_demeter_args_t *ask_demeter_conf)
{
    int ret = 0;
    linked_list_t *parsed_json_list = NULL;

    switch(handle_json_hosts(raw_json, ask_demeter_conf, &parsed_json_list)) {
        case 0:
            break;
        case 1:
            fprintf(stderr, "Error while parsing json.\n");
            return (1);
        default:
            return (1);
    }
    display_json(parsed_json_list, ask_demeter_conf);
    free_parsed_hostname_json_list(parsed_json_list);
    return (ret);
}