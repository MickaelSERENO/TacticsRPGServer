#include "GameDB.h"

GameDB* GameDB::singleton = NULL;

void GameDB::initSingleton()
{
	singleton = new GameDB();
}

GameDB* GameDB::getSingleton()
{
	return singleton;
}

GameDB::GameDB()
{
	//We init the maps
	
}
