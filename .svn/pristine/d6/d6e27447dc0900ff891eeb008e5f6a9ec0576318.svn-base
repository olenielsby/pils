#include "sqlite-plugface.h"
#include "sqlite3.h"
#include <string>

class Error : public pilsplug::interface::Error
{
public:
	Error(sqlite3 *db) : message(sqlite3_errmsg(db)) {}
	virtual pilsplug::Result text(const char *&result, ...) {result = message.data(); return NULL;}
private:
	std::string message;
};

class Database;

class Query : public pilsplug::interface::Query
{
public:
	Query(const Database &owner, sqlite3_stmt *stmt);
	~Query();
	virtual pilsplug::Result columnType(int &result, const int &columnIndex, ...);
	virtual pilsplug::Result columnCount(int &result, ...);
	virtual pilsplug::Result columnString(const char *&result, const int &columnIndex, ...);
	virtual pilsplug::Result columnInt(int &result, const int &columnIndex, ...);
	virtual pilsplug::Result columnDouble(double &result, const int &columnIndex, ...);
	virtual pilsplug::Result columnBlob(pilsplug::BlobReference &result, const int &columnIndex, ...);
	virtual pilsplug::Result step(int &result, ...);
	virtual pilsplug::Result reset(void *result, ...);
	virtual pilsplug::Result bindString(void *result, const int &index, const char *value, ...);
	virtual pilsplug::Result bindInt(void *result, const int &index, const int &value, ...);
	virtual pilsplug::Result bindDouble(void *result, const int &idex, const double &value, ...);
	virtual pilsplug::Result bindBlob(void *result, const int &index, const pilsplug::BlobReference &value, ...);
	virtual pilsplug::Result clearBindings(void *result, ...);
private:
	sqlite3_stmt *const stmt;
	const Database *const owner;
};

class Database : public pilsplug::interface::Database
{
public:
	Database(sqlite3 *db);
	~Database();
	virtual pilsplug::Result query(pilsplug::interface::Query *&result, const char *sql, ...) const;
	sqlite3 *db;
};
