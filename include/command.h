#ifndef  COMMAND_INC
#define  COMMAND_INC

#define GET_INSCRIPTION 0x01 //The inscription
#define GET_CLASS       0x02 //The class to play
#define GET_TYPE        0x03 //The type of the class to play
#define GET_ACTION      0x04 //The action of a unit
	#define ACTION_MOVE   0x01 //The motion
	#define ACTION_ATTACK 0x02
#define GET_END_TURN    0x05
#define GET_DICEVALUE   0x06
#define GET_CREATE_UNIT 0x07
#define GET_FETCH_ROOM  0x08
#define GET_LOG_IN      0x09

#define SEND_LOG_SUCCESS 0x0a
#define SEND_WAIT_ROOM   0x0b
#define SEND_START       0x0c

#endif
