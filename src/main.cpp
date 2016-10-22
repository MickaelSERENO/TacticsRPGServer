#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <cstring>
#include <stdlib.h>
#include "Client.h"
#include "command.h"
#include "Room.h"
#include "Database.h"
#include "GameDB.h"
#include "openssl/ssl.h"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define PORT 9322
#define closesocket(param) close(param)

//Clients values
std::list<Client*> clientConnected;
pthread_mutex_t    clientMutex=PTHREAD_MUTEX_INITIALIZER;

void* socketHandler(void* c);

int main (int argc, char *argv[])
{
	Room::initSingleton();
	Database::initSingleton();
	GameDB::initSingleton();

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0); //Protocol TCP/IP
	SOCKET clientSocket;
	SOCKADDR_IN server;
	SOCKADDR_IN client;
	socklen_t serverLength = sizeof(server);
	socklen_t clientLength;

	if(serverSocket != SOCKET_ERROR)
	{
		int sockErr;
		server.sin_addr.s_addr = inet_addr("192.168.43.192");
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
					printf("CLIENT CONNECTED");
					//Add the client to the array
					pthread_mutex_lock(&clientMutex);
					Client* c = new Client(clientSocket, client, clientLength);
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

	Room::freeSingleton();
	Database::freeSingleton();
	return EXIT_SUCCESS;
}

void* socketHandler(void* c)
{
	Client* client = (Client*) c;
	printf("Client connected \n");
	
	uint8_t message[65536];
	int16_t readSize;
	int16_t messageSize;

	while(readSize = read(client->getSocket(), &messageSize, 2))
	{
		if(readSize <= 0)
			break;

		if((readSize = read(client->getSocket(), message, messageSize)) < 0)
			break;

		message[messageSize+1] = '\0';
		std::cout << "Message Size " << messageSize << " Message " << message << std::endl;

		//The command is contained in the first byte
		uint8_t command = message[0];
		switch(command)
		{
			//New inscription
			case GET_INSCRIPTION:
			case GET_LOG_IN:
			{
				//Get the mail
				uint8_t mailLength = message[1];
				uint8_t*   mail    = (uint8_t*)malloc(sizeof(char)*(mailLength+1));
				memcpy(mail, message + 2, mailLength);
				mail[mailLength] = '\0';

				//Get the password
				uint8_t passwordLength = message[mailLength+2];
				uint8_t*   password    = (uint8_t*)malloc(sizeof(char)*(passwordLength+1));
				memcpy(password, message + (3 + mailLength), passwordLength);
				password[passwordLength] = '\0';

				//Encrypt the password
				size_t length = passwordLength;
				uint8_t hash[SHA_DIGEST_LENGTH+1];
				SHA1(password, length, hash);
				hash[SHA_DIGEST_LENGTH] = '\0';

				if(command == GET_INSCRIPTION)
				{
					//Add to the database
					Database::lockMutex();
					Database::getSingleton()->inscription(mail, hash);
					Database::unlockMutex();
				}

				else if(command == GET_LOG_IN)
				{
					Database::lockMutex();
					bool isLogged = Database::getSingleton()->logIn(mail, hash);
					Database::unlockMutex();

					client->sendIsLogged(isLogged, (const char*)(mail));
					free(mail);
					free(password);
				}

				break;
			}

			case GET_FETCH_ROOM:
			{
				if(client->isLogged())
				{
					char room[128];
					memcpy(room, message+1, messageSize-1);
					Room::lockMutex();
					Room::getSingleton()->addClientToRoom(client, room);
					Room::unlockMutex();
				}
				break;
			}

			default:
			{
				std::cout << "command " << command << " is not implemented yet" << std::endl;
			}
		}
	}

	//Delete the client
	pthread_mutex_lock(&clientMutex);
	clientConnected.remove(client);
	pthread_mutex_unlock(&clientMutex);
	printf("Client Disconnected \n");

	//We need to disconnect the client from the server
	Room::getSingleton()->disconnectClient(client);
	delete client;

	return NULL;
}
