#ifndef  TESTTILE_INC
#define  TESTTILE_INC

#include "Map/Tiles/Tile.h"

class TestTile : public Tile
{
	public:
		TestTile(void* info);
		uint32_t m_coucou=25987;
};

#endif
