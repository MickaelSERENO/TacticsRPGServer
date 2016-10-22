#include "Map/Traces/DynamicTrace.h"

DynamicTrace::DynamicTrace(const char* name, uint32_t nbCasesX, uint32_t nbCasesY, uint32_t sizeX, uint32_t sizeY) : Trace(name), m_sizeX(sizeX), m_sizeY(sizeY), m_nbCasesX(nbCasesX), m_nbCasesY(nbCasesY)
{
	for(uint32_t i=0; i < nbCasesX; i++)
	{
		m_tiles.push_back(std::vector<Tile*>());
		for(uint32_t j=0; j < nbCasesY; j++)
			m_tiles[i].push_back(NULL);
	}
}

Tile* DynamicTrace::getTileTraceCoords(int x, int y)
{
	if(x < 0 || y < 0 || x >= m_nbCasesX * m_sizeX || y >= m_nbCasesY * m_sizeY)
		return NULL;
	return m_tiles[x/m_sizeX][y/m_sizeY];
}

void DynamicTrace::addTile(Tile* tile, uint32_t x, uint32_t y)
{
	bool isAdded = false;
	for(uint32_t i = 0; i < tile->getNbCasesX(); i++)
	{
		if(x >= (m_nbCasesX - i) * m_sizeX)
		   break;	
		for(uint32_t j=0; j < tile->getNbCasesY(); j++)
		{
			if(y >= (m_nbCasesY - i) * m_sizeY)
				break;
			isAdded = true;
			m_tiles[x/m_sizeX][y/m_sizeY] = tile;
		}
	}

	if(isAdded)
		Trace::addTile(tile, x, y);
}
