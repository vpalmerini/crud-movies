#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../packet.h"
#include "../response.h"

void retrieve_movie(char *file_path, packet *packet, int packet_size, response *response)
{
    int id = packet->movie_id;
    response->n_movies = 0;

    FILE *fptr;
    if ((fptr = fopen(file_path, "rb+")) == NULL)
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

    printf("Nº Movies: %d\n", response->n_movies);
    printf("ID: %d\n", response->packets[0].movie_id);
    printf("Title: %s", response->packets[0].movie_title);
    printf("Genre: %s", response->packets[0].movie_genre);
    printf("Sinopsis: %s", response->packets[0].movie_sinopsis);
    printf("Rooms: %s", response->packets[0].rooms);

    return;
}