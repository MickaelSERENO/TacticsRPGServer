#ifndef  GAMEDB__INC
#define  GAMEDB__INC

#include "sqlite3.h"
#include "ResourcesManager.h"
#include "Map/Map.h"

class GameDB
{
	public:
		~GameDB();
		static void initSingleton();
		static GameDB* getSingleton();
	private:
		GameDB();
		ResourcesManager<Map*> m_maps;
		static GameDB* singleton;
};

#endif
