#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int Close(int fd)
{
    if (close(fd) < 0)
    {
        printf("Error on closing socket\n");
        exit(0);
    }

    return 0;
}