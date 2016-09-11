#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Client.h"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define PORT 9339
#define closesocket(param) close(param)

//Clients values
std::list<Client*> clientConnected;
pthread_mutex_t    clientMutex=PTHREAD_MUTEX_INITIALIZER;

void* socketHandler(void* c);

int main (int argc, char *argv[])
{
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0); //Protocol TCP/IP
	SOCKET clientSocket;
	SOCKADDR_IN server;
	SOCKADDR_IN client;
	socklen_t serverLength = sizeof(server);
	socklen_t clientLength;

	if(serverSocket != SOCKET_ERROR)
	{
		int sockErr;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_family = AF_INET;
		server.sin_port = htons(PORT);

		sockErr = bind(serverSocket, (SOCKADDR*)&server, serverLength);
		if(sockErr != SOCKET_ERROR)
		{
			sockErr = listen(serverSocket, 5);
			if(sockErr != SOCKET_ERROR)
			{
				pthread_t threadId;
				while(clientSocket = accept(serverSocket, (SOCKADDR*)&client, &clientLength))
				{
					//Add the client to the array
					pthread_mutex_lock(&clientMutex);
					Client c  = new Client();
					c->socket = clientSocket;
					c->sin    = client;
					c->length = clientLength;
					clientConnected.push_back(c);
					pthread_mutex_unlock(&clientMutex);

					//Launch the thread
					pthread_create(&threadId, NULL, socketHandler, (void*)c);
					pthread_detach(threadId);
				}
			}
			else
				perror("Error : can't listen the server");
		}
		else
			perror("Error : can't bind the server");
	}
	else
		perror("Error : can't create the socket");
	close(serverSocket);
	return EXIT_SUCCESS;
}

void* socketHandler(void* c)
{
	Client* client = (Client*) c;
	FILE* fileClient = fdopen(client->socket, "r");
	if(fileClient == NULL)
		perror("Error in loading the socket as a FILE*");
	char message[2000];
	int readSize;
	char command;
	printf("Client connected \n");

	while((command = getc(fileClient)) != EOF)
	{
		//The command is contained in the first byte
		printf("%d command \n", command);
	}

	//Delete the client
	pthread_mutex_lock(&clientMutex);
	clientConnected.remove(client);
	pthread_mutex_unlock(&clientMutex);
	printf("Client Disconnected \n");
	delete client;

	return NULL;
}
