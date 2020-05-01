#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

// RedHat: readline-devel / Debian: libreadline-dev
#include <readline/readline.h>
#include <readline/history.h>

#include "client.h"

unsigned char *serialize_packet(unsigned char *buffer, packet *packet, int field_size);
unsigned char *deserialize_packet(unsigned char *buffer, packet *packet, int field_size);
void send_data(int sock_fd, packet *packet, response *response, int buffer_size, int field_size, int op);
unsigned char *deserialize_response(unsigned char *buffer, response *response, int packet_size, int field_size);
ssize_t Readline(int fd, void *vptr, size_t maxlen);

int main(int argc, char **argv)
{
    int sock_fd;
    int selected_op;
    struct sockaddr_in server_address;
    packet packet;
    response response;

    if (argc != 3)
    {
        printf("Argumentos: <Endereço IP> <Porta>\n");
        exit(0);
    }

    const int SERVER_PORT = strtol(argv[2], NULL, 10);
    sock_fd = Socket(PF_INET, SOCK_STREAM, 0);

    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);

    Inet_pton(AF_INET, argv[1], &server_address.sin_addr);

    Connect(sock_fd, (SA *)&server_address, sizeof(server_address));

    list_operations();

    selected_op = get_operation(stdin, FIELD);
    printf("Operação Escolhida: %d\n", selected_op);

    while (selected_op != 0)
    {
        ask_params(stdin, selected_op, &packet, FIELD);
        send_data(sock_fd, &packet, &response, MAXLINE, FIELD, selected_op);
        list_operations();
        selected_op = get_operation(stdin, FIELD);
    }

    exit(0);
}

unsigned char *serialize_packet(unsigned char *buffer, packet *packet, int field_size)
{
    buffer = serialize_int(buffer, packet->op);
    buffer = serialize_int(buffer, packet->movie_id);
    buffer = serialize_char(buffer, packet->movie_title, field_size);
    buffer = serialize_char(buffer, packet->movie_genre, field_size);
    buffer = serialize_char(buffer, packet->movie_sinopsis, field_size);
    buffer = serialize_char(buffer, packet->rooms, field_size);

    return buffer;
}

unsigned char *deserialize_packet(unsigned char *buffer, packet *packet, int field_size)
{
    buffer = deserialize_int(buffer, &packet->op);
    buffer = deserialize_int(buffer, &packet->movie_id);
    buffer = deserialize_char(buffer, packet->movie_title, field_size);
    buffer = deserialize_char(buffer, packet->movie_genre, field_size);
    buffer = deserialize_char(buffer, packet->movie_sinopsis, field_size);
    buffer = deserialize_char(buffer, packet->rooms, field_size);

    return buffer + (MAXLINE - (8 + 4 * field_size));
}

void send_data(int sock_fd, packet *packet, response *response, int buffer_size, int field_size, int op)
{
    char *buffer = (char *)calloc(buffer_size, sizeof(char));
    char *resp_buffer = (char *)calloc(RESPONSE, sizeof(char));

    serialize_packet(buffer, packet, field_size);
    Writen(sock_fd, buffer, buffer_size);

    if (op != 3)
    {
        if (Readline(sock_fd, resp_buffer, RESPONSE) == 0)
        {
            printf("str_cli: server terminated prematurely\n");
            exit(0);
        }

        deserialize_response(resp_buffer, response, MAXLINE, field_size);

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

unsigned char *deserialize_response(unsigned char *buffer, response *response, int packet_size, int field_size)
{
    buffer = deserialize_int(buffer, &response->n_movies);
    printf("Nº Movies: %d\n", response->n_movies);

    if (response->n_movies == 0)
    {
        printf("Nenhum filme encontrado\n");
        return buffer;
    }

    int i;
    for (i = 0; i < response->n_movies; i++)
    {
        buffer = deserialize_packet(buffer, &response->packets[i], field_size);
    }

    return buffer;
}

ssize_t Readline(int fd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char c, *ptr;

    ptr = vptr;
    for (n = 0; n < maxlen; n++)
    {
    again:
        if ((rc = read(fd, &c, 1)) == 1)
        {
            *ptr++ = c;
        }
        else if (rc == 0)
        {
            *ptr = 0;
            return (n - 1);
        }
        else
        {
            if (errno == EINTR)
                goto again;
            return (-1);
        }
    }
    *ptr = 0;
    return (n);
}