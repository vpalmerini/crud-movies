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
void send_data(int sock_fd, packet *packet, int buffer_size, int field_size);

int main(int argc, char **argv)
{
    int sock_fd;
    int selected_op;
    struct sockaddr_in server_address;
    packet packet;

    if (argc != 3)
    {
        printf("Argumentos: <Endereço IP> <Porta>\n");
        exit(0);
    }

    packet.movie_title = (char *)calloc(FIELD, sizeof(char));
    packet.movie_genre = (char *)calloc(FIELD, sizeof(char));
    packet.movie_sinopsis = (char *)calloc(FIELD, sizeof(char));
    packet.rooms = (char *)calloc(FIELD, sizeof(char));

    const int SERVER_PORT = strtol(argv[2], NULL, 10);
    sock_fd = Socket(PF_INET, SOCK_STREAM, 0);

    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);

    Inet_pton(AF_INET, argv[1], &server_address.sin_addr);

    Connect(sock_fd, (SA *)&server_address, sizeof(server_address));

    list_operations();

    selected_op = get_operation(stdin, FIELD);

    while (selected_op != 0)
    {
        ask_params(stdin, selected_op, &packet, FIELD);
        send_data(sock_fd, &packet, MAXLINE, FIELD);
        bzero(&packet, sizeof(packet));
        list_operations();
        selected_op = get_operation(stdin, FIELD);
    }

    free(packet.movie_title);
    free(packet.movie_genre);
    free(packet.movie_sinopsis);
    free(packet.rooms);

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

    printf("Op: %d\n", packet->op);
    printf("ID: %d\n", packet->movie_id);
    printf("Title: %s", packet->movie_title);
    printf("Genre: %s", packet->movie_genre);
    printf("Sinopsis: %s", packet->movie_sinopsis);
    printf("Rooms: %s", packet->rooms);

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

    printf("Op: %d\n", packet->op);
    printf("ID: %d\n", packet->movie_id);
    printf("Title: %s", packet->movie_title);
    printf("Genre: %s", packet->movie_genre);
    printf("Sinopsis: %s", packet->movie_sinopsis);
    printf("Rooms: %s", packet->rooms);

    return buffer;
}

void send_data(int sock_fd, packet *packet, int buffer_size, int field_size)
{
    char buffer[buffer_size];
    serialize_packet(buffer, packet, field_size);
    deserialize_packet(buffer, packet, field_size);

    return;
}