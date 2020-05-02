#define MAXLINE 4096
#define OPERATION 32
#define FIELD 256
#define ROOMS 20
#define LISTENQ 1024
#define RESPONSE 20482
#define SA struct sockaddr
#define stdin stdin

#include "functions/packet.h"
#include "functions/response.h"
#include "functions/print_packet/print_packet.h"
#include "functions/print_response/print_response.h"
#include "functions/get_operation/get_operation.h"
#include "functions/add_movie/add_movie.h"
#include "functions/read_movie/read_movie.h"
#include "functions/delete_movie/delete_movie.h"
#include "functions/retrieve_movie/retrieve_movie.h"

#include "../wrappers/socket/socket.h"
#include "../wrappers/bind/bind.h"
#include "../wrappers/listen/listen.h"
#include "../wrappers/accept/accept.h"
#include "../wrappers/close/close.h"
#include "../wrappers/writen/writen.h"

#include "../serializers/serialize_int/serialize_int.h"
#include "../serializers/serialize_char/serialize_char.h"
#include "../serializers/deserialize_int/deserialize_int.h"
#include "../serializers/deserialize_char/deserialize_char.h"
#include "../serializers/serialize_packet/serialize_packet.h"