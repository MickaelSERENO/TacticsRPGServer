#ifndef  STATICTRACE_INC
#define  STATICTRACE_INC

#include "Map/Traces/Trace.h"

/** \class StaticTrace
 * \brief StaticTrace class. It is to manage tiles which have a pattern position.*/
class StaticTrace : public Trace
{
	public:
		/** \brief constructor for StaticTrace. Initialise the pattern of the trace.
		 * \param parent the parent of the trace
		 * \param name the name of the trace
		 * \param sizeX the width for each tiles
		 * \param sizeY the height for each tiles
		 * \param nbCasesX the number of tiles per row
		 * \param nbCasesY the number of tiles per column
		 * \param padX the space before the trace starts.
		 * \param padY the space before the trace starts.*/
		StaticTrace(const std::string& name, 
				    uint32_t sizeX, uint32_t sizeY, uint32_t nbCasesX, uint32_t nbCasesY,
				    uint32_t padX, uint32_t padY);

		virtual Tile* getTileTraceCoords(int x, int y);
		void addTile(Tile* tile, uint32_t x, uint32_t y);
		void addTileInTraceCoord(Tile* tile, uint32_t x, uint32_t y);
	private:
		uint32_t m_nbCasesX;
		uint32_t m_nbCasesY;
		uint32_t m_sizeX;
		uint32_t m_sizeY;
		uint32_t m_padX;
		uint32_t m_padY;
};

#endif
