// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such main, much code, very program!
//___________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include "ask_demeter.h"

int main (int ac, char **av)
{
    ask_demeter_args_t *args = init_args();

    if (get_arg(ac, av, args) == 84)
        return (84);
    // else
    //     printf("Job id: %lli\nHostname: %s\nTask id: %lli\nFormat: %s\n", args->job_id, args->hostname, args->task_id, args->format);
    return (0);
}