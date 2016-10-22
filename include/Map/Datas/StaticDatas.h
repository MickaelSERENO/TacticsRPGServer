#ifndef  STATICDATAS_INC
#define  STATICDATAS_INC

#include "Map/Tiles/StaticTile.h"

typedef StaticTile*(*createStaticTilePtr)(void* info);

struct StaticDatas
{
	createStaticTilePtr createStaticTile;
	void* info;
};

#endif
