#include <stdio.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "server.h"

int main(int argc, char **argv)
{
    int sock_fd, new_fd;
    socklen_t client_len;
    pid_t childpid;

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
            exit(0);
        }

        Close(new_fd);
    }

    exit(0);
}