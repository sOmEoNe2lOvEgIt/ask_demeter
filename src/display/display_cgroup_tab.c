// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such json, much handle!
//___________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include "ask_demeter.h"

int display_cgroup_tab_all_nodes(linked_list_t *host_list, ask_demeter_args_t *ask_demeter_conf)
{
    parsed_hostname_json_t *node = NULL;
    linked_list_t *tmp = NULL, *tmp_cgroup = NULL;
    cgroup_data_t *cgroup_data = NULL;
    int size = 0;

    print_line(109, false);
    printf("│      Hostname     │   Stepid   │  MaxMemUse │  UnderOom  │   OomKill  │ CpusetCpus │ CpusetEffectiveCpus │\n");
    print_line(109, false);
    size = get_list_size(host_list);
    for (int i = 0; i < size; i++)
    {
        if (!(tmp = get_first_host_after_hostname(host_list, node ? node->hostname : "")))
            continue;
        if (!(node = (parsed_hostname_json_t *)tmp->data) || !(tmp_cgroup = node->cgroup_data))
            continue;
        for (;tmp_cgroup && !tmp_cgroup->data && tmp_cgroup->next; tmp_cgroup = tmp_cgroup->next);
        if (!tmp_cgroup->data)
            continue;
        for (;tmp_cgroup && (cgroup_data = (cgroup_data_t *)tmp_cgroup->data); tmp_cgroup = tmp_cgroup->next) {
            if (cgroup_data->step_id == UINT_MAX && ask_demeter_conf->step_id == -1)
                printf("│   %14s  │    BASH    │ %10d │ %10d │ %10d │ %10s │ %19s │\n",
                       node->hostname, cgroup_data->mem_max_usage_bytes, cgroup_data->under_oom, cgroup_data->oom_kill, cgroup_data->cpuset_cpus, cgroup_data->cpuset_effective_cpus);
            else if (!ask_demeter_conf->hide_steps &&
            (ask_demeter_conf->step_id == -1 || cgroup_data->step_id == (unsigned int)ask_demeter_conf->step_id))
                printf("│   %14s  │ %10d │ %10d │ %10d │ %10d │ %10s │ %19s │\n",
                       node->hostname, cgroup_data->step_id, cgroup_data->mem_max_usage_bytes, cgroup_data->under_oom, cgroup_data->oom_kill, cgroup_data->cpuset_cpus, cgroup_data->cpuset_effective_cpus);
        }
    }
    print_line(109, false);
    return (0);
}