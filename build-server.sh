gcc serializers/serialize_int/serialize_int.c -o serializers/serialize_int/serialize_int.o -c
gcc serializers/serialize_char/serialize_char.c -o serializers/serialize_char/serialize_char.o -c
gcc serializers/deserialize_int/deserialize_int.c -o serializers/deserialize_int/deserialize_int.o -c
gcc serializers/deserialize_char/deserialize_char.c -o serializers/deserialize_char/deserialize_char.o -c

gcc server/functions/print_packet/print_packet.c -o server/functions/print_packet/print_packet.o -c
gcc server/functions/print_response/print_response.c -o server/functions/print_response/print_response.o -c
gcc server/functions/get_operation/get_operation.c -o server/functions/get_operation/get_operation.o -c
gcc server/functions/add_movie/add_movie.c -o server/functions/add_movie/add_movie.o -c
gcc server/functions/read_movie/read_movie.c -o server/functions/read_movie/read_movie.o -c
gcc server/functions/delete_movie/delete_movie.c -o server/functions/delete_movie/delete_movie.o -c
gcc server/functions/retrieve_movie/retrieve_movie.c -o server/functions/retrieve_movie/retrieve_movie.o -c
gcc server/functions/list_movies/list_movies.c -o server/functions/list_movies/list_movies.o -c
gcc server/functions/list_movies_by_genre/list_movies_by_genre.c -o server/functions/list_movies_by_genre/list_movies_by_genre.o -c

gcc wrappers/socket/socket.c -o wrappers/socket/socket.o -c
gcc wrappers/bind/bind.c -o wrappers/bind/bind.o -c
gcc wrappers/listen/listen.c -o wrappers/listen/listen.o -c
gcc wrappers/accept/accept.c -o wrappers/accept/accept.o -c
gcc wrappers/close/close.c -o wrappers/close/close.o -c
gcc wrappers/writen/writen.c -o wrappers/writen/writen.o -c
gcc server/server.c -o server/server.o -c

gcc -o bin/server server/server.o \
                  serializers/serialize_int/serialize_int.o \
                  serializers/serialize_char/serialize_char.o \
                  serializers/deserialize_int/deserialize_int.o \
                  serializers/deserialize_char/deserialize_char.o \
                  wrappers/socket/socket.o \
                  wrappers/bind/bind.o \
                  wrappers/listen/listen.o \
                  wrappers/accept/accept.o \
                  wrappers/close/close.o \
                  wrappers/writen/writen.o \
                  server/functions/get_operation/get_operation.o \
                  server/functions/add_movie/add_movie.o \
                  server/functions/read_movie/read_movie.o \
                  server/functions/delete_movie/delete_movie.o \
                  server/functions/retrieve_movie/retrieve_movie.o \
                  server/functions/print_packet/print_packet.o \
                  server/functions/print_response/print_response.o \
                  server/functions/list_movies/list_movies.o \
                  server/functions/list_movies_by_genre/list_movies_by_genre.o