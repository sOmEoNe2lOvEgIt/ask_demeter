// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such arg, much options, very getting!
//___________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>
#include "ask_demeter.h"

static int help(void)
{
    printf("USAGE:\n\task_demeter [OPTION]...\n");
    printf("\tAsk Demeter for the info of a finished job.\n\n");
    printf("OPTIONS:\n");
    printf("\t-h, --help\t\t\t\tDisplay this help and exits.\n");
    printf("\t-j, --jobId JOBID ∈ [0, max_uint32]\tThe id of the job. /!\\Required.\n");
    printf("\t-s, --stepId STEPID ∈ [-1, max_uint32]\tThe id of the step. Default is -1, returns info only for the step.\n");
    printf("\t-n, --nodeset \"NODESET\"\t\t\tThe nodeset for the job, return infos only from nodes specified.\n");
    printf("\t-i, --infiniband-logs\t\t\tDisplay the infiniband logs.\n");
    printf("\t-l, --slurmsys-logs\t\t\tDisplay the slurm and system logs.  /!\\ TO BE SEPARATED\n");
    printf("\t-X, --hide-steps\t\t\tOnly show info for the \"BASH\" step.\n");
    printf("\t-L, --hide-log-counters\t\t\tHide the log counters.  /!\\ TO BE SEPARATED\n");
    printf("\t-f, --format FORMAT\t\t\tThe format of the output. Valid formats are: json, xml, csv.  /!\\ NOT YET IMPLEMENTED\n\n");
    return (1);
}

static bool check_arg(ask_demeter_args_t *args)
{
    if (args->job_id == -1) {
        fprintf(stderr, "Error: Missing job id.\n");
        return (true);
    }
    if (args->job_id < 0) {
        fprintf(stderr, "Error: Invalid job id.\n");
        return (true);
    }
    if (args->step_id < -1) {
        fprintf(stderr, "Error: Invalid task id.\n");
        return (true);
    }
    if (args->format && (strcmp(args->format, "json") != 0 &&
    strcmp(args->format, "xml") != 0 && strcmp(args->format, "csv") != 0)) {
        fprintf(stderr, "Error: Invalid format.\n");
        return (true);
    }
    return (false);
}

static bool is_positive_int(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return (false);
    }
    return (true);
}

int get_arg(int ac, char **av, ask_demeter_args_t *args)
{
    static struct option long_options[] =
    {{"help", no_argument, 0, 'h'},
    {"jobId", required_argument, 0, 'j'},
    {"stepId",  required_argument, 0, 's'},
    {"nodeset", required_argument, 0, 'n'},
    {"slurmsys-logs", no_argument, 0, 'l'},
    {"infiniband_logs", no_argument, 0, 'i'},
    {"hideSteps", no_argument, 0, 'X'},
    {"hideLogCounters", no_argument, 0, 'L'},
    {0, 0, 0, 0}};
    int option_index = 0;
    int get_opt = 0;

    while ((get_opt = getopt_long(ac, av, "hliXLj:n:s:", long_options, &option_index)) != -1) {
        switch (get_opt) {
            case 'h':
                return (help());
            case 'j':
                if (!is_positive_int(optarg)) {
                    fprintf(stderr, "Error: Invalid job id. Has to be a positive integer.\n");
                    return (84);
                }
                args->job_id = atoi(optarg);
                break;
            case 's':
                if (!is_positive_int(optarg) && strcmp(optarg, "-1") != 0) {
                    fprintf(stderr, "Error: Invalid step id. Has to be an integer over or equal to '-1'\n");
                    return (84);
                }
                args->step_id = atoi(optarg);
                break;
            case 'n':
                args->node_set = optarg;
                break;
            case 'l':
                args->slurmsys_logs = true;
                break;
            case 'i':
                args->infiniband_logs = true;
                break;
            case 'X':
                args->hide_steps = true;
                break;
            case 'L':
                args->hide_log_counters = true;
                break;
            default:
                fprintf(stderr, "Error: Invalid option.\n");
                return (84);
        }
    }
    if (check_arg(args))
        return (84);
    return (0);
}