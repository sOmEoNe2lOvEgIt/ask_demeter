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
    int ret = 0;

    if ((args = init_args()) == NULL ||
    (conf = read_conf()) == NULL ||
    get_arg(ac, av, args)) {
        ret = 84;
    }
    if (!ret && (data = get_demeter_json(args, conf)) != NULL) {
        if (handle_json(data, args))
            ret = 84;
        free(data);
    } else
        ret = 84;
    free_args(args);
    free_conf(conf);
    return (ret);
}