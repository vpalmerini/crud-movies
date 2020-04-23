#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../packet.h"

void list_by_genre(FILE *fp, packet *packet, int field_size)
{
    char *input = (char *)calloc(field_size, sizeof(char));

    printf("Entre com o gênero dos filmes a serem listados:\n");
    fgets(input, field_size, fp);
    strcpy(packet->movie_genre, input);

    free(input);

    return;
}