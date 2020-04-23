#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int Inet_pton(int af, const char *src, void *dst)
{
    if (inet_pton(af, src, dst) < 0)
    {
        printf("error on converting input to IP address\n");
        exit(0);
    }
}