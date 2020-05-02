#ifndef RETRIEVE_MOVIE_FROM_DB_H
#define RETRIEVE_MOVIE_FROM_DB_H

#include "../../../serializers/packet.h"
#include "../../../serializers/response.h"

void retrieve_movie(char *file_path, packet *packet, int packet_size, response *response);

#endif