#ifndef PACKET_H
#define PACKET_H

typedef struct packet
{
    int op;
    int movie_id;
    char *movie_title;
    char *movie_sinopsis;
    char *movie_genre;
    char *rooms;
} packet;

#endif