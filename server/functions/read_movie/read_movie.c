#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../packet.h"

void read_movie(char *file_path, packet *packet, int packet_size)
{
    FILE *fptr;
    if ((fptr = fopen(file_path, "rb")) == NULL)
    {
        printf("%s\n", strerror(errno));
        exit(1);
    }

    fread(packet, packet_size, 1, fptr);
    fclose(fptr);

    return;
}