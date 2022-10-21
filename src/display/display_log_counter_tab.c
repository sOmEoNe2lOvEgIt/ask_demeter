// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such json, much handle!
//___________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include "ask_demeter.h"

int display_log_counter_tab(log_counter_t *log_counter)
{  
    printf("  SYSTEM/SLURM LOG COUNTERS:\n");
    print_line(67, true);
    printf("\t│   Errors   │  Warnings  │    Infos   │   Debugs   │   Fatals   │\n");
    print_line(67, true);
    printf("\t│ %10d │ %10d │ %10d │ %10d │ %10d │\n", log_counter->errors, log_counter->warnings, log_counter->infos, log_counter->debugs, log_counter->fatals);
    print_line(67, true);
    return (0);
}