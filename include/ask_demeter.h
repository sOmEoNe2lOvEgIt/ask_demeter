// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, so many includes, much code, very program!
//___________________________________________________________________________________________________________________________________________

#ifndef ASK_DEMETER_H_
#define ASK_DEMETER_H_

#include <stdbool.h>
#include <json-c/json.h>
#include "demeter.h"

typedef struct ask_demeter_args_s {
    long long signed job_id;
    long long signed step_id;
    char *hostname;
    char *format;
    char *node_set;
    bool slurmsys_logs;
    bool infiniband_logs;
} ask_demeter_args_t;

ask_demeter_args_t *init_args(void);

void free_args(ask_demeter_args_t *args);

int get_arg(int ac, char **av, ask_demeter_args_t *args);

char *get_demeter_json(ask_demeter_args_t *args, demeter_conf_t *conf);

int handle_json(char *raw_json, ask_demeter_args_t *ask_demeter_conf);

int parse_json(json_object *raw_json, ask_demeter_args_t *ask_demeter_conf, char **output_str);

int display_json(char *parsed_json, ask_demeter_args_t *ask_demeter_conf);

#endif /* !ASK_DEMETER_H_ */
