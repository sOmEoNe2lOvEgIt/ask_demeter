// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such arg, much options, very getting!
//___________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include "ask_demeter.h"

static int help(void)
{
    printf("USAGE:\n\task_demeter [OPTION]...\n");
    printf("\tAsk Demeter for the info of a finished job.\n\n");
    printf("OPTIONS:\n");
    printf("\t-h, --help\t\t\t\tDisplay this help and exit.\n");
    printf("\t-j, --jobId=JOBID ∈ [0, max_uint32]\tThe id of the job. /!\\Required.\n");
    printf("\t-H, --hostname=HOSTNAME\t\t\tThe hostname for the job.\n");
    printf("\t-t, --taskId=TASKID ∈ [-1, max_uint32]\tThe id of the task. Default is -1, returns info for the whole job.\n");
    printf("\t-f, --format=FORMAT\t\t\tThe format of the output. Valid formats are: json, xml, csv.\n");
    return (0);
}

int get_arg(int ac, char **av, ask_demeter_args_t *args)
{
    static struct option long_options[] =
    {{"help", no_argument, 0, 'h'},
    {"jobId", required_argument, 0, 'j'},
    {"hostname", required_argument, 0, 'H'},
    {"taskId",  required_argument, 0, 't'},
    {"format",  required_argument, 0, 'f'},
    {0, 0, 0, 0}};
    int option_index = 0;
    int get_opt = 0;

    while ((get_opt = getopt_long(ac, av, "hj:H:t:f:", long_options, &option_index)) != -1) {
        switch (get_opt) {
            case 'h':
                return (help());
            case 'j':
                args->job_id = atoi(optarg);
                break;
            case 'H':
                args->hostname = optarg;
                break;
            case 't':
                args->task_id = atoi(optarg);
                break;
            case 'f':
                args->format = optarg;
                break;
            default:
                return (84);
        }
    }
    if (args->job_id == -1) {
        fprintf(stderr, "Error: Missing job id.\n");
        return (84);
    }
    if (args->job_id < 0) {
        fprintf(stderr, "Error: Invalid job id.\n");
        return (84);
    }
    if (args->task_id < -1) {
        fprintf(stderr, "Error: Invalid task id.\n");
        return (84);
    }
    return (0);
}