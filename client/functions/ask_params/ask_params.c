#include <stdio.h>
#include <stdlib.h>

#include "../packet.h"
#include "../response.h"
#include "../add_movie/add_movie.h"
#include "../delete_movie/delete_movie.h"
#include "../retrieve_movie/retrieve_movie.h"
#include "../retrieve_title/retrieve_title.h"
#include "../list_by_genre/list_by_genre.h"

void ask_params(FILE *fp, int op, packet *packet, int field_size)
{
    switch (op)
    {
    case 1:
        printf("Listagem de filmes\n");
        packet->op = 1;
        break;
    case 2:
        printf("Adicionando Filme\n");
        packet->op = 2;
        add_movie(fp, packet, field_size);
        break;
    case 3:
        printf("Removendo Filme\n");
        packet->op = 3;
        delete_movie(fp, packet, field_size);
        break;
    case 4:
        printf("Retornando Filme\n");
        packet->op = 4;
        retrieve_movie(fp, packet, field_size);
        break;
    case 5:
        printf("Retornando Título de Filme\n");
        packet->op = 5;
        retrieve_title(fp, packet, field_size);
        break;
    case 6:
        printf("Listando Filmes de um dado gênero\n");
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