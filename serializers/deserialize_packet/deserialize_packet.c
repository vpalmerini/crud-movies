#include "../packet.h"

#include "../deserialize_int/deserialize_int.h"
#include "../deserialize_char/deserialize_char.h"

unsigned char *deserialize_packet(unsigned char *buffer, packet *packet, int field_size, int packet_size)
{
    buffer = deserialize_int(buffer, &packet->op);
    buffer = deserialize_int(buffer, &packet->movie_id);
    buffer = deserialize_char(buffer, packet->movie_title, field_size);
    buffer = deserialize_char(buffer, packet->movie_genre, field_size);
    buffer = deserialize_char(buffer, packet->movie_sinopsis, field_size);
    buffer = deserialize_char(buffer, packet->rooms, field_size);

    return buffer + (packet_size - (8 + 4 * field_size));
}