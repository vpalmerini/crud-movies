#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

#include "../../../serializers/packet.h"
#include "../../../serializers/response.h"

#include "../get_operation/get_operation.h"
#include "../../../wrappers/writen/writen.h"

#include "../../../serializers/serialize_response/serialize_response.h"
#include "../../../serializers/deserialize_packet/deserialize_packet.h"

void receive_data(int sock_fd, int buffer_size, packet *packet, int field_size, char *db_path, response *response, int response_size, int *counter, int packet_size)
{
    ssize_t n;
    char *buffer = (char *)calloc(buffer_size, sizeof(char));
    char *buffer_response = (char *)calloc(response_size, sizeof(char));

again:
    while ((n = read(sock_fd, buffer, buffer_size)) > 0)
    {
        deserialize_packet(buffer, packet, field_size, packet_size);
        int op = packet->op;
        get_operation(db_path, packet, packet_size, response, response_size, counter);

        if (op != 3)
        {
            serialize_response(buffer_response, response, packet_size, field_size);
            Writen(sock_fd, buffer_response, response_size);
        }
    }

    if (n < 0 && errno == EINTR)
    {
        goto again;
    }
    else if (n < 0)
    {
        printf("Error to receive data from client\n");
    }

    free(buffer);
    free(buffer_response);
}