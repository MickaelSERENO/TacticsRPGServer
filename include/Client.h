#ifndef  CLIENT_INC
#define  CLIENT_INC

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

typedef struct Client
{
	SOCKET socket;
	SOCKADDR_IN sin;
	socklen_t length;
}Client;

extern std::list<Client*> clientConnected;
extern pthread_mutex_t    clientMutex=PTHREAD_MUTEX_INITIALIZER;

#endif
