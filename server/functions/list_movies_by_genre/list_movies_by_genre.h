#ifndef LIST_MOVIES_BY_GENRE_FROM_DB_H
#define LIST_MOVIES_BY_GENRE_FROM_DB_H

#include "../packet.h"
#include "../response.h"

void list_movies_by_genre(char *file_path, packet *packet, int packet_size, response *response);

#endif