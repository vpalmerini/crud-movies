#ifndef GET_OPERATION_FROM_PACKET_H
#define GET_OPERATION_FROM_PACKET_H

void get_operation(char *db_path, packet *packet, int packet_size, response *response, int response_size, int *counter);

#endif