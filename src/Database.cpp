#include "Database.h"

Database* Database::singleton = NULL;
pthread_mutex_t Database::databaseMutex = PTHREAD_MUTEX_INITIALIZER;

void Database::initSingleton()
{
	singleton = new Database();
}

Database* Database::getSingleton()
{
	return singleton;
}

void Database::freeSingleton()
{
	delete singleton;
}

void Database::lockMutex()
{
	pthread_mutex_lock(&databaseMutex);
}

void Database::unlockMutex()
{
	pthread_mutex_unlock(&databaseMutex);
}

Database::Database()
{
	sqlite3_open("database.db", &m_sql);
}

Database::~Database()
{
	sqlite3_close(m_sql);
}

void Database::inscription(const uint8_t* mail, const uint8_t* hashPassword)
{
	char message[2048];
	char hexPassword[SHA_DIGEST_LENGTH*2];
	convertToHex(hexPassword, hashPassword, SHA_DIGEST_LENGTH);
	sprintf(message, "INSERT INTO Client (mail, password) VALUES (\'%s\', X\'%s\');", mail, hexPassword);
	printf(message);
	printf("\n");
	char* errMsg;
	int rc = sqlite3_exec(m_sql, message, Database::inscription_callback, 0, &errMsg);
	sqlite3_free(errMsg);
}

int Database::inscription_callback(void *data, int argc, char **argv, char **azColName)
{
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

bool Database::logIn(const uint8_t* mail, const uint8_t* hash)
{
	char* errMsg;
	char message[2048];
	Database_LogIn_Callback data{.password = hash, .okay = false};
	sprintf(message, "SELECT password FROM Client WHERE mail = \'%s\';", mail);
	int rc = sqlite3_exec(m_sql, message, Database::logIn_callback, &data, &errMsg);
	sqlite3_free(errMsg);

	return data.okay;
}

int Database::logIn_callback(void *data, int argc, char **argv, char **azColName)
{
	Database_LogIn_Callback* d = (Database_LogIn_Callback*)(data);
	if(argv[0] == NULL)
	{
		d->okay = false;
		return 0;
	}
	uint8_t* result            = (uint8_t*)(argv[0]);

	for(uint8_t i=0; i < SHA_DIGEST_LENGTH; i++)
	{
		if(result[i] != d->password[i])
		{
			d->okay = false;
			return 0;
		}
	}

	d->okay = true;
	return 0;
}
