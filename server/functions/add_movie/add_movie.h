#ifndef ADD_MOVIE_TO_DB_H
#define ADD_MOVIE_TO_DB_H

#include "../../../serializers/packet.h"

void add_movie(char *db_path, packet *packet, int packet_size, int *counter);

#endif