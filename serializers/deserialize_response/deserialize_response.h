#ifndef DESERIALIZE_RESPONSE_H
#define DESERIALIZE_RESPONSE_H

#include "../packet.h"
#include "../response.h"

unsigned char *deserialize_response(unsigned char *buffer, response *response, int packet_size, int field_size);

#endif