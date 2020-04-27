#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../packet.h"
#include "../response.h"

void retrieve_movie(char *file_path, packet *packet, int packet_size, response *response, int response_size)
{
    int id = packet->movie_id;

    FILE *fptr;
    if ((fptr = fopen(file_path, "rb+")) == NULL)
    {
        printf("%s\n", strerror(errno));
        exit(1);
    }

    size_t nread;
    long int currPos;
    while ((nread = fread(packet, packet_size, 1, fptr)) > 0)
    {
        if (id == packet->movie_id && packet->deleted == 0)
        {
            response->n_movies = 1;
            response->packets[0] = *packet;
        }
    }

    return;
}