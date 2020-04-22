#ifndef SERVER_H
#define SERVER_H

#include "../wrappers/socket/socket.h"
#include "../wrappers/bind/bind.h"
#include "../wrappers/listen/listen.h"
#include "../wrappers/accept/accept.h"
#include "../wrappers/close/close.h"
#include "../wrappers/writen/writen.h"

#define SA struct sockaddr
#define LISTENQ 1024
#define MAXLINE 4096

#endif