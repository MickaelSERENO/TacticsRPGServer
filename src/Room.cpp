#include "Room.h"

Room* Room::singleton = NULL;
pthread_mutex_t Room::roomMutex=PTHREAD_MUTEX_INITIALIZER;

SubRoom::SubRoom(uint8_t size) : m_size(size)
{
}

void SubRoom::addClient(Client* client)
{
	m_clients.push_back(client);
	if(!isFull())
		client->sendWaitRoom();
}

const std::list<Client*> SubRoom::getClients() const
{
	return m_clients;
}

bool SubRoom::isFull() const
{
	return m_size == m_clients.size();
}

bool SubRoom::disconnectClient(Client* client)
{
	for(std::list<Client*>::iterator it = m_clients.begin(); it != m_clients.end(); it++)
	{
		if((*it) == client)
		{
			m_clients.erase(it);
			return true;
		}
	}	

	return false;
}

void Room::initSingleton()
{
	singleton = new Room();
}

Room* Room::getSingleton()
{
	return singleton;
}

void Room::freeSingleton()
{
	delete singleton;
}

void Room::lockMutex()
{
	pthread_mutex_lock(&roomMutex);
}

void Room::unlockMutex()
{
	pthread_mutex_unlock(&roomMutex);
}

Room::Room()
{

}

Room::~Room()
{
	for(auto& it : m_subRooms)
		for(auto& it2 : it.second)
			delete it2;
}

const std::list<SubRoom*>& Room::getSubRooms(const std::string& key) const
{
	return m_subRooms.find(key)->second;
}

const SubRoom*  Room::addClientToRoom(Client* client, const std::string& map)
{
	//Add the client to an existing room
	std::map<std::string, std::list<SubRoom*>>::iterator it = m_subRooms.find(map);	
	for(auto& it2 : it->second)
	{
		if(!it2->isFull())
		{
			it2->addClient(client);
			return it2;
		}
	}

	//Or create a room
	SubRoom* sr = new SubRoom(2);
	sr->addClient(client);
	if(it != m_subRooms.end())
		it->second.push_back(sr);
	else
		m_subRooms.insert(std::pair<std::string, std::list<SubRoom*>>(map, std::list<SubRoom*>(1, sr)));
	return sr;
}

void Room::disconnectClient(Client* client)
{
	for(auto& it : m_subRooms)
	{
		for(auto& it2 : it.second)
			if(it2->disconnectClient(client))
				return;
	}
}
