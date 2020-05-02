#include <stdio.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "server.h"

void receive_data(int sock_fd, int buffer_size, packet *packet, int field_size, char *db_path, response *response, int response_size, int *counter, int packet_size);
unsigned char *serialize_response(unsigned char *buffer, response *response, int packet_size, int field_size);

int main(int argc, char **argv)
{
    int sock_fd, new_fd;
    socklen_t client_len;
    pid_t childpid;
    packet packet;
    response response;
    char db_path[MAXLINE] = "db.bin";
    int id_counter = 1;

    if (argc != 2)
    {
        printf("Argumentos: <Porta>\n");
        exit(0);
    }

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
            receive_data(new_fd, MAXLINE, &packet, FIELD, db_path, &response, RESPONSE, &id_counter, MAXLINE);
            exit(0);
        }

        Close(new_fd);
    }

    exit(0);
}

void receive_data(int sock_fd, int buffer_size, packet *packet, int field_size, char *db_path, response *response, int response_size, int *counter, int packet_size)
{
    ssize_t n;
    char *buffer = (char *)calloc(buffer_size, sizeof(char));
    char *buffer_response = (char *)calloc(response_size, sizeof(char));

again:
    while ((n = read(sock_fd, buffer, buffer_size)) > 0)
    {
        deserialize_packet(buffer, packet, field_size, packet_size);
        int op = packet->op;
        get_operation(db_path, packet, MAXLINE, response, response_size, counter);

        if (op != 3)
        {
            serialize_response(buffer_response, response, MAXLINE, field_size);
            Writen(sock_fd, buffer_response, response_size);
        }
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
    free(buffer_response);
}

unsigned char *serialize_response(unsigned char *buffer, response *response, int packet_size, int field_size)
{
    buffer = serialize_int(buffer, response->n_movies);

    int i;
    for (i = 0; i < response->n_movies; i++)
    {
        buffer = serialize_packet(buffer, &(response->packets[i]), field_size, packet_size);
    }

    return buffer;
}