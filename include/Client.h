#ifndef  CLIENT_INC
#define  CLIENT_INC

#include "command.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <list>
#include <string>

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

class Client
{
	public:
		Client(SOCKET socket, SOCKADDR_IN sin, socklen_t length);
		~Client();
		SOCKET      getSocket() const;
		SOCKADDR_IN getSin() const;
		bool isLogged() const;

		void sendIsLogged(bool isLogged, const char* mail);
		void sendWaitRoom();
		void sendStart();
	private:
		SOCKET m_socket;
		SOCKADDR_IN m_sin;
		socklen_t m_length;

		bool m_isLogged = false;
		std::string m_mail; //Use as an ID
};

extern std::list<Client*> clientConnected;
extern pthread_mutex_t    clientMutex;

#endif
