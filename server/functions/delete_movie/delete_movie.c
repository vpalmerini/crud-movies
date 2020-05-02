#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../../../serializers/packet.h"

void delete_movie(char *file_path, packet *packet, int packet_size)
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
        if (id == packet->movie_id)
        {
            packet->deleted = 1;
            currPos = ftell(fptr);
            fseek(fptr, (currPos - packet_size), SEEK_SET);
            fwrite(packet, packet_size, 1, fptr);
            fflush(fptr);
        }
    }
}