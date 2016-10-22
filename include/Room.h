#ifndef  ROOM_INC
#define  ROOM_INC

#include <list>
#include <map>
#include <pthread.h>
#include "Client.h"

class SubRoom
{
	public:
		SubRoom(uint8_t size);

		void addClient(Client* client);

		/** \brief disconnect a Client if exist in the subroom
		 * \param client the Client to disconnect
		 * \return return if the Client existed in the subroom*/
		bool disconnectClient(Client* client);

		const std::list<Client*> getClients() const;

		bool isFull() const;
	private:
		std::list<Client*> m_clients; //The list of clients for the room
		uint8_t            m_size;    //The size of the room
};

class Room
{
	public:
		static void initSingleton();
		static Room* getSingleton();
		static void freeSingleton();

		static void lockMutex();
		static void unlockMutex();

		~Room();

		const           std::list<SubRoom*>& getSubRooms(const std::string& key) const; 
		const SubRoom*  addClientToRoom(Client* client, const std::string& map);
		void            disconnectClient(Client* client);
	private:
		Room();
		static Room* singleton;
		static pthread_mutex_t roomMutex;
		std::map<std::string, std::list<SubRoom*>> m_subRooms;
};

#endif
