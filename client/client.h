#define MAXLINE 4096
#define OPERATION 32
#define FIELD 256
#define ROOMS 20
#define RESPONSE 20482
#define SA struct sockaddr
#define stdin stdin

#include "functions/packet.h"
#include "functions/response.h"

#include "functions/add_movie/add_movie.h"
#include "functions/ask_params/ask_params.h"
#include "functions/get_operation/get_operation.h"
#include "functions/list_operations/list_operations.h"
#include "functions/delete_movie/delete_movie.h"
#include "functions/retrieve_movie/retrieve_movie.h"
#include "functions/retrieve_title/retrieve_title.h"
#include "functions/list_by_genre/list_by_genre.h"
#include "functions/send_data/send_data.h"

#include "../wrappers/socket/socket.h"
#include "../wrappers/writen/writen.h"
#include "../wrappers/inet_pton/inet_pton.h"
#include "../wrappers/connect/connect.h"
#include "../wrappers/readline/readline.h"

#include "../serializers/serialize_int/serialize_int.h"
#include "../serializers/serialize_char/serialize_char.h"
#include "../serializers/deserialize_int/deserialize_int.h"
#include "../serializers/deserialize_char/deserialize_char.h"
#include "../serializers/serialize_packet/serialize_packet.h"
#include "../serializers/deserialize_packet/deserialize_packet.h"
#include "../serializers/deserialize_response/deserialize_response.h"