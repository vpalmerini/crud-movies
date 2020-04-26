#ifndef DELETE_MOVIE_FROM_DB_H
#define DELETE_MOVIE_FROM_DB_H

#include "../packet.h"

void delete_movie(char *file_path, packet *packet, int packet_size);

#endif