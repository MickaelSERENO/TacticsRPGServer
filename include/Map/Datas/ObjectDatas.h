#ifndef  OBJECTDATAS_INC
#define  OBJECTDATAS_INC

#include "CSV.h"
#include "Map/Tiles/TileObject.h"
#include <vector>

typedef TileObject*(*createObjectPtr)(uint32_t, uint32_t, uint32_t, uint32_t, void*);

/** \struct ObjectDatas
 * \brief object datas about objects. In fact, it keeps CSV string about tiles and files (where to look for creating tiles which will create the Object), and the Object characteristics, such as tileSize and nbCases*/
struct ObjectDatas
{
	createObjectPtr createObject;
	std::vector<char*> CSVTileID;
	std::vector<char*> CSVFileID;
	void* info;
	uint32_t nbCasesX;
	uint32_t nbCasesY;
	uint32_t tileSizeX;
	uint32_t tileSizeY;
};

#endif
