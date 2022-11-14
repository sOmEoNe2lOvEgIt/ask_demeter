// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such json, much innit!
//___________________________________________________________________________________________________________________________________________

#include <stdlib.h>
#include "ask_demeter.h"

parsed_hostname_json_t *init_parsed_hostname_json(void)
{
    parsed_hostname_json_t *parsed_hostname_json = NULL;

    if (!(parsed_hostname_json = malloc(sizeof(parsed_hostname_json_t))))
        return (NULL);
    parsed_hostname_json->hostname = NULL;
    parsed_hostname_json->user_id = 0;
    parsed_hostname_json->cgroup_data = NULL;
    parsed_hostname_json->sys_log_counter = malloc(sizeof(log_counter_t));
    parsed_hostname_json->slurm_log_counter = malloc(sizeof(log_counter_t));
    parsed_hostname_json->slurm_logs = NULL;
    parsed_hostname_json->sys_logs = NULL;
    parsed_hostname_json->ib_logs = NULL;
    parsed_hostname_json->sel_counters = NULL;
    return (parsed_hostname_json);
}

void free_parsed_hostname_json(parsed_hostname_json_t *parsed_hostname_json)
{
    if (!parsed_hostname_json)
        return;
    if (parsed_hostname_json->hostname)
        free(parsed_hostname_json->hostname);
    if (parsed_hostname_json->sys_log_counter)
        free(parsed_hostname_json->sys_log_counter);
    if (parsed_hostname_json->slurm_log_counter)
        free(parsed_hostname_json->slurm_log_counter);
    if (parsed_hostname_json->slurm_logs)
        free(parsed_hostname_json->slurm_logs);
    if (parsed_hostname_json->sys_logs)
        free(parsed_hostname_json->sys_logs);
    if (parsed_hostname_json->ib_logs)
        free(parsed_hostname_json->ib_logs);
    if (parsed_hostname_json->sel_counters)
        free(parsed_hostname_json->sel_counters);
    free_cgroup_list(parsed_hostname_json->cgroup_data);
    free(parsed_hostname_json);
}