#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "socket.h"

int Socket(int domain, int type, int protocol)
{
    int sock_fd;

    if ((sock_fd = socket(domain, type, protocol)) < 0)
    {
        printf("Error on creating Socket\n");
        exit(0);
    }

    return sock_fd;
}