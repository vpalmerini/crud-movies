#include <stdio.h>
#include <stdlib.h>

#include "../packet.h"
#include "../response.h"
#include "../add_movie/add_movie.h"
#include "../read_movie/read_movie.h"
#include "../delete_movie/delete_movie.h"
#include "../retrieve_movie/retrieve_movie.h"

void get_operation(char *db_path, packet *packet, int packet_size, response *response, int response_size)
{
    FILE *fptr;

    switch (packet->op)
    {
    case 1:
        printf("Listagem de filmes\n");
        break;
    case 2:
        printf("Adicionando Filme\n");
        packet->deleted = 0;
        add_movie(db_path, packet, packet_size);
        break;
    case 3:
        printf("Removendo Filme\n");
        delete_movie(db_path, packet, packet_size);
        break;
    case 4:
        printf("Retornando Filme\n");
        retrieve_movie(db_path, packet, packet_size, response, response_size);
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