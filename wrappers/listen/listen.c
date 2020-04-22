#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

int Listen(int fd, int n)
{
    if (listen(fd, n) < 0)
    {
        printf("Error on start listening\n");
        exit(0);
    }

    return 0;
}