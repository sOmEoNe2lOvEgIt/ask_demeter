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

    if ((parsed_json = json_tokener_parse(raw_json)) == NULL)
        return (1);
    if ((hits = json_object_object_get(parsed_json, "hits")) == NULL)
        return (freeturn_json_object(parsed_json, 1, NULL));
    if ((hits_array = json_object_object_get(hits, "hits")) == NULL)
        return (freeturn_json_object(parsed_json, 1, NULL));
    for (int i = 0; (array_hit = json_object_array_get_idx(hits_array, i)) != NULL && !ret; i++) {
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

void display_json(linked_list_t *list)
{
    parsed_hostname_json_t *parsed_json_struct = NULL;
    linked_list_t *cgroup_tmp = NULL;
    cgroup_data_t *cgroup_data_struct = NULL;

    for (linked_list_t *tmp = list; tmp != NULL; tmp = tmp->next) {
        parsed_json_struct = (parsed_hostname_json_t *)tmp->data;
        if (!parsed_json_struct->hostname)
            continue;
        printf("Hostname: %s\n", parsed_json_struct->hostname);
        printf("\tUser id: %d\n", parsed_json_struct->user_id);
        cgroup_tmp = parsed_json_struct->cgroup_data;
        while (cgroup_tmp && cgroup_tmp->data) {
            cgroup_data_struct = (cgroup_data_t *)cgroup_tmp->data;
            if (cgroup_data_struct->step_id != UINT_MAX)
                printf("\tStep id: %u\n", cgroup_data_struct->step_id);
            else
                printf("\tStep id: End step\n");
            printf("\t\tMem max usage: %u\n", cgroup_data_struct->mem_max_usage_bytes);
            cgroup_tmp = cgroup_tmp->next;
        }
    }
}

int handle_json(char *raw_json, ask_demeter_args_t *ask_demeter_conf)
{
    int ret = 0;
    linked_list_t *list = NULL;

    switch(handle_json_hosts(raw_json, ask_demeter_conf, &list)) {
        case 0:
            break;
        case 1:
            fprintf(stderr, "Error while parsing json.\n");
            return (1);
        default:
            return (1);
    }
    display_json(list);
    return (ret);
}