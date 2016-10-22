#ifndef  HEX_INC
#define  HEX_INC

#include "stdint.h"

extern const char HEX[16];
void convertToHex(char* dest, const uint8_t* src, uint32_t size);

#endif
