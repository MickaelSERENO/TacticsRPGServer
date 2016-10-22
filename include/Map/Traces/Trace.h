#ifndef  TRACE_INC
#define  TRACE_INC

#include "Map/Tiles/Tile.h"
#include <string>
#include <vector>

/** \class Trace
 * \brief Basic abstract class for traces. Don't use it directly*/

class Trace
{
	public:
		/** \brief Basic constructor for Trace.*/
		Trace(const std::string& name);

		/** \brief Basic destructor for Trace.*/
		~Trace();
		virtual Tile* getTileTraceCoords(int x, int y)=0;

		/** \brief add the tile at the position x, y.
		 * \param x the x position in pixels coords
		 * \param y the y position in pixels coords*/
		virtual void addTile(Tile* tile, uint32_t x, uint32_t y);

		const std::string& getName() const;
	protected:
		std::vector<std::vector<Tile*>> m_tiles;
		std::string m_name;
};

#endif
