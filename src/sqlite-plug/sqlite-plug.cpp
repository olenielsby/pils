#include "sqlite-plug.h"

Database::Database(sqlite3 *db) : db(db) {}

Database::~Database()
{
	sqlite3_close(db);
}

pilsplug::Result Database::query(pilsplug::interface::Query *&result, const char *sql, ...) const
{
	sqlite3_stmt *stmt;
	int code = sqlite3_prepare(db, sql, -1, &stmt, NULL);
	if (code != SQLITE_OK) return new Error(db);
	result = new ::Query(*this, stmt);
	return NULL;
}

Query::Query(const Database &owner, sqlite3_stmt *stmt)
	: owner(&owner), stmt(stmt)
{
	owner.acquire();
}

Query::~Query()
{
	sqlite3_finalize(stmt);
	owner->release();
}

pilsplug::Result Query::columnCount(int &result, ...)
{
	result = sqlite3_column_count(stmt);
	return NULL;
}

pilsplug::Result Query::columnString(const char *&result, const int &columnIndex, ...)
{
	result = (const char *)sqlite3_column_text(stmt, columnIndex-1);
	return NULL;
}

pilsplug::Result Query::columnBlob(pilsplug::BlobReference &result, const int &columnIndex, ...)
{
	result.data = sqlite3_column_blob(stmt, columnIndex-1);
	result.count = sqlite3_column_bytes(stmt, columnIndex-1);
	return NULL;
}

pilsplug::Result Query::columnType(int &result, const int &columnIndex, ...)
{
	result = sqlite3_column_type(stmt, columnIndex-1);
	return NULL;
}

pilsplug::Result Query::columnInt(int &result, const int &columnIndex, ...)
{
	result = sqlite3_column_int(stmt, columnIndex-1);
	return NULL;
}

pilsplug::Result Query::columnDouble(double &result, const int &columnIndex, ...)
{
	result = sqlite3_column_double(stmt, columnIndex-1);
	return NULL;
}

pilsplug::Result Query::step(int &result, ...)
{
	result = sqlite3_step(stmt) == SQLITE_ROW;
	return NULL;
}

pilsplug::Result Query::reset(void *result, ...)
{
	if (sqlite3_reset(stmt) != SQLITE_OK)
		return new Error(owner->db);
	else return NULL;
}

pilsplug::Result Query::bindString(void *result, const int &index, const char *value, ...)
{
	if (sqlite3_bind_text(stmt, index, value, -1, SQLITE_TRANSIENT) != SQLITE_OK)
		return new Error(owner->db);
	else return NULL;
}

pilsplug::Result Query::bindInt(void *result, const int &index, const int &value, ...)
{
	if (sqlite3_bind_int(stmt, index, value) != SQLITE_OK)
		return new Error(owner->db);
	else return NULL;
}

pilsplug::Result Query::bindDouble(void *result, const int &index, const double &value, ...)
{
	if (sqlite3_bind_double(stmt, index, value) != SQLITE_OK)
		return new Error(owner->db);
	else return NULL;
}

pilsplug::Result Query::bindBlob(void *result, const int &index, const pilsplug::BlobReference &value, ...)
{
	if (sqlite3_bind_blob(stmt, index, value.data, value.count, SQLITE_TRANSIENT) != SQLITE_OK)
		return new Error(owner->db);
	else return NULL;
}

pilsplug::Result Query::clearBindings(void *result, ...)
{
	if (sqlite3_clear_bindings(stmt) != SQLITE_OK)
		return new Error(owner->db);
	else return NULL;
}
