#include <stdio.h>

#include "../../../serializers/packet.h"

void print_movie(packet *packet)
{
    printf("ID: %d\n", packet->movie_id);
    printf("Título: %s", packet->movie_title);
    printf("Gênero: %s", packet->movie_genre);
    printf("Sinopse: %s", packet->movie_sinopsis);
    printf("Salas: %s", packet->rooms);
    printf("\n");

    return;
}