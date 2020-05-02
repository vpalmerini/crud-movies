#ifndef DESERIALIZE_PACKET_H
#define DESERIALIZE_PACKET_H

#include "../packet.h"

unsigned char *deserialize_packet(unsigned char *buffer, packet *packet, int field_size, int packet_size);

#endif