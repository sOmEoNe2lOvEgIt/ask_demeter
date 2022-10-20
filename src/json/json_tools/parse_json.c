// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such json, much parsing!
//___________________________________________________________________________________________________________________________________________

#define _GNU_SOURCE
#include <stdio.h>
#include <json-c/json.h>
#include "ask_demeter.h"

static int freeturn_step_key(int ret, char *step_key)
{
    if (step_key)
        free(step_key);
    return (ret);
}

int parse_json_str(json_object *raw_json, ask_demeter_args_t *ask_demeter_conf, char **output_str)
{
    json_object *source = NULL, *job_data = NULL,
    *cgroup = NULL, *step = NULL;
    char *step_key = NULL;

    if ((source = json_object_object_get(raw_json, "_source")) == NULL)
        return (freeturn_step_key(1, NULL));
    if (ask_demeter_conf->step_id != -1) {
        asprintf(&step_key, "step_%llu", ask_demeter_conf->step_id);
        if (!step_key)
            return (freeturn_step_key(1, NULL));
        if ((job_data = json_object_object_get(source, "job_data")) == NULL)
            return (freeturn_step_key(1, step_key));
        if ((cgroup = json_object_object_get(job_data, "cgroup")) == NULL)
            return (freeturn_step_key(1, step_key));
        if ((step = json_object_object_get(cgroup, step_key)) == NULL) {
            fprintf(stderr, "No step %llu for this job.\n", ask_demeter_conf->step_id);
            return (freeturn_step_key(2, step_key));
        }
        (*output_str) = strdup((char *)json_object_to_json_string(step));
    } else
        (*output_str) = strdup((char *)json_object_to_json_string(source));
    return (freeturn_step_key(0, step_key));
}