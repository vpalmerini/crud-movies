#ifndef PACKET_H
#define PACKET_H

#define FIELD 256

typedef struct packet
{
    int op;
    int movie_id;
    char movie_title[FIELD];
    char movie_sinopsis[FIELD];
    char movie_genre[FIELD];
    char rooms[FIELD];
} packet;

#endif