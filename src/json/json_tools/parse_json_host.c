// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such json, much display, beautyfull ASCII!
//___________________________________________________________________________________________________________________________________________

#define _GNU_SOURCE
#include <stdio.h>
#include <json-c/json.h>
#include "ask_demeter.h"
#ifndef UINT_MAX
#define UINT_MAX 4294967295
#endif

static int freeturn_json_obj(json_object *jobj, int ret)
{
    while (json_object_put(jobj) != 1);
    return (ret);
}

static int freeturn_json_obj_str(json_object *jobj, int ret, char *str)
{
    if (str)
        free(str);
    return (freeturn_json_obj(jobj, ret));
}

static int get_log_counter(char *parsed_json_str, parsed_hostname_json_t *parsed_json, bool is_syslog)
{
    json_object *jobj = NULL, *jobj_element = NULL;
    log_counter_t *log_counter = NULL;


    if (is_syslog)
        log_counter = parsed_json->sys_log_counter;
    else
        log_counter = parsed_json->slurm_log_counter;
    if (!parsed_json_str)
        return (1);
    if (!(jobj = json_tokener_parse(parsed_json_str)))
        return (freeturn_json_obj_str(jobj, 1, parsed_json_str));
    if (!json_object_object_get_ex(jobj, "fatals", &jobj_element))
        return (freeturn_json_obj_str(jobj, 1, parsed_json_str));
    log_counter->fatals = (uint)json_object_get_int64(jobj_element);
    if (!json_object_object_get_ex(jobj, "errors", &jobj_element))
        return (freeturn_json_obj_str(jobj, 1, parsed_json_str));
    log_counter->errors = (uint)json_object_get_int64(jobj_element);
    if (!json_object_object_get_ex(jobj, "warnings", &jobj_element))
        return (freeturn_json_obj_str(jobj, 1, parsed_json_str));
    log_counter->warnings = (uint)json_object_get_int64(jobj_element);
    if (!json_object_object_get_ex(jobj, "infos", &jobj_element))
        return (freeturn_json_obj_str(jobj, 1, parsed_json_str));
    log_counter->infos = (uint)json_object_get_int64(jobj_element);
    if (!json_object_object_get_ex(jobj, "debugs", &jobj_element))
        return (freeturn_json_obj_str(jobj, 1, parsed_json_str));
    log_counter->debugs = (uint)json_object_get_int64(jobj_element);
    return (freeturn_json_obj_str(jobj, 0, parsed_json_str));
}

static int get_cgroup_step_cont(json_object *jobj, parsed_hostname_json_t *parsed_json, uint step_id)
{
    json_object *jobj_element = NULL;
    cgroup_data_t *cgroup_data = NULL;

    cgroup_data = init_cgroup_struct();
    if (!cgroup_data)
        return (1);
    cgroup_data->step_id = step_id;
    if (!json_object_object_get_ex(jobj, "cpuset_cpus", &jobj_element))
        return (1);
    cgroup_data->cpuset_cpus = strdup(json_object_get_string(jobj_element));
    if (!json_object_object_get_ex(jobj, "cpuset_effective_cpus", &jobj_element))
        return (1);
    cgroup_data->cpuset_effective_cpus = strdup(json_object_get_string(jobj_element));
    if (!json_object_object_get_ex(jobj, "mem_max_usage_bytes", &jobj_element))
        return (1);
    cgroup_data->mem_max_usage_bytes = atol(json_object_get_string(jobj_element));
    if (!json_object_object_get_ex(jobj, "under_oom", &jobj_element))
        return (1);
    cgroup_data->under_oom = atol(json_object_get_string(jobj_element));
    if (!json_object_object_get_ex(jobj, "oom_kill", &jobj_element))
        return (1);
    cgroup_data->oom_kill = atol(json_object_get_string(jobj_element));
    parsed_json->cgroup_data = add_to_list(parsed_json->cgroup_data, cgroup_data);
    return (0);
}
static int get_host_cgroup(json_object *jobj, parsed_hostname_json_t *parsed_json)
{
    json_object *jobj_element = NULL;
    char step_str[17] = "step_0";
    uint step_id = 0;

    while (json_object_object_get_ex(jobj, step_str, &jobj_element)) {
        if (get_cgroup_step_cont(jobj_element, parsed_json, step_id))
            return (1);
        step_id++;
        sprintf(step_str, "step_%u", step_id);
    }
    if (!json_object_object_get_ex(jobj, "no_step", &jobj_element))
        return (0);
    if (get_cgroup_step_cont(jobj_element, parsed_json, UINT_MAX))
        return (1);
    return (0);
}

static int get_host_json(json_object *jobj, parsed_hostname_json_t *parsed_json)
{
    json_object *jiobj = NULL;

    if (!json_object_object_get_ex(jobj, "user_id", &jiobj))
        return (freeturn_json_obj(jobj, 1));
    parsed_json->user_id = atol(json_object_get_string(jiobj));
    if (!json_object_object_get_ex(jobj, "hostname", &jiobj))
        return (freeturn_json_obj(jobj, 1));
    parsed_json->hostname = strdup(json_object_get_string(jiobj));
    if (!json_object_object_get_ex(jobj, "job_data", &jiobj))
        return (freeturn_json_obj(jobj, 1));
    if (!json_object_object_get_ex(jiobj, "cgroup", &jiobj))
        return (freeturn_json_obj(jobj, 1));
    if (get_host_cgroup(jiobj, parsed_json))
        return (freeturn_json_obj(jobj, 1));
    if (!json_object_object_get_ex(jobj, "job_data", &jiobj))
        return (freeturn_json_obj(jobj, 1));
    if (!json_object_object_get_ex(jiobj, "slurm_log_counter", &jiobj))
        return (freeturn_json_obj(jobj, 1));
    if (get_log_counter(strdup(json_object_to_json_string(jiobj)), parsed_json, false))
        return (freeturn_json_obj(jobj, 1));
    if (!json_object_object_get_ex(jobj, "job_data", &jiobj))
        return (freeturn_json_obj(jobj, 1));
    if (!json_object_object_get_ex(jiobj, "sys_log_counter", &jiobj))
        return (freeturn_json_obj(jobj, 1));
    if (get_log_counter(strdup(json_object_to_json_string(jiobj)), parsed_json, true))
        return (freeturn_json_obj(jobj, 1));
    if (!json_object_object_get_ex(jobj, "job_data", &jiobj))
        return (freeturn_json_obj(jobj, 1));
    if (!json_object_object_get_ex(jiobj, "slurmlogs", &jiobj))
        return (freeturn_json_obj(jobj, 1));
    parsed_json->slurm_logs = strdup(json_object_get_string(jiobj));
    if (!json_object_object_get_ex(jobj, "job_data", &jiobj))
        return (freeturn_json_obj(jobj, 1));
    if (!json_object_object_get_ex(jiobj, "syslogs", &jiobj))
        return (freeturn_json_obj(jobj, 1));
    parsed_json->sys_logs = strdup(json_object_get_string(jiobj));
    if (!json_object_object_get_ex(jobj, "job_data", &jiobj))
        return (freeturn_json_obj(jobj, 1));
    if (!json_object_object_get_ex(jiobj, "sel_logs", &jiobj))
        return (freeturn_json_obj(jobj, 1));
    parsed_json->ib_logs = strdup(json_object_get_string(jiobj));
    if (!json_object_object_get_ex(jobj, "job_data", &jiobj))
        return (freeturn_json_obj(jobj, 1));
    if (!json_object_object_get_ex(jiobj, "sel_count", &jiobj))
        return (freeturn_json_obj(jobj, 1));
    parsed_json->sel_counters = strdup(json_object_get_string(jiobj));
    return (0);
}

int parse_json_host(char *parsed_json_str, ask_demeter_args_t *ask_demeter_conf,
parsed_hostname_json_t *parsed_json)
{
    json_object *jobj = NULL, *jobj_element = NULL;

    if (!(jobj = json_tokener_parse(parsed_json_str)) ||
    !json_object_object_get_ex(jobj, "hostname", &jobj_element))
        return (1);
    if (ask_demeter_conf->node_set &&
    !is_in_nodeset((char *)json_object_get_string(jobj_element), ask_demeter_conf->node_set))
        return (freeturn_json_obj(jobj, 0));
    if (get_host_json(jobj, parsed_json))
        return (freeturn_json_obj(jobj, 1));
    return (freeturn_json_obj(jobj, 0));
}
