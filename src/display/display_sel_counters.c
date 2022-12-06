// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such json, much handle!
//___________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include "gather_ib.h"
#include "ask_demeter.h"

static perf_data_t *freeturn_json_object(struct json_object *obj, perf_data_t *ret, perf_data_t *to_free)
{
    while (json_object_put(obj) != 1);
    if (to_free)
        free(to_free);
    return (ret);
}

static perf_data_t *get_sel_from_json(char *json)
{
    perf_data_t *perf_data = NULL;
    json_object *parsed_json = NULL, *hits = json_object_new_null();

    if (!(parsed_json = json_tokener_parse(json)))
        return(NULL);
    if (!(perf_data = malloc(sizeof(perf_data_t))))
        return(freeturn_json_object(parsed_json, NULL, NULL));
    if (!json_object_object_get_ex(parsed_json, "counterselect", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->counterselect = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "linkdowned", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->linkdowned = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "portselect", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->portselect = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "qp1dropped", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->qp1dropped = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "rcvdata", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->rcvdata = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "rcvpkts", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->rcvpkts = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "vl15dropped", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->vl15dropped = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "xmitdata", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->xmtdata = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "xmitpkts", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->xmtpkts = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "xmitwait", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->xmtwait = atoll(json_object_to_json_string(hits));
    return (freeturn_json_object(parsed_json, perf_data, NULL));
}

static perf_data_t *get_sel_err_from_json(char *json)
{
    perf_data_t *perf_data = NULL;
    json_object *parsed_json = NULL, *hits = json_object_new_null();

    if (!(parsed_json = json_tokener_parse(json)))
        return(NULL);
    if (!(perf_data = malloc(sizeof(perf_data_t))))
        return(freeturn_json_object(parsed_json, NULL, NULL));
    if (!json_object_object_get_ex(parsed_json, "excbufoverrunerrors", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->excbufoverrunerrors = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "linkintegrityerrors", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->linkintegrityerrors = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "portbufferoverrunerrors", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->portbufferoverrunerrors = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "portdlidmappingerrors", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->portdlidmappingerrors = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "portlocalphysicalerrors", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->portlocalphysicalerrors = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "portloopingerrors", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->portloopingerrors = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "portmalformedpkterrors", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->portmalformedpkterrors = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "portvlmappingerrors", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->portvlmappingerrors = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "rcvconstrainterrors", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->rcvconstrainterrors = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "rcverrors", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->rcverrors = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "rcvremotephyerrors", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->rcvremotephyerrors = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "rcvswrelayerrors", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->rcvswrelayerrors = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "symbolerrors", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->symbolerrors = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "xmitconstrainterrors", &hits))
        return(freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->xmtconstrainterrors = atoll(json_object_to_json_string(hits));
    if (!json_object_object_get_ex(parsed_json, "xmitdiscards", &hits))
        return (freeturn_json_object(parsed_json, NULL, perf_data));
    perf_data->xmtdiscards = atoll(json_object_to_json_string(hits));
    return (freeturn_json_object(parsed_json, perf_data, NULL));
}

int display_sel_counters_tab_all_nodes(linked_list_t *host_list, ask_demeter_args_t *demeter_args)
{
    parsed_hostname_json_t *node = NULL;
    linked_list_t *tmp = NULL;
    perf_data_t *perf_data = NULL;
    char *perf_data_str = NULL;

    int size = 0;

    print_line(133, false);
    printf("│      Hostname      │countersel│linkdowned│portselect│qp1dropped│  rcvdata │  rcvpkts │ vl15drop |  xmtdata │  xmtpkts │  xmtwait │\n");
    print_line(133, false);
    size = get_list_size(host_list);
    for (int i = 0; i < size; i++)
    {
        if (!(tmp = get_first_host_after_hostname(host_list, node ? node->hostname : "")))
            continue;
        if (!(node = (parsed_hostname_json_t *)tmp->data))
            continue;
        if (!(perf_data_str = node->sel_counters))
            continue;
        else {
            if ((perf_data = get_sel_from_json(perf_data_str))) {
            printf("│%20s│%10u│%10u│%10u│%10u│%10u│%10u│%10u│%10u│%10u│%10u│\n",
            node->hostname, perf_data->counterselect, perf_data->linkdowned, perf_data->portselect, perf_data->qp1dropped, perf_data->rcvdata, perf_data->rcvpkts, perf_data->vl15dropped, perf_data->xmtdata, perf_data->xmtpkts, perf_data->xmtwait);
            free(perf_data);
            }
        }
    }
    print_line(133, false);
    return (0);
}

int display_sel_counters_err_all_nodes(linked_list_t *host_list, ask_demeter_args_t *demeter_args)
{
    parsed_hostname_json_t *node = NULL;
    linked_list_t *tmp = NULL;
    perf_data_t *perf_data = NULL;
    char *perf_data_str = NULL;

    int size = 0;

    if (demeter_args->infiniband_extended) {
        print_line(383, false);
        printf("│      Hostname      │  excbufoverrunerrors  │  linkintegrityerrors  │portbufferoverrunerrors│ portdlidmappingerrors │portlocalphysicalerrors│   portloopingerrors   │ portmalformedpkterrors│  portvlmappingerrors  │  rcvconstrainterrors  │       rcverrors       │   rcvremotephyerrors  │    rcvswrelayerrors   │      symbolerrors     │  xmitconstrainterrors │      xmitdiscards     │\n");
        print_line(383, false);
    }
    else {
        print_line(239, false);
        printf("│      Hostname      │  excbufoverrunerrors  │  linkintegrityerrors  │  rcvconstrainterrors  │       rcverrors       │   rcvremotephyerrors  │    rcvswrelayerrors   │      symbolerrors     │  xmitconstrainterrors │      xmitdiscards     │\n");
        print_line(239, false);
    }
    size = get_list_size(host_list);
    for (int i = 0; i < size; i++)
    {
        if (!(tmp = get_first_host_after_hostname(host_list, node ? node->hostname : "")))
            continue;
        if (!(node = (parsed_hostname_json_t *)tmp->data))
            continue;
        if (!(perf_data_str = node->sel_counters))
            continue;
        else {
            if ((perf_data = get_sel_err_from_json(perf_data_str))) {
            if (demeter_args->infiniband_extended)
                printf("│%20s│%23u│%23u│%23u│%23u│%23u│%23u│%23u│%23u│%23u│%23u│%23u│%23u│%23u│%23u│%23u│\n",
                node->hostname, perf_data->excbufoverrunerrors, perf_data->linkintegrityerrors, perf_data->portbufferoverrunerrors, perf_data->portdlidmappingerrors, perf_data->portlocalphysicalerrors, perf_data->portloopingerrors, perf_data->portmalformedpkterrors, perf_data->portvlmappingerrors, perf_data->rcvconstrainterrors, perf_data->rcverrors, perf_data->rcvremotephyerrors, perf_data->rcvswrelayerrors, perf_data->symbolerrors, perf_data->xmtconstrainterrors, perf_data->xmtdiscards);
            else
                printf("│%20s│%23u│%23u│%23u│%23u│%23u│%23u│%23u│%23u│%23u│\n",
                node->hostname, perf_data->excbufoverrunerrors, perf_data->linkintegrityerrors, perf_data->rcvconstrainterrors, perf_data->rcverrors, perf_data->rcvremotephyerrors, perf_data->rcvswrelayerrors, perf_data->symbolerrors, perf_data->xmtconstrainterrors, perf_data->xmtdiscards);
            free(perf_data);
            }
        }
    }
    if (demeter_args->infiniband_extended)
        print_line(383, false);
    else
        print_line(239, false);
    return (0);
}
