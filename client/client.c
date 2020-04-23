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

    exit(0);
}