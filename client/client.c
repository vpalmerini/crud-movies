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
        send_data(sock_fd, &packet, &response, MAXLINE, FIELD, selected_op, MAXLINE, RESPONSE);
        list_operations();
        selected_op = get_operation(stdin, FIELD);
        printf("Operação Escolhida: %d\n", selected_op);
    }

    exit(0);
}