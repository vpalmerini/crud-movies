#ifndef RECEIVE_DATA_H
#define RECEIVE_DATA_H

#include "../../../serializers/packet.h"
#include "../../../serializers/response.h"

void receive_data(int sock_fd, int buffer_size, packet *packet, int field_size, char *db_path, response *response, int response_size, int *counter, int packet_size);

#endif