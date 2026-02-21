#ifndef _ODBC_PLUGFACE_H_
#define _ODBC_PLUGFACE_H_
#define NULL 0
#include "pilsplug/pilsplug.h"

namespace pilsplug
{
	namespace interface
	{
		class Error : public Object
		{
		public:
			virtual Result text(const char *&result, ...) = 0;
		};

		class Statement : public Object
		{
		public:
			virtual Result execDirect(void *result, BlobReference &query, ...) = 0;
			virtual Result fetch(void *result, ...) = 0;
			virtual Result getNumber(double &result, const int &columnIndex, ...) = 0;
			virtual Result getText(BlobReference &result, const int &columnIndex, ...) = 0;
		};

		class Connection : public Object
		{
		public:
			virtual Result connect(void *result, BlobReference const &source, BlobReference const &user, BlobReference const &password, ...) = 0;
			virtual Result statement(Statement *&result, ...) = 0;
		};

		class Root : public Object
		{
		public:
			virtual Result connect(Connection *&result, BlobReference &connectionString, ...) = 0;
			virtual Result connection(Connection *&result, ...) = 0;
		};
	}
}

#endif
