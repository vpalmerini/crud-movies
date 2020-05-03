#include <stdio.h>

#include "../../../serializers/response.h"
#include "../print_packet/print_packet.h"

void Print_response(response *response)
{

    int i;
    for (i = 0; i < response->n_movies; i++)
    {
        Print_packet(&(response->packets[i]));
    }

    return;
}