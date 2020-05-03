#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../../../serializers/packet.h"
#include "../../../serializers/response.h"

void retrieve_movie(char *file_path, packet *packet, int packet_size, response *response)
{
    int id = packet->movie_id;
    response->n_movies = 0;

    FILE *fptr;
    if ((fptr = fopen(file_path, "ab+")) == NULL)
    {
        printf("%s\n", strerror(errno));
        exit(1);
    }

    size_t nread;
    while ((nread = fread(packet, packet_size, 1, fptr)) > 0)
    {
        if (id == packet->movie_id && packet->deleted == 0)
        {
            response->n_movies = 1;
            response->packets[0] = *packet;
            break;
        }
    }

    return;
}