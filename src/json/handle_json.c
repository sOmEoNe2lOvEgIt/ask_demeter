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

static void display_logs(linked_list_t *list, ask_demeter_args_t *ask_demeter_conf)
{
    if (ask_demeter_conf->slurm_logs) {
        printf ("\n\nSlurm logs for each node:");
        if (display_slurm_logs_all_nodes(list))
            fprintf(stderr, "Error while displaying slurm logs.\n");
    }if (ask_demeter_conf->sys_logs) {
        printf ("\n\nSys logs for each node:");
        if (display_sys_logs_all_nodes(list))
            fprintf(stderr, "Error while displaying sys logs.\n");
    }
    if (ask_demeter_conf->infiniband_logs) {
        printf ("\nInfiniband logs for each node:\n");
        if (display_ib_logs_all_nodes(list))
            fprintf(stderr, "Error while displaying infiniband logs.\n");
    }
}

static void display_json(linked_list_t *list, ask_demeter_args_t *ask_demeter_conf)
{
    if (ask_demeter_conf->logs) {
        display_logs(list, ask_demeter_conf);
        return;   
    }
    printf ("Cgroup data for each node:\n");
    if (display_cgroup_tab_all_nodes(list, ask_demeter_conf))
        fprintf(stderr, "Error while displaying cgroup data.\n");
    if (!ask_demeter_conf->hide_log_counters && !ask_demeter_conf->logs) {
        printf ("\nSLURM log counter for each node:\n");
        if (display_log_counter_tab_all_nodes(list, ask_demeter_conf, false))
            fprintf(stderr, "Error while displaying log counter data.\n");
        printf ("\nSYSTEM log counter for each node:\n");
        if (display_log_counter_tab_all_nodes(list, ask_demeter_conf, true))
            fprintf(stderr, "Error while displaying log counter data.\n");
    }
    if (ask_demeter_conf->infiniband_counters) {
        printf("\nSEL (infiniband) counters for each node:\n");
        if (display_sel_counters_tab_all_nodes(list, ask_demeter_conf))
            fprintf(stderr, "Error while displaying sel counters data.\n");
        if (display_sel_counters_err_all_nodes(list, ask_demeter_conf))
            fprintf(stderr, "Error while displaying sel counters data.\n");
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

static void print_json_as_csv(char *raw_json)
{
    FILE *tmp_file = NULL;
    char *python_cmd = NULL;
    json_object *parsed_json = NULL, *hits = NULL;

    if (!(tmp_file = fopen("/tmp/demeter_tmp.json", "w")))
        return;
    if (!(parsed_json = json_tokener_parse(raw_json)))
        return;
    if (!(hits = json_object_object_get(parsed_json, "hits")))
        return;
    fprintf(tmp_file, "%s", json_object_to_json_string(hits));
    fclose(tmp_file);
    // if (asprintf(&python_cmd, "python3 %s/src/json_to_csv.py", ASK_DEMETER_PATH) == -1)
    //     return;
    if (asprintf(&python_cmd, "./src/json_to_csv.py /tmp/demeter_tmp.json") == -1)  // TEMPORARY, TO REPLACE WITH THE LINES ABOVE
        return;                                                                     // TEMPORARY, TO REPLACE WITH THE LINES ABOVE
    print_line(130, false);
    system(python_cmd);
    print_line(130, false);
    free(python_cmd);
    remove("/tmp/demeter_tmp.json");
}

static int display_each_format(char *raw_json, ask_demeter_args_t *ask_demeter_conf)
{
    if ((strcmp(ask_demeter_conf->format, "json") == 0)) {
        print_line(130, false);
        printf("%s\n", raw_json);
        print_line(130, false);
        return(0);
    }
    if ((strcmp(ask_demeter_conf->format, "csv") == 0)) {
        print_json_as_csv(raw_json);
        return(0);
    }
    return (1);
}

int handle_json(char *raw_json, ask_demeter_args_t *ask_demeter_conf)
{
    linked_list_t *parsed_json_list = NULL;

    if (ask_demeter_conf->format)
        return (display_each_format(raw_json, ask_demeter_conf));
    switch(handle_json_hosts(raw_json, ask_demeter_conf, &parsed_json_list)) {
        case 0:
            break;
        case 1:
            fprintf(stderr, "Error while parsing json.\n");
            return (1);
        default:
            return (1);
    }
    if (!ask_demeter_conf->format)
        display_json(parsed_json_list, ask_demeter_conf);
    free_parsed_hostname_json_list(parsed_json_list);
    return (0);
}