#ifndef LIST_MOVIES_FROM_DB_H
#define LIST_MOVIES_FROM_DB_H

#include "../packet.h"
#include "../response.h"

void list_movies(char *file_path, packet *packet, int packet_size, response *response);

#endif