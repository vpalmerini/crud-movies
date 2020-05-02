#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../../../serializers/packet.h"

void read_movie(FILE *fptr, char *file_path, packet *packet, int packet_size)
{
    if ((fptr = fopen(file_path, "rb")) == NULL)
    {
        printf("%s\n", strerror(errno));
        exit(1);
    }

    size_t nread;
    while ((nread = fread(packet, packet_size, 1, fptr)) > 0)
    {
        printf("Movie ID: %d\n", packet->movie_id);
        printf("Movie Title: %s", packet->movie_title);
    }
    fclose(fptr);

    return;
}