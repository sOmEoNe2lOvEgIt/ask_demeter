// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such json, much handle!
//___________________________________________________________________________________________________________________________________________

#define _GNU_SOURCE
#include <stdio.h>
#include <json-c/json.h>
#include "ask_demeter.h"

int handle_json(char *raw_json, ask_demeter_args_t *ask_demeter_conf)
{
    char *output_str = NULL;

    switch(parse_json(raw_json, ask_demeter_conf, &output_str)) {
        case 0:
            printf(output_str);
            break;
        case 1:
            fprintf(stderr, "Error while parsing json.\n");
            return (1);
        default:
            return (1);
    }
    if (output_str)
        free(output_str);
    return (0);
}