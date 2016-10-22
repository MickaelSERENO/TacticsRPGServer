#include "Map/Tiles/Tile.h"

Tile::Tile(void* info) : m_info(info)
{
}

void* Tile::getInfo()
{
	return m_info;
}

bool Tile::canDestroy()
{
	return m_canDestroy;
}

uint32_t Tile::getNbCasesX() const
{
	return m_nbCasesX;
}

uint32_t Tile::getNbCasesY() const
{
	return m_nbCasesY;
}
