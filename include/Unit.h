#ifndef  UNIT_INC
#define  UNIT_INC

#include "stdlib.h"
#include "stdint.h"

/** \class Unit
 *  \brief The Unit representation of the client*/
class Unit
{
	public:
		/** \brief The constructor.
		 * \param message the message send by the client
		 * The message representation is : uc(32 bits) ut(32 bits) pv(32 bits) mp(32bits) posX(32 bits) posY(32 bits) unitID(32 bits) level(8 bits)*/
		Unit(uint8_t* message);
	private:
		int      m_uc;
		int      m_ut;
		uint32_t m_posX;
		uint32_t m_posY;
		uint32_t m_unitID;
		uint8_t  m_level;
};

#endif
