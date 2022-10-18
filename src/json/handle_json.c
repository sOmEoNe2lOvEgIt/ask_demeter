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

static int handle_json_host(char *raw_json, ask_demeter_args_t *ask_demeter_conf)
{
    json_object *parsed_json = NULL, *hits = NULL,
    *hits_array = NULL, *array_hit = NULL;
    char *output_str = NULL;
    int ret = 0;

    if ((parsed_json = json_tokener_parse(raw_json)) == NULL)
        return (1);
    if ((hits = json_object_object_get(parsed_json, "hits")) == NULL)
        return (freeturn_json_object(parsed_json, 1, NULL));
    if ((hits_array = json_object_object_get(hits, "hits")) == NULL)
        return (freeturn_json_object(parsed_json, 1, NULL));
    for (int i = 0; (array_hit = json_object_array_get_idx(hits_array, i)) != NULL && !ret; i++) {
        switch(parse_json(array_hit, ask_demeter_conf, &output_str)) {
            case 0:
                break;
            case 1:
                fprintf(stderr, "Error while parsing json.\n");
                ret = 1;
            default:
                ret = 1;
        }
        if (output_str){
            if (display_json(output_str, ask_demeter_conf))
               ret = 1;
            free(output_str);
        }
    }
    return (freeturn_json_object(parsed_json, ret, NULL));
}

int handle_json(char *raw_json, ask_demeter_args_t *ask_demeter_conf)
{
    int ret = 0;

    switch(handle_json_host(raw_json, ask_demeter_conf)) {
        case 0:
            break;
        case 1:
            fprintf(stderr, "Error while parsing json.\n");
            return (1);
        default:
            return (1);
    }
    return (ret);
}