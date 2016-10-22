#ifndef  TILE_INC
#define  TILE_INC

#include "stdint.h"

class Tile
{
	public:
		Tile(void* info);		

		/** \brief return the information about the tile.
		 * \return the information about the tile. The information is stock as a pointer on void*/
		void* getInfo();

		uint32_t getNbCasesX() const;
		uint32_t getNbCasesY() const;

		/** \brief tell if the tile can be destroyed or not.
		 * return return if the tile can be destroyed*/
		bool canDestroy();
	protected:
		void*    m_info;
		bool     m_canDestroy=false;
		uint32_t m_nbCasesX=1;
		uint32_t m_nbCasesY=1;
};

#endif
