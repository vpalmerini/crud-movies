#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

ssize_t Writen(int sock_fd, const void *buf, size_t n)
{
    ssize_t number;

    if ((number = write(sock_fd, buf, n)) < 0)
    {
        printf("Error on writing response\n");
        exit(0);
    }

    return number;
}