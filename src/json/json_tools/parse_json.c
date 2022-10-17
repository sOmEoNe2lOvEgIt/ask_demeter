// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such json, much parsing!
//___________________________________________________________________________________________________________________________________________

#define _GNU_SOURCE
#include <stdio.h>
#include <json-c/json.h>
#include "ask_demeter.h"

int freeturn_json_object(struct json_object *obj, int ret, char *step_key)
{
    while (json_object_put(obj) != 1);
    if (step_key)
        free(step_key);
    return (ret);
}

int parse_json(char *raw_json, ask_demeter_args_t *ask_demeter_conf, char **output_str)
{
    json_object *parsed_json = NULL, *hits = NULL,
    *hits_array = NULL, *array_hit = NULL, *source = NULL,
    *job_data = NULL, *cgroup = NULL, *step = NULL;
    char *step_key = NULL;

    if ((parsed_json = json_tokener_parse(raw_json)) == NULL)
        return (1);
    if (ask_demeter_conf->step_id != -1) {
        asprintf(&step_key, "step_%llu", ask_demeter_conf->step_id);
        if (!step_key)
            return (freeturn_json_object(parsed_json, 1, NULL));
        if ((hits = json_object_object_get(parsed_json, "hits")) == NULL)
            return (freeturn_json_object(parsed_json, 1, step_key));
        if ((hits_array = json_object_object_get(hits, "hits")) == NULL)
            return (freeturn_json_object(parsed_json, 1, step_key));
        if ((array_hit = json_object_array_get_idx(hits_array, 0)) == NULL)
            return (freeturn_json_object(parsed_json, 1, step_key));
        if ((source = json_object_object_get(array_hit, "_source")) == NULL)
            return (freeturn_json_object(parsed_json, 1, step_key));
        if ((job_data = json_object_object_get(source, "job_data")) == NULL)
            return (freeturn_json_object(parsed_json, 1, step_key));
        if ((cgroup = json_object_object_get(job_data, "cgroup")) == NULL)
            return (freeturn_json_object(parsed_json, 1, step_key));
        if ((step = json_object_object_get(cgroup, step_key)) == NULL) {
            fprintf(stderr, "No step %llu for this job.\n", ask_demeter_conf->step_id);
            return (freeturn_json_object(parsed_json, 2, step_key));
        }
        (*output_str) = strdup((char *)json_object_to_json_string(step));
    } else
        (*output_str) = strdup((char *)json_object_to_json_string(parsed_json));
    return (freeturn_json_object(parsed_json, 0, step_key));
}