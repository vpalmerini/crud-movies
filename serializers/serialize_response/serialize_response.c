#include "../response.h"
#include "../serialize_int/serialize_int.h"
#include "../serialize_packet/serialize_packet.h"

unsigned char *serialize_response(unsigned char *buffer, response *response, int packet_size, int field_size)
{
    buffer = serialize_int(buffer, response->n_movies);

    int i;
    for (i = 0; i < response->n_movies; i++)
    {
        buffer = serialize_packet(buffer, &(response->packets[i]), field_size, packet_size);
    }

    return buffer;
}