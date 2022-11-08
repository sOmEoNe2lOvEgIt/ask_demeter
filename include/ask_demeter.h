// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, so many includes, much code, very program!
//___________________________________________________________________________________________________________________________________________

#ifndef ASK_DEMETER_H_
#define ASK_DEMETER_H_

#include <stdbool.h>
#include <json-c/json.h>
#include "demeter.h"

typedef struct ask_demeter_args_s {
    long long signed job_id;
    long long signed step_id;
    char *format;
    char *node_set;
    bool slurmsys_logs;
    bool infiniband_logs;
    bool hide_steps;
    bool hide_log_counters;
} ask_demeter_args_t;

typedef struct parsed_hostname_json_s {
    char *hostname;
    uint user_id;
    linked_list_t *cgroup_data;
    log_counter_t *log_counter;
    char *sys_slurm_logs;
    char *ib_logs;
} parsed_hostname_json_t;

ask_demeter_args_t *init_args(void);

parsed_hostname_json_t *init_parsed_hostname_json(void);

void free_parsed_hostname_json(parsed_hostname_json_t *parsed_hostname_json);

void free_args(ask_demeter_args_t *args);

int get_arg(int ac, char **av, ask_demeter_args_t *args);

char *get_demeter_json(ask_demeter_args_t *args, demeter_conf_t *conf);

uint get_list_size (linked_list_t *list);

linked_list_t *get_first_host_after_hostname(linked_list_t *list, char *best_hostname);

int handle_json(char *raw_json, ask_demeter_args_t *ask_demeter_conf);

int parse_json_str(json_object *raw_json, ask_demeter_args_t *ask_demeter_conf, char **output_str);

int parse_json_host(char *parsed_json_str, ask_demeter_args_t *ask_demeter_conf,
parsed_hostname_json_t *parsed_json);

int display_cgroup_tab(linked_list_t *list, ask_demeter_args_t *ask_demeter_conf);

int display_cgroup_tab_all_nodes(linked_list_t *list, ask_demeter_args_t *ask_demeter_conf);

// int display_log_counter_tab(log_counter_t *log_counter);

int display_log_counter_tab_all_nodes(linked_list_t *host_list, ask_demeter_args_t *demeter_args);

int display_slurm_sys_logs(parsed_hostname_json_t *parsed_json);

int display_slurm_sys_logs_all_nodes(linked_list_t *parsed_json_list);

int display_ib_logs(parsed_hostname_json_t *parsed_json);

int display_ib_logs_all_nodes(linked_list_t *parsed_json_list);

void print_line(int len, bool tab);

#endif /* !ASK_DEMETER_H_ */
