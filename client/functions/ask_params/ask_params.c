#include <stdio.h>
#include <stdlib.h>

#include "../packet.h"

void ask_params(FILE *fp, int op, packet *packet, int field_size)
{
    switch (op)
    {
    case 1:
        printf("Listagem de filmes\n");
        packet->op = 1;
        break;
    case 2:
        packet->op = 2;
        add_movie(fp, packet, field_size);
        break;
    case 3:
        packet->op = 3;
        delete_movie(fp, packet, field_size);
        break;
    case 4:
        packet->op = 4;
        retrieve_movie(fp, packet, field_size);
        break;
    case 5:
        packet->op = 5;
        retrieve_title(fp, packet, field_size);
        break;
    case 6:
        packet->op = 6;
        list_by_genre(fp, packet, field_size);
        break;
    case 7:
        printf("Listagem de filmes (apenas Título e Salas)\n");
        packet->op = 7;
        break;
    default:
        printf("Operação inválida!\n");
        break;
    }
}