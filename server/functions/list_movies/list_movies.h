#ifndef LIST_MOVIES_FROM_DB_H
#define LIST_MOVIES_FROM_DB_H

#include "../../../serializers/packet.h"
#include "../../../serializers/response.h"

void list_movies(char *file_path, packet *packet, int packet_size, response *response);

#endif