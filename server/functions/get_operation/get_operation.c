#include <stdio.h>
#include <stdlib.h>

#include "../packet.h"
#include "../add_movie/add_movie.h"

void get_operation(char *db_path, packet *packet, int packet_size)
{
    switch (packet->op)
    {
    case 1:
        printf("Listagem de filmes\n");
        break;
    case 2:
        printf("Adicionando Filme\n");
        add_movie(db_path, packet, packet_size);
        break;
    case 3:
        printf("Removendo Filme\n");
        break;
    case 4:
        printf("Retornando Filme\n");
        break;
    case 5:
        printf("Retornando Título do Filme\n");
        break;
    case 6:
        printf("Listando Filmes de um Gênero\n");
        break;
    case 7:
        printf("Listagem de filmes (apenas Título e Salas)\n");
        break;
    default:
        printf("Operação inválida!\n");
        break;
    }
}