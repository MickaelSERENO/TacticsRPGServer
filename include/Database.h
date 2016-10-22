#ifndef  DATABASE_INC
#define  DATABASE_INC

#include <iostream>
#include "sqlite3.h"
#include "pthread.h"
#include "stdint.h"
#include <cstring>
#include <string>
#include "stdlib.h"
#include "openssl/ssl.h"
#include "hex.h"
#include "Client.h"

struct Database_LogIn_Callback
{
	const uint8_t* password;
	bool     okay;
};

typedef std::basic_string <unsigned char> ustring;

class Database
{
	public:
		//Singleton functions
		static void      initSingleton();
		static Database* getSingleton();
		static void      freeSingleton();

		static void		 lockMutex();
		static void      unlockMutex();

		~Database();
		void inscription(const uint8_t* mail, const uint8_t* hashPassword);
		bool logIn(const uint8_t* mail, const uint8_t* hash);
		static int inscription_callback(void *data, int argc, char **argv, char **azColName);
		static int logIn_callback(void *data, int argc, char **argv, char **azColName);
	private:
		static Database* singleton;
		static pthread_mutex_t databaseMutex;
		Database();

		sqlite3* m_sql=NULL;
};

#endif
