gcc wrappers/socket/socket.c -o wrappers/socket/socket.o -c
gcc wrappers/writen/writen.c -o wrappers/writen/writen.o -c
gcc wrappers/inet_pton/inet_pton.c -o wrappers/inet_pton/inet_pton.o -c
gcc wrappers/connect/connect.c -o wrappers/connect/connect.o -c
gcc client/client.c -o client/client.o -c

gcc -o bin/client client/client.o wrappers/socket/socket.o wrappers/writen/writen.o wrappers/inet_pton/inet_pton.o wrappers/connect/connect.o