#ifndef _SQLITE_PLUGFACE_H_
#define _SQLITE_PLUGFACE_H_
#define NULL 0
#include "pilsplug/pilsplug.h"

namespace pilsplug
{
	namespace interface
	{
		class Error : public Object
		{
		public:
			virtual Error *text(const char *&result, ...) = 0;
		};

		class Query : public Object
		{
		public:
			virtual Error *step(int &result, ...) = 0;
			virtual Error *columnCount(int &result, ...) = 0;
			virtual Error *columnType(int &result, const int &columnIndex, ...) = 0;
			virtual Error *columnString(const char *&result, const int &columnIndex, ...) = 0;
			virtual Error *columnInt(int &result, const int &columnIndex, ...) = 0;
			virtual Error *columnDouble(double &result, const int &columnIndex, ...) = 0;
			virtual Error *columnBlob(BlobReference &result, const int &columnIndex, ...) = 0;
			virtual Error *reset(void *result, ...) = 0;
			virtual Error *bindString(void *result, const int &columnIndex, const char *value, ...) = 0;
			virtual Error *bindInt(void *result, const int &columnIndex, const int &value, ...) = 0;
			virtual Error *bindDouble(void *result, const int &columnIndex, const double &value, ...) = 0;
			virtual Error *bindBlob(void *result, const int &columnIndex, const BlobReference &value, ...) = 0;
			virtual Error *clearBindings(void *result, ...) = 0;
		};

		class Database : public Object
		{
		public:
			virtual Error *query(Query *&result, const char *sql, ...) const = 0;
		};

		class Root : public Object
		{
		public:
			virtual Error *database(Database *&result, const char *filename, ...) = 0;
		};
	}
}

#endif
