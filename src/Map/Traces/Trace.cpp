#include "Map/Traces/Trace.h"

Trace::Trace(const std::string& name) : m_name(name)
{}

Trace::~Trace()
{
	for(uint32_t i=0; i < m_tiles.size(); i++)
	{
		for(uint32_t j=0; j < m_tiles[i].size(); j++)
		{
			Tile* tile = m_tiles[i][j];
			if(tile)
				delete tile;
		}
	}
}

void Trace::addTile(Tile* tile, uint32_t x, uint32_t y)
{
}

const std::string& Trace::getName() const
{
	return m_name;
}
