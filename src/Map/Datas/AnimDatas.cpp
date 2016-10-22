#include "Map/Datas/AnimDatas.h"

DynamicEntity::DynamicEntity(createDynamicAnimPtr create) : createDynamicAnim(create), info(NULL)
{
}

void DynamicEntity::addTile(const char* name, const char* type)
{
	m_names.push_back(name);
	m_types.push_back(type);
}

const std::vector<std::string>*  DynamicEntity::getNames() const
{
	return &m_names;
}

const std::vector<std::string>*  DynamicEntity::getTypes() const
{
	return &m_types;
}

StaticEntity::StaticEntity(createStaticAnimPtr create) : info(NULL), m_createStaticAnim(create)
{
}

StaticAnim* StaticEntity::createStaticAnim(uint32_t posX, uint32_t posY) const
{
	if(m_createStaticAnim)
		return m_createStaticAnim(info, posX, posY);
	return NULL;
}

const std::vector<std::string>*  StaticEntity::getNames() const
{
	return &m_names;
}

const std::vector<std::string>*  StaticEntity::getTypes() const
{
	return &m_types;
}


void StaticEntity::addEntity(const char* name, const char* type)
{
	m_names.push_back(name);
	m_types.push_back(type);
}
