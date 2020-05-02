#ifndef SERIALIZE_PACKET_H
#define SERIALIZE_PACKET_H

#include "../packet.h"

unsigned char *serialize_packet(unsigned char *buffer, packet *packet, int field_size, int packet_size);

#endif