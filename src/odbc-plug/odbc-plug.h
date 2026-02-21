#include "odbc-plugface.h"

#ifndef _PILS_ODBC_PLUG_H_
#define _PILS_ODBC_PLUG_H_

#include <string>
#if defined(_MSC_VER)
#include <windows.h>
#endif
#include <sql.h>
#include <sqlext.h>
#undef interface

namespace pilsplug
{
	class Root : public interface::Root
	{
	public:
		Root(SQLHENV sql_environment_handle);
		~Root();
		virtual Result connect(interface::Connection *&result, BlobReference &connectionString, ...);
		virtual Result connection(interface::Connection *&result, ...);
		SQLHENV sql_env;
	};

	class Connection : public interface::Connection
	{
	public:
		Connection(Root &root, SQLHDBC dbc);
		~Connection();
		virtual Result connect(void *result, BlobReference const &source, BlobReference const &user, BlobReference const &password, ...);
		virtual Result statement(interface::Statement *&result, ...);
		Root &root;
		SQLHDBC dbc;
	};

	class Statement : public interface::Statement
	{
	public:
		Statement(Connection &connection, SQLHSTMT stmt);
		~Statement();
		virtual Result execDirect(void *result, BlobReference &query, ...);
		virtual Result fetch(void *result, ...);
		virtual Result getNumber(double &result, const int &columnIndex, ...);
		virtual Result getText(BlobReference &result, const int &columnIndex, ...);
		Connection &connection;
		std::string text;
		SQLHSTMT stmt;
	};

	class Error : public interface::Error
	{
	public:
		Error(SQLSMALLINT handletype, SQLHANDLE handle);
		virtual Result text(const char *&result, ...) {result = &message[0]; return NULL;}
	private:
		std::string message;
	};
}

#endif
