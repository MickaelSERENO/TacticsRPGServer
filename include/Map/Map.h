#ifndef  MAP_INC
#define  MAP_INC

#include "Map/TileFactory.h"
#include "Map/Tiles/Tile.h"
#include "Map/Tiles/TestTile.h"
#include "Map/Tiles/StaticTile.h"
#include "Map/Tiles/DynamicAnim.h"
#include "Map/Tiles/DefaultTile.h"
#include "Map/Tiles/TileObject.h"
#include "Map/MapFiles.h"
#include "Map/Datas/StaticDatas.h"
#include "Map/Datas/ObjectDatas.h"
#include "Map/Datas/AnimDatas.h"
#include "Map/Traces/StaticTrace.h"
#include "Map/Traces/DynamicTrace.h"
#include "expat.h"
#include "CSV.h"
#include "Vector2.h"
#include <fstream>
#include "string.h"

/** \brief extract x and y from a str like XxY where the second x is a cross
 * \param str the str
 * \param x pointer to store the x coordinate
 * \param y pointer to store the y coordinate
 *  */
template<typename T, typename S>
void getXYFromStr(const char* str, T* x, S* y)
{
    uint32_t i;
    for(i=0; str[i] != 'x' && str[i] != 'X' && str[i] != '\0'; i++);

    if(str[i] != '\0')
    {
        *x = atoi(str);
        *y = atoi(&(str[i+1]));
    }
}

extern uint32_t XML_depth; /** <!XML depth on the current XML file*/
extern uint32_t XML_NthColumn; /** <!XML column number for static files on the current XML file*/

/** \class Map 
 * \brief basic class for decompiling Map files
 * The xml format file is like this :
 * <map>
 *	<Window numberCase="axb" tileSize="axb" title="title"/>
 *
 *	<Files>
 *	 <Static file="path" spacing="axb" tileSize="axb">
 *	  <staticTile name="name" type="type"/>
 *	 </Static>
 *	 <Dynamic file="path"> //Used for animation
 *	  <dynamicEntity name="name">
 *	   <dynamicTile name="name" pos="axb" size="axb" type="type"/>
 *	  </dynamicEntity>
 *	  <staticEntity n="n" nX="nX" name="name" pos="axb" spacing="axb" size="axb">
 *		<staticTile name="name" type="type"/>
 *	  </staticEntity>
 *	 </Dynamic>
 *	</Files>
 *
 *  <Objects name="name" numberCases = "axb" tileSize="axb" type="type">
 *   <ObjectsColumn fileID="fileID" tileID="tileID"/>
 *  </Objects>
 *
 *  <Traces>
 *   <StaticTrace name="name" shift="axb" size="axb">
 *    <Column>
 *     #If objectID == 1, the tileID is the id of the object (objectID is juste a boolean for saying if this tile is an object or not)
 *	   <Static fileID="fileID" tileID="tileID" objectID="objectID"/>
 *	   <Animation fileID="fileID" tileID="tileID" name="name"/> #name is in CSV format
 *    </Column>
 *   </StaticTraces>
 *   <DynamicTrace name="name">
 *    <DynamicTile animName="name" animeTime="time" fileID="fileID" origin="axb" position="axb" tileID="tileID"/>
 *    <StaticTile fileID="fileID" tileID="tileID" position="axb"/>
 *   </DynamicTrace>
 *  </Traces>
 * </map> 
 *
 * each fileID et tileID are represented in csv format for StaticTrace. It earns us some time process and file spaces. This couple tells us which tile it is (which file and which tile in this file)*/
class Map
{
	public:
		/** \brief Constructor of the class Map. It creates and parse a XML file. The default position of the Map is (1.0, 1.0) with the size (nbCaseX * tileSizeX, nbCaseY * tileSizeY). Remember to scale the Map after its creation
		 * \param parent the parent of the Map*/
		Map();

		/** \brief destructor of the class Map. It will destroy each traces, each texture used in this map*/
		~Map();

		/* \brief parse the file
		 * \param file the XML file*/
		void parse(const std::string& path);

		/** \brief reset the default configuration of the Map : the Rectangle3f will be :
		 * x = y = z = 0
		 * width  = nbCasesX * caseSizeX
		 * height = nbCasesY * caseSizeY
		 * depth  = 0*/
		void resetDefaultConf();

		/** \brief get the pointer function to create a static tile from name and type. This function is aimed to be overwrited.
		 * \param name the name of the tile contained on the xml file
		 * \param type the type of the tile contained on the xml file
		 * \return a pointer function to create static tiles. NULL if not correct*/
		virtual createStaticTilePtr getStaticTileFunction(const char* name, const char* type)const; 

		/** \brief Get a pointer to the static tile information (could be a structure, or something else)
		 * \param name the name of the tile contained on the xml file
		 * \param type the type of the tile contained on the xml file
		 * \return a pointer to a void*. NULL if not correct*/
		virtual void*               getStaticTileInfo(const char* name, const char* type);

		/** \brief get the pointer function to create a dynamic tile from name and type. This function is aimed to be overwrited.
		 * \param name the name of the tile contained on the xml file
		 * \return a pointer function to create dynamic tiles. NULL if not correct*/
		virtual createDynamicAnimPtr getDynamicAnimFunction(const char* name) const; 

		/** \brief Get a pointer to the dynamic animation tile information (could be a structure, or something else)
		 * \param name the name of the tile contained on the xml file
		 * \return a pointer to a void*. NULL if not correct*/
		virtual void*                getDynamicAnimTileInfo(const char* name);

		/** \brief get the pointer function to create a dynamic tile from name and type. This function is aimed to be overwrited.
		 * \param name the name of the tile contained on the xml file
		 * \return a pointer function to create dynamic tiles. NULL if not correct*/
		virtual createStaticAnimPtr getStaticAnimFunction(const char* name) const; 

		/** \brief Get a pointer to the static animation tile information (could be a structure, or something else)
		 * \param name the name of the tile contained on the xml file
		 * \return a pointer to a void*. NULL if not correct*/
		virtual void*                getStaticAnimTileInfo(const char* name);

		/** \brief set the pointer function for this ObjectDatas following its name and its type
		 * \param name the name of the tile contained on the xml file
		 * \param type the type of the tile contained on the xml file
		 * \return a pointer function to create object. NULL if not correct*/
		virtual createObjectPtr getObjectFunction(const char* name, const char* type) const;

		/** \brief Get a pointer to the object information (could be a structure, or something else)
		 * \param name the name of the tile contained on the xml file
		 * \param type the type of the tile contained on the xml file
		 * \return a pointer to a void*. NULL if not correct*/
		void*                       getObjectTileInfo(const char* name, const char* type);

		/** \brief get the tile on the coord x, y in pixels and trace coords (and not OpenGL)
		 * \param x the x component
		 * \param y the y component
		 * \return the Tile at this position. NULL if nothing*/
		Tile* getTileTraceCoords(int x, int y);

		/** \brief get the tile on the coord x, y in trace coords in a specific trace
		 * \param x the x component
		 * \param y the y component
		 * \param traceName the trace name. We will check this position on this trace only.
		 * \return the Tile at this position. NULL if nothing (trace not found or position not found)*/
		Tile* getTileTraceCoords(int x, int y, const char* traceName);

		/** \brief tell if the position x, y is outside the Map. The Map Rect is (0, 0, nbCaseX*tileSizeX, nbCaseY*tileSizeY)
		 * \param x the x coords
		 * \param y the y coords
		 * \return tells if the coords are outsize the Map or not.*/
		bool isOutside(uint32_t x, uint32_t y) const;

		/** \brief add a tile at the position x, y on the trace represented by its name
		 * \param tile the Tile to add
		 * \param x the x coords
		 * \param y the y coords
		 * \return the previous tile in the trace*/
		Tile* addTile(Tile* tile, uint32_t x, uint32_t y, const char* traceName);

		/** \brief add a tile at the position x, y on the trace represented by its id
		 * \param tile the Tile to add
		 * \param x the x coords
		 * \param y the y coords
		 * \return the previous tile in the trace*/
		Tile* addTile(Tile* tile, uint32_t x, uint32_t y, uint32_t traceID);

		Vector2i getNbCases() const;
		Vector2i getCasesSize() const;

		/** \brief Default fonction called on a new element of the XML. It will set the correct startElement function following the section name (Files, Objects or Traces)
		 * \param name the name of the section
		 * \param attrs the attributes of the section
		 *  */
		static void startElement(void* map, const char* name, const char** attrs);

		/** \brief Parse the section Files of the XML
		 * \param name the name of the section
		 * \param attrs the attributes of the section
		 *  */
		static void startElementFiles(void* map, const char* name, const char** attrs);

		/** \brief Parse the section Objects of the XML
		 * \param name the name of the section
		 * \param attrs the attributes of the section
		 *  */
		static void startElementObjects(void* map, const char* name, const char** attrs);

		/** \brief Parse the section Trace of the XML
		 * \param name the name of the section
		 * \param attrs the attributes of the section
		 *  */
		static void startElementTraces(void* map, const char* name, const char** attrs);

		/** \brief Function called after that the section is readed
		 * \param name the name of the section
		 * \param attrs the attributes of the section*/
		static void endElement(void* map, const char* name);
	private:
		//The Parser
		XML_Parser m_parser;

		//Files
		uint32_t                   m_nbFiles;
		std::vector<StaticFile*>   m_staticFiles;
		std::vector<DynamicFile*>  m_dynamicFiles;

		//Objects
		std::vector<ObjectDatas*>  m_objects;

		//Traces
		std::vector<Trace*>        m_traces;
		std::vector<StaticTrace*>  m_staticTraces;
		std::vector<DynamicTrace*> m_dynamicTraces;

		//Map datas
		uint32_t m_nbCasesX;
		uint32_t m_nbCasesY;
		uint32_t m_caseSizeX;
		uint32_t m_caseSizeY;
};
#endif
