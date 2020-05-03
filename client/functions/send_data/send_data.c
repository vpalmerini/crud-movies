#include <stdio.h>
#include <stdlib.h>

#include "../../../serializers/packet.h"
#include "../../../serializers/response.h"

#include "../../../serializers/serialize_packet/serialize_packet.h"
#include "../../../serializers/deserialize_response/deserialize_response.h"
#include "../../../wrappers/writen/writen.h"
#include "../../../wrappers/readline/readline.h"

void send_data(int sock_fd, packet *packet, response *response, int buffer_size, int field_size, int op, int packet_size, int response_size)
{
    char *buffer = (char *)calloc(buffer_size, sizeof(char));
    char *resp_buffer = (char *)calloc(response_size, sizeof(char));

    serialize_packet(buffer, packet, field_size, packet_size);
    Writen(sock_fd, buffer, buffer_size);

    if (op != 3)
    {
        if (Readline(sock_fd, resp_buffer, response_size) == 0)
        {
            printf("str_cli: server terminated prematurely\n");
            exit(0);
        }

        deserialize_response(resp_buffer, response, packet_size, field_size);

        if (response->n_movies > 0)
        {
            int i;
            switch (op)
            {
            case 1:
                for (i = 0; i < response->n_movies; i++)
                {
                    printf("ID: %d\n", response->packets[i].movie_id);
                    printf("Title: %s", response->packets[i].movie_title);
                    printf("Genre: %s", response->packets[i].movie_genre);
                    printf("Sinopsis: %s", response->packets[i].movie_sinopsis);
                    printf("Rooms: %s", response->packets[i].rooms);
                    printf("\n");
                }
                break;
            case 2:
                printf("ID do filme adicionado: %d\n", response->packets[0].movie_id);
                break;
            case 4:
                printf("ID: %d\n", response->packets[0].movie_id);
                printf("Title: %s", response->packets[0].movie_title);
                printf("Genre: %s", response->packets[0].movie_genre);
                printf("Sinopsis: %s", response->packets[0].movie_sinopsis);
                printf("Rooms: %s", response->packets[0].rooms);
                break;
            case 5:
                printf("Título: %s", response->packets[0].movie_title);
                break;
            case 6:
                for (i = 0; i < response->n_movies; i++)
                {
                    printf("ID: %d\n", response->packets[i].movie_id);
                    printf("Title: %s", response->packets[i].movie_title);
                    printf("Genre: %s", response->packets[i].movie_genre);
                    printf("Sinopsis: %s", response->packets[i].movie_sinopsis);
                    printf("Rooms: %s", response->packets[i].rooms);
                    printf("\n");
                }
                break;
            case 7:
                for (i = 0; i < response->n_movies; i++)
                {
                    printf("Title: %s", response->packets[i].movie_title);
                    printf("Rooms: %s", response->packets[i].rooms);
                    printf("\n");
                }
                break;
            default:
                break;
            }
        }
    }

    free(resp_buffer);
    free(buffer);

    return;
}