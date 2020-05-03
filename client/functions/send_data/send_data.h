#ifndef SEND_DATA_H
#define SEND_DATA_H

#include "../../../serializers/packet.h"
#include "../../../serializers/response.h"

void send_data(int sock_fd, packet *packet, response *response, int buffer_size, int field_size, int op, int packet_size, int response_size);

#endif