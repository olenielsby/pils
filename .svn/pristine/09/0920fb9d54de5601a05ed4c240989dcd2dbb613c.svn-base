#ifndef _MYSQL_PLUGFACE_H_
#define _MYSQL_PLUGFACE_H_
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

		class Row : public Object
		{
		public:
			virtual Error *count(int &result, ...) = 0;
			virtual Error *item(BlobReference &result, const int &index, ...) = 0;
		};

		class ResultSet : public Object
		{
		public:
			virtual Error *eof(void *result, ...) = 0;
			virtual Error *fetch_row(Row *&result, ...) = 0;
		};

		class Statement : public Object
		{
		public:
			virtual Error *parameters(int &result, ...) = 0;
			virtual Error *run(void *result, ...) = 0;
			virtual Error *bind_int(void *result, const int &value, ...) = 0;
			virtual Error *bind_double(void *result, const double &value, ...) = 0;
			virtual Error *bind_blob(void *result, const BlobReference &value, ...) = 0;
		};

		class Connection : public Object
		{
		public:
			virtual Error *get_server_version(int &result, ...) = 0;
			virtual Error *query(void *result, const BlobReference &query, ...) = 0;
			virtual Error *use_result(ResultSet *&result, ...) = 0;
			virtual Error *statement(Statement *&result, const BlobReference &query, ...) = 0;
//			virtual Error *affected_rows(double &result, ...) = 0;
//			virtual Error *autocommit(void *result, const int &mode, ...) = 0;
//			virtual Error *commit(void *, ...) = 0;
//			virtual Error *field_count(int &result, ...) = 0;
//			virtual Error *insert_id(double &result, ...) = 0;
//			virtual Error *more_results(int &result, ...) = 0;
//			virtual Error *next_result(ResultSet *&result, ...) = 0;
//			virtual Error *rollback(void *result, ...) = 0;
//			virtual Error *select_db(void *result, const char *db, ...) = 0;
//			virtual Error *select_db(void *result, ...) = 0;
//			virtual Error *store_result(ResultSet *&result, ...) = 0;
//			virtual Error *ssl_set(void *result, const char *key, const char *cert, const char *ca, const char *capath, const char *cipher, ...) = 0;
		};

		class Host : public Object
		{
		public:
			virtual Error *connect(Connection *&result, const char *user, const char *passwd, const char *db, ...) = 0;
		};

		class Root : public Object
		{
		public:
			virtual Error *hostport(Host *&result, const char *host, const int &port, ...) = 0;
			virtual Error *host(Host *&result, const char *host, ...) = 0;
		};
	}
}

#endif
