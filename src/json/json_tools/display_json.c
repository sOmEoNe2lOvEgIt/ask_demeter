// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such json, much display, beautyfull ASCII!
//___________________________________________________________________________________________________________________________________________

#define _GNU_SOURCE
#include <stdio.h>
#include <json-c/json.h>
#include "ask_demeter.h"

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

int display_json_cgroup(char *parsed_json)
{
    json_object *jobj = NULL, *jobj_element = NULL;

    if (!parsed_json)
        return (1);
    if (!(jobj = json_tokener_parse(parsed_json))) {
        free (parsed_json);
        return (1);
    }
    if (!(jobj_element = json_object_object_get(jobj, "cpuset_cpus")))
        return (freeturn_json_obj_str(jobj, 1, parsed_json));
    printf("\tCpuset cpus: %s\n", json_object_get_string(jobj_element));
    if (!(jobj_element = json_object_object_get(jobj, "cpuset_effective_cpus")))
        return (freeturn_json_obj_str(jobj, 1, parsed_json));
    printf("\tCpuset effective cpus: %s\n", json_object_get_string(jobj_element));
    if (!(jobj_element = json_object_object_get(jobj, "mem_max_usage_bytes")))
        return (freeturn_json_obj_str(jobj, 1, parsed_json));
    printf("\tMax memory usage in bytes: %s\n", json_object_get_string(jobj_element));
    if (!(jobj_element = json_object_object_get(jobj, "under_oom")))
        return (freeturn_json_obj_str(jobj, 1, parsed_json));
    printf("\tUnder oom: %s\n", json_object_get_string(jobj_element));
    printf("\t/!\\ This data may be inacurate due to the cgroup data not being there at job's epilog. /!\\\n");
    return (freeturn_json_obj_str(jobj, 0, parsed_json));
}

static int disp_log_counter(char *parsed_json)
{
    json_object *jobj = NULL, *jobj_element = NULL;

    if (!parsed_json)
        return (1);
    if (!(jobj = json_tokener_parse(parsed_json)))
        return (freeturn_json_obj_str(jobj, 1, parsed_json));
    printf("\nLog counter:\n");
    if (!(jobj_element = json_object_object_get(jobj, "fatals")))
        return (freeturn_json_obj_str(jobj, 1, parsed_json));
    printf("\tFatals: %lu\n", json_object_get_uint64(jobj_element));
    if (!(jobj_element = json_object_object_get(jobj, "errors")))
        return (freeturn_json_obj_str(jobj, 1, parsed_json));
    printf("\tErrors: %lu\n", json_object_get_uint64(jobj_element));
    if (!(jobj_element = json_object_object_get(jobj, "warnings")))
        return (freeturn_json_obj_str(jobj, 1, parsed_json));
    printf("\tWarnings: %lu\n", json_object_get_uint64(jobj_element));
    if (!(jobj_element = json_object_object_get(jobj, "infos")))
        return (freeturn_json_obj_str(jobj, 1, parsed_json));
    printf("\tInfos: %lu\n", json_object_get_uint64(jobj_element));
    if (!(jobj_element = json_object_object_get(jobj, "debugs")))
        return (freeturn_json_obj_str(jobj, 1, parsed_json));
    printf("\tDebugs: %lu\n", json_object_get_uint64(jobj_element));
    return (freeturn_json_obj_str(jobj, 0, parsed_json));
}

static int disp_job_json(json_object *jobj)
{
    json_object *jiobj = NULL;

    if (!(jiobj = json_object_object_get(jobj, "user_id")))
        return (freeturn_json_obj(jobj, 1));
    printf("User id: %s\n", json_object_get_string(jiobj));
    if (!(jiobj = json_object_object_get(jobj, "hostname")))
        return (freeturn_json_obj(jobj, 1));
    printf("Hostname: %s\n", json_object_get_string(jiobj));
    if (!(jiobj = json_object_object_get(jobj, "job_data")))
        return (freeturn_json_obj(jobj, 1));
    if (!(jiobj = json_object_object_get(jiobj, "cgroup")))
        return (freeturn_json_obj(jobj, 1));
    if (!(jiobj = json_object_object_get(jiobj, "no_step")))
        return (freeturn_json_obj(jobj, 1));
    printf("\nCgroup data for the whole job:\n");
    if (display_json_cgroup(strdup(json_object_to_json_string(jiobj))))
        return (freeturn_json_obj(jobj, 1));
    if (!(jiobj = json_object_object_get(jobj, "job_data")))
        return (freeturn_json_obj(jobj, 1));
    if (!(jiobj = json_object_object_get(jiobj, "log_counter")))
        return (freeturn_json_obj(jobj, 1));
    if (disp_log_counter(strdup(json_object_to_json_string(jiobj))))
        return (freeturn_json_obj(jobj, 1));
    return (0);
}

int display_json(char *parsed_json, ask_demeter_args_t *ask_demeter_conf)
{
    json_object *jobj = NULL;

    // printf ("JSON string: %s\n\n", parsed_json);
    printf("\nASK_DEMETER GATHERED DATA:\n\n");
    if (!(jobj = json_tokener_parse(parsed_json)))
        return(1);
    
    printf("Job id: %lli\n", ask_demeter_conf->job_id);
    if (ask_demeter_conf->step_id == -1 && disp_job_json(jobj))
        return (1);
    return (freeturn_json_obj(jobj, 0));
}