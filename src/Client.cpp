#include "Client.h"

Client::Client(SOCKET socket, SOCKADDR_IN sin, socklen_t length) :
	m_socket(socket), m_sin(sin), m_length(length)
{}

Client::~Client()
{
	close(m_socket);
}

SOCKET Client::getSocket() const
{
	return m_socket;
}

SOCKADDR_IN Client::getSin() const
{
	return m_sin;
}

bool Client::isLogged() const
{
	return m_isLogged;
}

void Client::sendIsLogged(bool isLogged, const char* mail)
{
	uint8_t message[4];
	*((short*)message) = 2;
	message[2] = SEND_LOG_SUCCESS;
	message[3] = (isLogged) ? 1 : 0;

	write(m_socket, message, 4);

	m_isLogged = isLogged;
	if(isLogged)
		m_mail = mail;
}

void Client::sendWaitRoom()
{
	char message = SEND_WAIT_ROOM;
	write(m_socket, &message, 1);
}
