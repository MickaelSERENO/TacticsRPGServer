#ifndef  ROOM_INC
#define  ROOM_INC

class SubRoom
{
	public:
		SubRoom();
		void addClient(Client* client);
		const std::list<Client*> getClients() const;
	private:
		std::list<Client*> m_clients;
};

class Room
{
	public:
		Room();
		~Room();
		const std::list<SubRoom*>& getSubRooms() const; 
		void addSubRoom(Client* firstClient);
	private:
		std::list<SubRoom*> m_subRooms;
};

#endif
