#include "hex.h"

const char HEX[16]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

void convertToHex(char* dest, const uint8_t* src, uint32_t size)
{
	for(uint32_t i=0; i < size; i++)
	{
		uint8_t v   = src[i];
		dest[2*i]   = HEX[v >> 4]; 
		dest[2*i+1] = HEX[(uint8_t)(v << 4) >> 4]; 
	}
}
