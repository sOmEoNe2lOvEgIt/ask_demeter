// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such logs, much display!
//___________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include "ask_demeter.h"

int display_slurm_sys_logs(parsed_hostname_json_t *parsed_json)
{
    if (!parsed_json)
        return (1);
    printf ("\nLOGS:\n%s\n", parsed_json->sys_slurm_logs);
    return (0);
}