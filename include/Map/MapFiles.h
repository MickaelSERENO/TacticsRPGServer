#ifndef  MAPFILES_INC
#define  MAPFILES_INC

#include <map>
#include "Map/Datas/StaticDatas.h"
#include "Map/Datas/AnimDatas.h"
#include "Map/Tiles/DefaultTile.h"

/** \class StaticFile
 * \brief contain information about a static file.*/
class StaticFile
{
	public:
		/** \brief Default constructor for a StaticFile*/
		StaticFile();
		~StaticFile();

		/** \brief Add a StaticDatas on this file. Has to be allocated dynamically, and doesn't have to be destroy by the user (the object will do it itself)
		 * \param tileDatas the StaticDatas to add*/
		void   addStaticDatas(StaticDatas* tileDatas);

		/** \brief Create a tile placed at the place tileID. If you want to create a default tile, use def=true
		 * \param parent the parent of the new Tile*
		 * \param tileID the position of the tile on the file.
		 * \param def put def to true if you want to create a DefaultTile
		 * \return the Tile created. NULL if can't be created*/
		Tile*  createTile(uint32_t tileID, bool def);
	private:
		std::vector<StaticDatas*> m_tileDatas;
};

/** \class DynamicFile*/
class DynamicFile
{
	public:
		/** \brief Constructor for DynamicFile*/
		DynamicFile();
		~DynamicFile();

		/** \brief add a DynamicEntity to this file.
		 * \param key the name of the entity
		 * \param DynamicEntity the DynamicEntity itself*/
		void addDynamicEntity(const std::string& key, DynamicEntity* entity);

		/** \brief add a StaticEntity to this file.
		 * \param key the name of the entity
		 * \param StaticEntity the StaticEntity itself*/
		void addStaticEntity(const std::string& key, StaticEntity* entity);

		/** \brief get the last DynamicEntity added to this file
		 * \return The last DynamicEntity added*/
		DynamicEntity* getLastDynamicEntity();

		/** \brief get the last StaticEntity added to this file
		 * \return The last StaticEntity added*/
		StaticEntity* getLastStaticEntity();

		/** \brief get the DynamicEntity bound to the key name
		 * \param name the name of the animation
		 * \return the DynamicEntity which corresponds to the name. NULL if not found*/
		DynamicEntity* getDynamicEntity(const std::string& name);

		/** \brief get the StaticEntity bound to the key name
		 * \param name the name of the animation
		 * \return the StaticEntity which corresponds to the name. NULL if not found*/
		StaticEntity* getStaticEntity(const std::string& name);
	private:
		std::multimap<std::string, DynamicEntity*> m_dynamicEntities;
		std::multimap<std::string, StaticEntity*>  m_staticEntities;
};

#endif
