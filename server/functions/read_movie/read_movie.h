#ifndef READ_MOVIE_FROM_DB_H
#define READ_MOVIE_FROM_DB_H

#include "../../../serializers/packet.h"

void read_movie(FILE *fptr, char *file_path, packet *packet, int packet_size);

#endif