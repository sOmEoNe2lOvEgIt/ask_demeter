// ATOS PROJECT, 2022
// ASK DEMETER
// File description:
// Wow, such main, much code, very program!
//___________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include <json-c/json.h>


int main (int ac, char **av)
{
    if (ac != 2) {
        printf("Missing json file.");
        return (1);
    }
    
    json_object *jobj = json_object_from_file(av[1]);

    json_object_object_foreach(jobj, key, val) {
        printf("%s: %s", key, json_object_get_string(val));
    }
    return (0);
}
