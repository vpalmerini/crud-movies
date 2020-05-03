#include <stdio.h>

#include "../packet.h"
#include "../response.h"

#include "../deserialize_int/deserialize_int.h"
#include "../deserialize_packet/deserialize_packet.h"

unsigned char *deserialize_response(unsigned char *buffer, response *response, int packet_size, int field_size)
{
    buffer = deserialize_int(buffer, &response->n_movies);

    if (response->n_movies == 0)
    {
        printf("Nenhum filme encontrado\n");
        return buffer;
    }

    int i;
    for (i = 0; i < response->n_movies; i++)
    {
        buffer = deserialize_packet(buffer, &response->packets[i], field_size, packet_size);
    }

    return buffer;
}