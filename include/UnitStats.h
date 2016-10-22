#ifndef  UNITSTATS_INC
#define  UNITSTATS_INC

#include "stdint.h"
#include "Database.h"
#include <map>
#include <vector>
#include "utils.h"

enum UnitClass
{
	DIVINITY,
	DEVIL,
	HUMAN,
	NEUTRAL,
	DIVIN_BEAST,
	DEMONIAC_BEAST,
	DRAGONS
};

enum UnitType
{
	ABERRATION,
	ARDOR,
	ASIAN_DRAGON,
	BOWMAN,
	CELESTIAL,
	CHARITY,
	CHASTITY,
	CHIMERA,
	COMPASSION,
	DARK_DRAGON,
	DEMONIAC_ANIMAL,
	DEMONIAC_PLANT,
	DIVINE_PLANT,
	ELDER_DRAGON,
	ELEMENTARY,
	ELEMENTARY_DRAGON,
	ENVY,
	FAIRY,
	FIGHT_DRAGON,
	FLYING,
	GARGOYLE,
	GIANT,
	GLUTTONY,
	GOBELIN,
	GOLEM,
	GREED,
	HAMMERMAN,
	HARPY,
	HUMILITY,
	LANCEMAN,
	LUST,
	MAGIC_ANIMAL,
	MAGICIAN,
	MARTIAL,
	METALLIC_DRAGON,
	ORC,
	PARSIMONY,
	PRIDE,
	REPTILIAN,
	SANGUINARY_BEAST,
	SERENITY,
	SLOTH,
	SPECTRUM,
	SPIRIT,
	SWORDMAN,
	UNDEAD,
	UNDEAD_DRAGON,
	WHIPMAN,
	WRATH
};

struct TypeStats
{
	UnitType unitType;
	int8_t place;
};

struct UnitStats
{
	//Unit database
	UnitType unitType; /* <!The type of the Unit */

	std::string name; /* <!The name of the Unit */
	std::string description; /* <!The description of the Unit */

	int      id; /* <! The id of the Unit */
	uint32_t occupation; /* <! The occupation of a building */
	uint32_t goldCost; /* <! How many gold it costs */
	uint32_t life; /* <!How many life has the Unit*/
	uint32_t mana; /* <!How many mana has the Unit */
	uint32_t defense; /* <!The defense of the Unit */
	uint32_t speDefense; /* <!The special defense of the Unit */
	uint32_t attack; /* <!The attack of the Unit */
	uint32_t speAttack; /* <!The special attack of the Unit */
	uint32_t movableCost; /* <!How many cases I can cross (weighted by the Tile cost) */
	uint32_t accuracy; /* <!The accuracy of the Unit */
	uint32_t visibility; /* <!The visibility in the fog of the Unit */
	uint32_t level; /* <!The level where the Unit is available */
	bool     winged; /*  <!Tell if the unit can fly */
	double   nbTourStat; /* <!Statistics telling how many times the Unit can attack */
	double   nbAttackStat; /* <!Statistics telling how many I can attack per actions */
};

class UnitSubAnim
{
	public:
		UnitSubAnim(Orientation orientation);
		virtual ~UnitSubAnim();
		virtual Animation* createAnim(Updatable* parent, Material* mtl, const Texture* texture, uint32_t nbFrame) const=0;
	private:
		Orientation m_orientation;
	
};

class UnitStaticAnim : public UnitSubAnim
{
	public:
		UnitStaticAnim(Orientation orientation, int x, int y, int sizeX, int sizeY, int padX, int padY, int n, int nX);
		virtual Animation* createAnim(Updatable* parent, Material* mtl, const Texture* texture, uint32_t nbFrame) const;
	private:
		int m_x;
		int m_y;
		int m_sizeX;
		int m_sizeY;
		int m_padX;
		int m_padY;
		int m_n;
		int m_nX;
};

/*  class UnitDynamicAnim
{
	//std::vector<UnitDynamicSubAnim> subAnim;
};*/

class UnitAnim
{
	public:
		UnitAnim(int unitID, const std::string& name, const std::string& modelPath);
		virtual ~UnitAnim();
		void addAnimation(Orientation orientation, UnitSubAnim* anim, bool toDelete=true);
		Animation* createAnim(Updatable* parent, Material* mtl, const Texture* texture, uint32_t nbFrame, Orientation orientation);
		const std::string& getModelPath() const;
	private:
		std::map<Orientation, UnitSubAnim*> m_anims;
		std::map<Orientation, bool> m_delete;
		int m_unitID;
		std::string m_name;
		std::string m_modelPath; /* <!The path of the texture of the Unit */
};

class UnitTree
{
	public:
		UnitTree(UnitClass uc);
		~UnitTree();
		std::vector<const UnitStats*> getChildren(const std::string& name) const;
		std::vector<const UnitStats*> getChildren(int id) const;
		std::vector<const UnitStats*> getFirstParents() const;
	private:
		UnitClass m_uc;
		std::map<UnitType, std::vector<UnitStats>> m_data;
		std::map<int, std::vector<int>> m_childTree;
};

struct ClassDataCallback
{
	UnitClass uc;
	Database* db;
	std::map<UnitType, std::vector<UnitStats>> data;
};

struct AnimDataCallback
{
	UnitAnim* ua;
	Database* db;
	int unitID;
	const std::string* name;
};

/** \brief Class which provides functions to access some part of the Data
  * \class UnitDatabase*/
class UnitDatabase
{
	public:
		/** \brief init the singleton
		 * \param db The Database to use*/
		static void initSingleton(Database* db);

		/** \brief get the singleton
		 * \return The UnitDatabase*/
		static UnitDatabase* getSingleton();

		//Mapping functions

		/** \brief get the string for an UnitClass
		 * \return the string associated with the UnitClass*/
		static std::string getClassName(UnitClass uc);

		/** \brief convert a UnitType to a std::string
		 * \return the string associated with the UnitType*/
		static std::string getUnitTypeString(UnitType ut);

		/** \brief convert a std::string to a UnitType
		 * \return the UnitType associated with the std::string*/
		static UnitType getUnitType(const std::string& ut);

		//Callback functions

		static int getUnitDataCallback(void* data, int nbColumn, char** argv, char** columnName);

		static int getClassDatabaseCallback(void* data, int nbColumn, char** argv, char** columnName);

		static int getChildrenCallback(void* data, int nbColumn, char** argv, char** columnName);

		static int getSubStaticAnimCallback(void* data, int nbColumn, char** argv, char** columnName);

		~UnitDatabase();

		/** \brief get the information of a whole UnitClass.
		 * \param uc The UnitClass
		 * \return an array of all the UnitStats of this UnitClass mapped by UnitType.*/
		std::map<UnitType, std::vector<UnitStats>> getClassDatabase(UnitClass uc);

		/** \brief get the id of the children of one unit represented by its id
		 * \param id The id of the Unit parent
		 * \return An array of the children of this Unit*/
		std::vector<int> getChildrenID(int id);
	private:
		static UnitDatabase* m_singleton;
		UnitDatabase(Database* db);
		Database* m_db=NULL;
};

#endif
