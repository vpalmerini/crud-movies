#include <stdio.h>

#include "../packet.h"

void Print_packet(packet *packet)
{
    printf("Movie ID: %d\n", packet->movie_id);
    printf("Movie Title: %s", packet->movie_title);
    printf("Movie Genre: %s", packet->movie_genre);
    printf("Movie Sinopsis: %s", packet->movie_sinopsis);
    printf("Movie Rooms: %s", packet->rooms);
    printf("Deleted: %d\n", packet->deleted);
}