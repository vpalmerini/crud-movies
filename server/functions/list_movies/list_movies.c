#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../../../serializers/packet.h"
#include "../../../serializers/response.h"

void list_movies(char *file_path, packet *packet, int packet_size, response *response, int response_size)
{
    response->n_movies = 0;

    FILE *fptr;
    if ((fptr = fopen(file_path, "ab+")) == NULL)
    {
        printf("%s\n", strerror(errno));
        exit(1);
    }

    size_t nread;
    int i = 0;
    while ((nread = fread(packet, packet_size, 1, fptr)) > 0)
    {
        if (packet->deleted == 0)
        {
            response->n_movies += 1;
            response->packets[i] = *packet;

            i += 1;
        }
    }

    return;
}