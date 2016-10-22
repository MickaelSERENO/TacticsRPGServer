#ifndef  DYNAMICANIM_INC
#define  DYNAMICANIM_INC

#include "Map/Tiles/Tile.h"

class DynamicAnim : public Tile
{
	public:
		DynamicAnim(void* info, uint32_t posX, uint32_t posY);
	private:
		uint32_t m_posX;
		uint32_t m_posY;
};

#endif
