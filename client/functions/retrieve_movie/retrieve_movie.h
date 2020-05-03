#ifndef RETRIEVE_MOVIE_H
#define RETRIEVE_MOVIE_H

#include "../../../serializers/packet.h"

void retrieve_movie(FILE *fp, packet *packet, int field_size);

#endif