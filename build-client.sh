gcc serializers/serialize_int/serialize_int.c -o serializers/serialize_int/serialize_int.o -c
gcc serializers/serialize_char/serialize_char.c -o serializers/serialize_char/serialize_char.o -c
gcc serializers/deserialize_int/deserialize_int.c -o serializers/deserialize_int/deserialize_int.o -c
gcc serializers/deserialize_char/deserialize_char.c -o serializers/deserialize_char/deserialize_char.o -c
gcc serializers/serialize_packet/serialize_packet.c -o serializers/serialize_packet/serialize_packet.o -c
gcc serializers/deserialize_packet/deserialize_packet.c -o serializers/deserialize_packet/deserialize_packet.o -c
gcc serializers/deserialize_response/deserialize_response.c -o serializers/deserialize_response/deserialize_response.o -c

gcc client/functions/add_movie/add_movie.c -o client/functions/add_movie/add_movie.o -c
gcc client/functions/ask_params/ask_params.c -o client/functions/ask_params/ask_params.o -c
gcc client/functions/get_operation/get_operation.c -o client/functions/get_operation/get_operation.o -c
gcc client/functions/list_operations/list_operations.c -o client/functions/list_operations/list_operations.o -c
gcc client/functions/delete_movie/delete_movie.c -o client/functions/delete_movie/delete_movie.o -c
gcc client/functions/retrieve_movie/retrieve_movie.c -o client/functions/retrieve_movie/retrieve_movie.o -c
gcc client/functions/retrieve_title/retrieve_title.c -o client/functions/retrieve_title/retrieve_title.o -c
gcc client/functions/list_by_genre/list_by_genre.c -o client/functions/list_by_genre/list_by_genre.o -c

gcc wrappers/socket/socket.c -o wrappers/socket/socket.o -c
gcc wrappers/writen/writen.c -o wrappers/writen/writen.o -c
gcc wrappers/inet_pton/inet_pton.c -o wrappers/inet_pton/inet_pton.o -c
gcc wrappers/connect/connect.c -o wrappers/connect/connect.o -c
gcc wrappers/readline/readline.c -o wrappers/readline/readline.o -c
gcc client/client.c -o client/client.o -c

gcc -o bin/client client/client.o \
                  serializers/serialize_int/serialize_int.o \
                  serializers/serialize_char/serialize_char.o \
                  serializers/deserialize_int/deserialize_int.o \
                  serializers/deserialize_char/deserialize_char.o \
                  serializers/serialize_packet/serialize_packet.o \
                  serializers/deserialize_packet/deserialize_packet.o \
                  serializers/deserialize_response/deserialize_response.o \
                  wrappers/socket/socket.o \
                  wrappers/writen/writen.o \
                  wrappers/inet_pton/inet_pton.o \
                  wrappers/connect/connect.o \
                  wrappers/readline/readline.o \
                  client/functions/add_movie/add_movie.o \
                  client/functions/ask_params/ask_params.o \
                  client/functions/get_operation/get_operation.o \
                  client/functions/list_operations/list_operations.o \
                  client/functions/delete_movie/delete_movie.o \
                  client/functions/retrieve_movie/retrieve_movie.o \
                  client/functions/retrieve_title/retrieve_title.o \
                  client/functions/list_by_genre/list_by_genre.o