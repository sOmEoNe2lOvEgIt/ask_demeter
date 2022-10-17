// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such get, much curl!
//___________________________________________________________________________________________________________________________________________

#define _GNU_SOURCE
#include <stdio.h>
#include <curl/curl.h>
#include "demeter.h"
#include "ask_demeter.h"

struct url_data {
    size_t size;
    char* data;
};

static size_t write_data(void *ptr, size_t size, size_t nmemb, struct url_data *data) {
    size_t index = data->size;
    size_t n = (size * nmemb);
    char* tmp;

    data->size += (size * nmemb);
    tmp = realloc(data->data, data->size + 1);
    if(tmp) {
        data->data = tmp;
    } else {
        if(data->data) {
            free(data->data);
        }
        fprintf(stderr, "Failed to allocate memory.\n");
        return (0);
    }
    memcpy((data->data + index), ptr, n);
    data->data[data->size] = '\0';
    return (size * nmemb);
}

static char *get_search_adress(char *in_adress)
{
    char *change = NULL, *adress = strdup(in_adress);

    if (adress == NULL)
        return (NULL);
    if ((change = strstr(adress, "_doc")) != NULL) {
        adress = realloc(adress, strlen(adress) + 4);
        change = strstr(adress, "_doc");
        strcpy(change, "_search");
    }
    return (adress);
}

static bool get_query(char **query, ask_demeter_args_t *args)
{
    // if (args->step_id != -1) {
    //     asprintf(query, "{ \"_source\":{ \"include\": [\"job_data.cgroup.step_%llu\"]}, \"query\": {\"match\": {\"job_id\": \"%lld\"}}}",
    //     args->step_id, args->job_id);
    // } else {
    //     asprintf(query, "{\"query\": {\"match\": {\"job_id\": \"%lld\"}}}",
    //     args->job_id);
    // }
    asprintf(query, "{\"query\": {\"match\": {\"job_id\": \"%lld\"}}}", args->job_id);
    if (*query == NULL)
        return (false);
    return (true);
}

char *get_demeter_job(ask_demeter_args_t *args, demeter_conf_t *conf)
{
    CURL *curl;
    CURLcode res;
    struct curl_slist *list = NULL;
    char *query = NULL,*adress = NULL;
    struct url_data data = {0, NULL};

    if (!get_query(&query, args) ||
    (data.data = malloc(4096)) == NULL)
        return (NULL);
    data.data[0] = '\0';
    adress = get_search_adress(conf->demeter_comp_loc);
    list = curl_slist_append(list, "Content-Type: application/json");
    if ((curl = curl_easy_init())) {
        curl_easy_setopt(curl, CURLOPT_URL, adress);
        if (conf->demeter_comp_proxy != NULL) {
            curl_easy_setopt(curl, CURLOPT_PROXY, conf->demeter_comp_proxy);
        }
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)(sizeof(char) * strlen(query)));
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        if ((res = curl_easy_perform(curl)) != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed:  %s\n", curl_easy_strerror(res));
    }
    curl_easy_cleanup(curl);
    curl_slist_free_all(list);
    free(query);
    free(adress);
    return (data.data);
}