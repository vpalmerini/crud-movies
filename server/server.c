#include <stdio.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "server.h"

unsigned char *deserialize_packet(unsigned char *buffer, packet *packet, int field_size);
void receive_data(int sock_fd, int buffer_size, packet *packet, int field_size, char *db_path);
void Print_packet(packet *packet);

int main(int argc, char **argv)
{
    int sock_fd, new_fd;
    socklen_t client_len;
    pid_t childpid;
    packet packet;
    char db_path[MAXLINE] = "db.bin";

    if (argc != 2)
    {
        printf("Argumentos: <Porta>\n");
        exit(0);
    }

    packet.movie_title = (char *)calloc(FIELD, sizeof(char));
    packet.movie_genre = (char *)calloc(FIELD, sizeof(char));
    packet.movie_sinopsis = (char *)calloc(FIELD, sizeof(char));
    packet.rooms = (char *)calloc(FIELD, sizeof(char));

    struct sockaddr_in server_address, client_address;
    const int SERVER_PORT = strtol(argv[1], NULL, 10);

    sock_fd = Socket(PF_INET, SOCK_STREAM, 0);

    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(SERVER_PORT);

    Bind(sock_fd, (SA *)&server_address, sizeof(server_address));

    Listen(sock_fd, LISTENQ);

    for (;;)
    {
        client_len = sizeof(client_address);
        new_fd = Accept(sock_fd, (SA *)&client_address, &client_len);

        if ((childpid = fork()) == 0)
        {
            Close(sock_fd);
            receive_data(new_fd, MAXLINE, &packet, FIELD, db_path);
            exit(0);
        }

        Close(new_fd);
    }

    free(packet.movie_title);
    free(packet.movie_genre);
    free(packet.movie_sinopsis);
    free(packet.rooms);

    exit(0);
}

void receive_data(int sock_fd, int buffer_size, packet *packet, int field_size, char *db_path)
{
    ssize_t n;
    char *buffer = (char *)calloc(buffer_size, sizeof(char));

again:
    while ((n = read(sock_fd, buffer, buffer_size)) > 0)
    {
        deserialize_packet(buffer, packet, field_size);
        get_operation(db_path, packet, MAXLINE);
        // Print_packet(packet);
    }

    if (n < 0 && errno == EINTR)
    {
        goto again;
    }
    else if (n < 0)
    {
        printf("Error to receive data from client\n");
    }

    free(buffer);
}

unsigned char *deserialize_packet(unsigned char *buffer, packet *packet, int field_size)
{
    buffer = deserialize_int(buffer, &packet->op);
    buffer = deserialize_int(buffer, &packet->movie_id);
    buffer = deserialize_char(buffer, packet->movie_title, field_size);
    buffer = deserialize_char(buffer, packet->movie_genre, field_size);
    buffer = deserialize_char(buffer, packet->movie_sinopsis, field_size);
    buffer = deserialize_char(buffer, packet->rooms, field_size);

    return buffer;
}

void Print_packet(packet *packet)
{
    printf("Operation: %d\n", packet->op);
    printf("Movie ID: %d\n", packet->movie_id);
    printf("Movie Title: %s", packet->movie_title);
    printf("Movie Genre: %s", packet->movie_genre);
    printf("Movie Sinopsis: %s", packet->movie_sinopsis);
    printf("Movie Rooms: %s", packet->rooms);
}