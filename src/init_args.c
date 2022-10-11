// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such init, much arg!
//___________________________________________________________________________________________________________________________________________


#include <stdlib.h>
#include "ask_demeter.h"

ask_demeter_args_t *init_args(void)
{
    ask_demeter_args_t *args = malloc(sizeof(ask_demeter_args_t));
    
    if (args == NULL)
        return (NULL);
    args->job_id = -1;
    args->task_id = -1;
    args->hostname = NULL;
    args->format = NULL;
    return (args);
}