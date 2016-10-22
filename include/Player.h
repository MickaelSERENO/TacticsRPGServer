#ifndef  PLAYER_INC
#define  PLAYER_INC

#include "Client.h"
#include "Unit.h"

class Player
{
	public:
		Player(Client* c);
		~Player();

		/** \brief Add a unit for the player. The unit*/
		void addUnit(uint8_t* message);
	private:
		Client* m_client;
		std::list<Unit*> m_units;
};

#endif
