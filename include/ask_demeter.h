// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, so many includes, much code, very program!
//___________________________________________________________________________________________________________________________________________

#ifndef ASK_DEMETER_H_
#define ASK_DEMETER_H_

#include "demeter.h"

typedef struct ask_demeter_args_s {
    long long signed job_id;
    long long signed task_id;
    char *hostname;
    char *format;
} ask_demeter_args_t;

ask_demeter_args_t *init_args(void);

int get_arg(int ac, char **av, ask_demeter_args_t *args);

char *get_demeter_job(uint job_id, demeter_conf_t *conf);


#endif /* !ASK_DEMETER_H_ */
