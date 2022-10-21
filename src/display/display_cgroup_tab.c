// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such json, much handle!
//___________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include "ask_demeter.h"

int display_cgroup_tab(linked_list_t *list, ask_demeter_args_t *ask_demeter_conf)
{
    cgroup_data_t *cgroup_data_struct = NULL;

    cgroup_data_struct = (cgroup_data_t *)list->data;
    printf("  CGROUP DATA:\n");
    print_line(89, true);
    printf("\t│   StepId   │  MaxMemUse │  UnderOom  │   OomKill  │ CpusetCpus │ CpusetEffectiveCpus │\n");
    print_line(89, true);
    for (; list != NULL && list->data; list = list->next)
    {
        cgroup_data_struct = (cgroup_data_t *)list->data;
        if (cgroup_data_struct->step_id == UINT_MAX)
            printf("\t│    BASH    │ %10d │ %10d │ %10d │ %10s │ %19s │\n",
                   cgroup_data_struct->mem_max_usage_bytes, cgroup_data_struct->under_oom, cgroup_data_struct->oom_kill, cgroup_data_struct->cpuset_cpus, cgroup_data_struct->cpuset_effective_cpus);
        else if (!ask_demeter_conf->hide_steps)
            printf("\t│ %10d │ %10d │ %10d │ %10d │ %10s │ %19s │\n",
                   cgroup_data_struct->step_id, cgroup_data_struct->mem_max_usage_bytes, cgroup_data_struct->under_oom, cgroup_data_struct->oom_kill, cgroup_data_struct->cpuset_cpus, cgroup_data_struct->cpuset_effective_cpus);
    }
    print_line(89, true);
    return (0);
}

int display_cgroup_tab_all_nodes(linked_list_t *list, ask_demeter_args_t *ask_demeter_conf)
{
    parsed_hostname_json_t *node = NULL;
    linked_list_t *tmp = NULL, *tmp_cgroup = NULL;
    cgroup_data_t *cgroup_data = NULL;

    print_line(109, false);
    printf("│      Hostname     │   Stepid   │  MaxMemUse │  UnderOom  │   OomKill  │ CpusetCpus │ CpusetEffectiveCpus │\n");
    print_line(109, false);
    for (tmp = list; tmp != NULL && tmp->data; tmp = tmp->next)
    {
        node = (parsed_hostname_json_t *)tmp->data;
        if (!(tmp_cgroup = node->cgroup_data))
            continue;
        while (tmp_cgroup->data == NULL && tmp_cgroup->next != NULL)
            tmp_cgroup = tmp_cgroup->next;
        if (tmp_cgroup->data == NULL)
            continue;

        while (tmp_cgroup)
        {
            if (!(cgroup_data = (cgroup_data_t *)tmp_cgroup->data))
                continue;
            if (cgroup_data->step_id == UINT_MAX)
                printf("│   %14s  │    BASH    │ %10d │ %10d │ %10d │ %10s │ %19s │\n",
                       node->hostname, cgroup_data->mem_max_usage_bytes, cgroup_data->under_oom, cgroup_data->oom_kill, cgroup_data->cpuset_cpus, cgroup_data->cpuset_effective_cpus);
            else if (!ask_demeter_conf->hide_steps)
                printf("│   %14s  │ %10d │ %10d │ %10d │ %10d │ %10s │ %19s │\n",
                       node->hostname, cgroup_data->step_id, cgroup_data->mem_max_usage_bytes, cgroup_data->under_oom, cgroup_data->oom_kill, cgroup_data->cpuset_cpus, cgroup_data->cpuset_effective_cpus);
            tmp_cgroup = tmp_cgroup->next;
        }
    }
    print_line(109, false);
    return (0);
}