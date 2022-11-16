// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such init, much arg!
//___________________________________________________________________________________________________________________________________________


#include <stdlib.h>
#include "ask_demeter.h"

void free_args(ask_demeter_args_t *args)
{
    if (args->format)
        free(args->format);
    free(args);
}

ask_demeter_args_t *init_args(void)
{
    ask_demeter_args_t *args = malloc(sizeof(ask_demeter_args_t));
    
    if (!args)
        return (NULL);
    args->job_id = -1;
    args->step_id = -1;
    args->format = NULL;
    args->node_set = NULL;
    args->logs = false;
    args->slurm_logs = false;
    args->sys_logs = false;
    args->infiniband_logs = false;
    args->infiniband_counters = false;
    args->infiniband_extended = false;
    args->hide_steps = false;
    return (args);
}