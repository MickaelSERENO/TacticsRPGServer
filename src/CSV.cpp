#include "CSV.h"

bool IntCSVParser::onValue(const char* string)
{
	int32_t  value         = 0;
	int8_t   signe         = 1;
	int32_t  exposant      = 1;
	int8_t  numberSize    = -1;
	uint32_t stringIndice;

	//Get only a number
	for(stringIndice=0; string[stringIndice] != '\0' && string[stringIndice] != '\n'; stringIndice++)
	{
		//Set the signe if needed
		if(string[stringIndice] == '-' && numberSize == -1)
			signe *= -1;

		//Don't read spaces
		else if(string[stringIndice] == ' ' && numberSize == -1)
			continue;

		//If the character is a number
		else if(string[stringIndice] - '0' >= 0 && string[stringIndice] - '0' <= 9)
		{
			value += exposant * (string[stringIndice] - '0');
			exposant *= 10;
			numberSize++;
		}

		else if(string[stringIndice] == ' ')
			continue;

		else
		{
			std::cerr << "Error while parsing CSV " << string << " Abort.\n";
			return false;
		}
	}

	if(numberSize == -1)
	{
		perror("Error while parsing. Abort \n");
		return false;
	}
	
	//Replace the number correctly (in the first for loop, the number is mirrored)
	int32_t stringValue=0;
	int32_t i;
	for(i=0; i <= numberSize; i++)
	{
		stringValue *=10;
		stringValue += value % 10;
		value /=10;
	}

	stringValue *= signe;

	//Set our values array
	m_values.push_back(stringValue);
	return true;
}

bool StrCSVParser::onValue(const char* value)
{
    m_values.push_back(std::string(value));
	return true;
}
