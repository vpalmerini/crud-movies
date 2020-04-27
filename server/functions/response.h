#ifndef RESPONSE_H
#define RESPONSE_H

#define N 10

#include "packet.h"

typedef struct response
{
    int n_movies;
    struct packet packet[N];
} response;

#endif