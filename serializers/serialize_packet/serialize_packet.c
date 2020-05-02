#include "../packet.h"

#include "../serialize_int/serialize_int.h"
#include "../serialize_char/serialize_char.h"

unsigned char *serialize_packet(unsigned char *buffer, packet *packet, int field_size, int packet_size)
{
    buffer = serialize_int(buffer, packet->op);
    buffer = serialize_int(buffer, packet->movie_id);
    buffer = serialize_char(buffer, packet->movie_title, field_size);
    buffer = serialize_char(buffer, packet->movie_genre, field_size);
    buffer = serialize_char(buffer, packet->movie_sinopsis, field_size);
    buffer = serialize_char(buffer, packet->rooms, field_size);

    return buffer + (packet_size - (8 + (4 * field_size)));
}