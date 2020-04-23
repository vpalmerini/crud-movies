#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

int Connect(int fd, const struct sockadrr *addrr, socklen_t len)
{
    if (connect(fd, addrr, len) < 0)
    {
        printf("error on connection with the server\n");
        exit(0);
    }
}