#ifndef SERIALIZE_RESPONSE_H
#define SERIALIZE_RESPONSE_H

#include "../response.h"

unsigned char *serialize_response(unsigned char *buffer, response *response, int packet_size, int field_size);

#endif