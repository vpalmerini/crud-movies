gcc wrappers/socket/socket.c -o wrappers/socket/socket.o -c
gcc wrappers/bind/bind.c -o wrappers/bind/bind.o -c
gcc wrappers/listen/listen.c -o wrappers/listen/listen.o -c
gcc wrappers/accept/accept.c -o wrappers/accept/accept.o -c
gcc wrappers/close/close.c -o wrappers/close/close.o -c
gcc wrappers/writen/writen.c -o wrappers/writen/writen.o -c
gcc server/server.c -o server/server.o -c

gcc -o bin/server server/server.o wrappers/socket/socket.o wrappers/bind/bind.o wrappers/listen/listen.o wrappers/accept/accept.o wrappers/close/close.o wrappers/writen/writen.o