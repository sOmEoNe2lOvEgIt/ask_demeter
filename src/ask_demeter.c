// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such main, much code, very program!
//___________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include "demeter.h"
#include "ask_demeter.h"

int main (int ac, char **av)
{
    ask_demeter_args_t *args = NULL;
    demeter_conf_t *conf = NULL;
    char *data = NULL;

    if ((args = init_args()) == NULL ||
    (conf = read_conf()) == NULL ||
    get_arg(ac, av, args))
        return (84);
    if ((data = get_demeter_job(args->job_id, conf)) == NULL)
        return (84);
    else {
        printf("%s\n", data);
        free(data);
    }
    return (0);
}