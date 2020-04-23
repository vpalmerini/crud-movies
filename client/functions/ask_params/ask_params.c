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
        printf("Entre com o nome do filme a ser removido\n");
        packet->op = 3;
        break;
    default:
        printf("Operação inválida!\n");
        break;
    }
}