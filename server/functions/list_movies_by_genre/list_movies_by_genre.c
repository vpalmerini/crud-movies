#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../../../serializers/packet.h"
#include "../../../serializers/response.h"

void list_movies_by_genre(char *file_path, packet *packet, int packet_size, response *response)
{
    response->n_movies = 0;
    char *genre = (char *)calloc(strlen(packet->movie_genre), sizeof(char));
    strcpy(genre, packet->movie_genre);

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
        if (packet->deleted == 0 && (strncmp(genre, packet->movie_genre, strlen(genre)) == 0))
        {
            response->n_movies += 1;
            response->packets[i] = *packet;

            i += 1;
        }
    }
    printf("Nº Movies: %d\n", response->n_movies);

    return;
}