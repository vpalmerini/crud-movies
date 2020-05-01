#include <stdio.h>
#include <stdlib.h>

#include "../packet.h"
#include "../response.h"
#include "../add_movie/add_movie.h"
#include "../read_movie/read_movie.h"
#include "../delete_movie/delete_movie.h"
#include "../retrieve_movie/retrieve_movie.h"
#include "../list_movies/list_movies.h"

void get_operation(char *db_path, packet *packet, int packet_size, response *response, int response_size, int *counter)
{
    FILE *fptr;

    switch (packet->op)
    {
    case 1:
        printf("Listagem de filmes\n");
        list_movies(db_path, packet, packet_size, response);
        break;
    case 2:
        printf("Adicionando Filme\n");
        packet->deleted = 0;
        add_movie(db_path, packet, packet_size, counter);
        retrieve_movie(db_path, packet, packet_size, response);
        break;
    case 3:
        printf("Removendo Filme\n");
        delete_movie(db_path, packet, packet_size);
        break;
    case 4:
        printf("Retornando Filme\n");
        retrieve_movie(db_path, packet, packet_size, response);
        break;
    case 5:
        printf("Retornando Título do Filme\n");
        retrieve_movie(db_path, packet, packet_size, response);
        break;
    case 6:
        printf("Listando Filmes de um Gênero\n");
        break;
    case 7:
        printf("Listagem de filmes (apenas Título e Salas)\n");
        list_movies(db_path, packet, packet_size, response);
        break;
    default:
        printf("Operação inválida!\n");
        break;
    }
}