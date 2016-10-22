#ifndef  ANIMDATAS_INC
#define  ANIMDATAS_INC

#include "Map/Tiles/DynamicAnim.h"
#include "Map/Tiles/StaticAnim.h"
#include <vector>
#include <string>

//info, posX, posY
typedef DynamicAnim*(*createDynamicAnimPtr)(void*, uint32_t, uint32_t);
//info, posX, posY
typedef StaticAnim*(*createStaticAnimPtr)(void*, uint32_t, uint32_t);

struct DynamicEntity
{
	public:
		DynamicEntity(createDynamicAnimPtr create);

		const createDynamicAnimPtr createDynamicAnim;
		void addTile(const char* name, const char* type);
		const std::vector<std::string>*  getNames() const;
		const std::vector<std::string>*  getTypes() const;

		void *info;
	private:
		std::vector<std::string> m_names;
		std::vector<std::string> m_types;
};

class StaticEntity
{
	public:
		StaticEntity(createStaticAnimPtr create);
		StaticAnim* createStaticAnim(uint32_t posX, uint32_t posY) const;
		const std::vector<std::string>*  getNames() const;
		const std::vector<std::string>*  getTypes() const;
		void addEntity(const char* name, const char* type);

		void* info;
	private:
		std::vector<std::string> m_names;
		std::vector<std::string> m_types;
		createStaticAnimPtr m_createStaticAnim;
};

#endif
