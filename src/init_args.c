// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such init, much arg!
//___________________________________________________________________________________________________________________________________________


#include <stdlib.h>
#include "ask_demeter.h"

void free_args(ask_demeter_args_t *args)
{
    if (args->hostname != NULL)
        free(args->hostname);
    if (args->format != NULL)
        free(args->format);
    free(args);
}

ask_demeter_args_t *init_args(void)
{
    ask_demeter_args_t *args = malloc(sizeof(ask_demeter_args_t));
    
    if (args == NULL)
        return (NULL);
    args->job_id = -1;
    args->step_id = -1;
    args->hostname = NULL;
    args->format = NULL;
    return (args);
}