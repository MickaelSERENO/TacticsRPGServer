#include "Map/Tiles/TileObject.h"

TileObject::TileObject(uint32_t nbCasesX, uint32_t nbCasesY, uint32_t tileSizeX, uint32_t tileSizeY, void* info) : Tile(info), m_tileSizeX(tileSizeX), m_tileSizeY(tileSizeY)
{
	m_nbCasesX = nbCasesX;
	m_nbCasesY = nbCasesY;
	for(uint32_t i=0; i < nbCasesX; i++)
	{
		m_tiles.push_back(std::vector<Tile*>());
		for(uint32_t j=0; j < nbCasesY; j++)
			m_tiles[i].push_back(NULL);
	}
}


void TileObject::addTile(Tile* tile, uint32_t x, uint32_t y)
{
	if(!tile || x >= m_nbCasesX || y >= m_nbCasesY)
		return;
	m_tiles[x][y] = tile;
}
