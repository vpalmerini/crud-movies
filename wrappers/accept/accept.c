#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

int Accept(int fd, struct sockaddr *addrr, socklen_t *len)
{
    if (accept(fd, addrr, len) < 0)
    {
        printf("Error on accepting connection\n");
        exit(0);
    }

    return 0;
}