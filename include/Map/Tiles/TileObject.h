#ifndef  TILEOBJECT_INC
#define  TILEOBJECT_INC

#include "Map/Tiles/Tile.h"
#include "stdlib.h"
#include <vector>

class TileObject : public Tile
{
	public:
		TileObject(uint32_t nbCasesX, uint32_t nbCasesY, uint32_t tileSizeX, uint32_t tileSizeY, void* info);

		/** \brief Add the tile 'tile' at the position x, y which are case coords */
		void addTile(Tile* tile, uint32_t x, uint32_t y);
	private:
		std::vector<std::vector<Tile*>> m_tiles;
		uint32_t m_tileSizeX;
		uint32_t m_tileSizeY;
};

#endif
