// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such get, much curl!
//___________________________________________________________________________________________________________________________________________

#define _GNU_SOURCE
#include <stdio.h>
#include <curl/curl.h>
#include "demeter.h"

struct url_data {
    size_t size;
    char* data;
};

size_t write_data(void *ptr, size_t size, size_t nmemb, struct url_data *data) {
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

static char *get_search_adress(char *adress)
{
    char *change = NULL;

    if (adress == NULL)
        return (NULL);
    if ((change = strstr(adress, "_doc")) != NULL) {
        adress = realloc(adress, strlen(adress) + 4);
        change = strstr(adress, "_doc");
        strcpy(change, "_search");
    }
    return (adress);
}

char *get_demeter_job(uint job_id, demeter_conf_t *conf)
{
    CURL *curl;
    CURLcode res;
    struct curl_slist *list = NULL;
    char *query = NULL,*adress = NULL;
    struct url_data data;

    asprintf(&query, "{\"query\" : {\"match\" : {\"job_id\" : \"%u\"}}}", job_id);
    if (query == NULL)
        return (NULL);
    adress = strdup(conf->demeter_comp_loc);
    adress = get_search_adress(adress);
    data.size = 0;
    data.data = malloc(4096);
    if(data.data == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return NULL;
    }
    data.data[0] = '\0';
    list = curl_slist_append(list, "Content-Type: application/json");
    curl = curl_easy_init();
    if (curl) {
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
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed:  %s\n", curl_easy_strerror(res));
    }
    curl_easy_cleanup(curl);
    curl_slist_free_all(list);
    free(query);
    return (data.data);
}