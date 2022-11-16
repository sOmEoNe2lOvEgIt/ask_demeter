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
    int ret = 0, get_arg_ret = 0;

    if (!(args = init_args()) ||
    !(conf = read_conf()) ||
    (get_arg_ret = get_arg(ac, av, args)) == 84) {
        ret = 84;
    }
    if (get_arg_ret == 1){
        if (args)
            free_args(args);
        if (conf)
            free_conf(conf);
        return (0);
    }
    if (!ret && (data = get_demeter_json(args, conf))) {
        if (handle_json(data, args))
            ret = 84;
        if (data)
            free(data);
    } else
        ret = 84;
    if (args)
        free_args(args);
    if (conf)
        free_conf(conf);
    return (ret);
}