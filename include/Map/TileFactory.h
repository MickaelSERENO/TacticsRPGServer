#ifndef  TEMPLATETILE_INC
#define  TEMPLATETILE_INC

#include "Map/Tiles/StaticTile.h"
#include "Map/Tiles/DynamicAnim.h"
#include "Map/Tiles/Tile.h"
#include "Map/Tiles/TileObject.h"

template <class T> StaticTile* staticTileFactory(void* info) 
{
	return (StaticTile*)(new T(info));
}

template <class T> Tile* dynamicTileFactory(void* info, uint32_t posX, uint32_t posY)
{
	return new T(info, posX, posY);
}

template <class T> TileObject* objectFactory(uint32_t nbCasesX, uint32_t nbCasesY, uint32_t tileSizeX, uint32_t tileSizeY, void* info)
{
	return new T(nbCasesX, nbCasesY, tileSizeX, tileSizeY, info);
}

#endif
