#include "Map/MapFiles.h"

StaticFile::StaticFile()
{
}

StaticFile::~StaticFile()
{
	for(uint32_t i=0; i < m_tileDatas.size(); i++)
		if(m_tileDatas[i])
			delete m_tileDatas[i];
}

void StaticFile::addStaticDatas(StaticDatas* tileDatas)
{
	m_tileDatas.push_back(tileDatas);
}

Tile* StaticFile::createTile(uint32_t tileID, bool def)
{
	if(tileID >= m_tileDatas.size())
		return NULL;
	if(!m_tileDatas[tileID])
		return NULL;

    //Get how many tiles we have in a row.
    //True value : (tWidth - tileSizeX + tileSizeX + spacingX -1) / (tileSizeX + spacingX) + 1 
    if(!def)
	{
		if(m_tileDatas[tileID]->createStaticTile)
		{
			Tile* tile = m_tileDatas[tileID]->createStaticTile(m_tileDatas[tileID]->info);
			return tile;
		}
		else
			return NULL;
	}
    Tile* tile = new DefaultTile(NULL);
	return tile;
}

DynamicFile::DynamicFile()
{}

DynamicFile::~DynamicFile()
{
    for(std::map<std::string, DynamicEntity*>::iterator it=m_dynamicEntities.begin(); it != m_dynamicEntities.end(); it++)
        if(it->second)
            delete it->second;

    for(std::map<std::string, StaticEntity*>::iterator it=m_staticEntities.begin(); it != m_staticEntities.end(); it++)
        if(it->second)
            delete it->second;
}

void DynamicFile::addDynamicEntity(const std::string& key, DynamicEntity* entity)
{
    m_dynamicEntities.insert(std::pair<std::string, DynamicEntity*>(key, entity));
}

void DynamicFile::addStaticEntity(const std::string& key, StaticEntity* entity)
{
    m_staticEntities.insert(std::pair<std::string, StaticEntity*>(key, entity));
}

DynamicEntity* DynamicFile::getDynamicEntity(const std::string& name)
{
    for(std::map<std::string, DynamicEntity*>::iterator it=m_dynamicEntities.begin(); it != m_dynamicEntities.end(); it++)
        if(it->first == name)
            return it->second;
	return NULL;
}

StaticEntity* DynamicFile::getStaticEntity(const std::string& name)
{
    for(std::map<std::string, StaticEntity*>::iterator it=m_staticEntities.begin(); it != m_staticEntities.end(); it++)
        if(it->first == name)
            return it->second;
	return NULL;
}

DynamicEntity* DynamicFile::getLastDynamicEntity()
{
    return (m_dynamicEntities.rbegin()->second);
}

StaticEntity*  DynamicFile::getLastStaticEntity()
{
    return (m_staticEntities.rbegin()->second);
}
