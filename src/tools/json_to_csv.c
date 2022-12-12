// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such main, much code, very program!
//___________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
#include "demeter.h"

void sub_json(json_object *obj, char **csv_names, char **csv_values)
{
    json_object *jname = NULL;

    json_object_object_foreach(obj, key, val) {
        json_object_object_get_ex(obj, key, &jname);
        if (json_object_get_type(jname) == json_type_object) {
            sub_json(jname, csv_names, csv_values);
        } else {
            strcat((*csv_names), key);
            strcat((*csv_names), ",");
            if (strlen(json_object_to_json_string(val))){
                strcat((*csv_values), json_object_to_json_string(val));
                strcat((*csv_values), ",");
            }
        }
    }
}

char *json_to_csv(char *json)
{
    json_object *jobj = json_tokener_parse(json), *jarray = json_object_object_get(jobj, "hits"),
    *jvalue = NULL;
    char *csv_names = malloc(sizeof(char) * strlen(json));
    char *csv_values = malloc(sizeof(char) * strlen(json));
    char *res = NULL;
    int i = 0;

    jarray = json_object_object_get(jarray, "hits");
    if (jarray != NULL) {
        jvalue = json_object_array_get_idx(jarray, i);
        jvalue = json_object_object_get(jvalue, "_source");
        sub_json(jvalue, &csv_names, &csv_values);
    }
    csv_names[strlen(csv_names) - 1] = '\n';
    res = strdup(strcat(csv_names, csv_values));
    res[strlen(res) - 1] = '\0';
    free(csv_names);
    free(csv_values);
    while (!json_object_put(jobj));
    return (res);
}