#ifndef  CSV_INC
#define  CSV_INC

#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include <string>
#include <vector>
#include <iostream>

template <typename T>
class CSVParser
{
	public:
		CSVParser();
		CSVParser(const char* string);
		~CSVParser();

		/** \brief parse the string "string". After each number, this function calls itself, while the string isn't read entirely.
		 * \param string the string to parse
		 * \return return if the parser has correctly parsed the file or not*/
		bool parse(const char* string);

		/** \brief get the value of the Parser
		 * \return the value array of the parser. Use getLen to get the value array's length*/
		const std::vector<T>* getValues() const;
	protected:
		/** \brief which action have we to do with the value which has just got parsed ?
		 * \param value the value parsed
		 * \return return if the action done on this value is a success or not*/
		virtual bool onValue(const char* value)=0;
		std::vector<T> m_values;
};

class IntCSVParser : public CSVParser<int32_t>
{
	private:
		virtual bool onValue(const char* value);
};

class StrCSVParser : public CSVParser<std::string>
{
	private:
		virtual bool onValue(const char* value);
};

template <typename T>
CSVParser<T>::CSVParser()
{
}

template <typename T>
CSVParser<T>::CSVParser(const char* string)
{
	parse(string);
}

template <typename T>
CSVParser<T>::~CSVParser()
{
}

template <typename T>
bool CSVParser<T>::parse(const char* string)
{
	uint32_t stringIndice=0;
	while(string[stringIndice] != '\n' && string[stringIndice] != '\0')	
	{
		std::string value="";

		for(; string[stringIndice] != ',' && string[stringIndice] != ';' && string[stringIndice] != '\0' && string[stringIndice] != '\n'; stringIndice++)
			value += string[stringIndice];
		if(!onValue(value.c_str()))
			return false;
		if(string[stringIndice] != '\0' && string[stringIndice] != '\n')
			stringIndice++;
	}
	return true;
}

template <typename T>
const std::vector<T>* CSVParser<T>::getValues() const
{
	return &m_values;
}
#endif
