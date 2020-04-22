#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int Bind(int fd, const struct sockaddr *addr, socklen_t len)
{
    if (bind(fd, addr, len) < 0)
    {
        printf("Error on binding socket");
        exit(0);
    }

    return 0;
}