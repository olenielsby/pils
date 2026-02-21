#include <string>
#include <vector>
#include "mysql-plugface.h"
#if defined(_MSC_VER)
#include <config-win.h>
#endif
#include <mysql.h>

#undef interface

namespace pilsplug
{
	class Root : public interface::Root
	{
	public:
		Root();
		~Root();
		Result hostport(interface::Host *&result, const char *host, const int &port,  ...);
		Result host(interface::Host *&result, const char *host,  ...);
	};

	class Connection : public interface::Connection
	{
	public:
		Connection();
		~Connection();
		virtual Result get_server_version(int &result, ...);
		virtual Result query(void *result, const BlobReference &query, ...);
		virtual Result use_result(interface::ResultSet *&result, ...);
		virtual Result statement(interface::Statement *&result, const BlobReference &query, ...);
		MYSQL mysql;
	};

	class ResultSet : public interface::ResultSet
	{
	public:
		ResultSet(Connection &connection, MYSQL_RES *resultSet);
		~ResultSet();
		virtual Result eof(void *result, ...);
		virtual Result fetch_row(interface::Row *&result, ...);
	private:
		friend class Row;
		friend class Field;
		MYSQL_RES *const resultSet;
		MYSQL_FIELD *const fields;
		int const fieldCount;
		Connection *const connection;
	};

	class Row : public interface::Row
	{
	public:
		Row(MYSQL_ROW row, const ResultSet &resultSet);
		~Row();
		virtual Result count(int &result, ...);
		virtual Result item(BlobReference &result, const int &index, ...);
	private:
		MYSQL_ROW const row;
		unsigned long *const lengths;
		const ResultSet *const resultSet;
	};

	class Error : public interface::Error
	{
	public:
		Error(MYSQL *mysql) : message(mysql_error(mysql)) {}
		Error(MYSQL_STMT *stmt) : message(mysql_stmt_error(stmt)) {}
		Error(const char *message) : message(message) {}
		virtual Result text(const char *&result, ...) {result = &message[0]; return NULL;}
	private:
		std::string const message;
	};

	class Statement : public interface::Statement
	{
	public:
		Statement(MYSQL_STMT *stmt, Connection &owner);
		~Statement();
		virtual Result parameters(int &result, ...);
		virtual Result run(void *result, ...);
		virtual Result bind_int(void *result, const int &value, ...);
		virtual Result bind_double(void *result, const double &value, ...);
		virtual Result bind_blob(void *result, const BlobReference &value, ...);
	private:
		size_t boundCount;
		class Bound
		{
		public:
			virtual ~Bound(){}
		};
		std::vector<MYSQL_BIND> bindVector;
		std::vector<Bound *>boundVector;
		Connection &owner;
		MYSQL_STMT *const stmt;
	};

	class Host : public interface::Host
	{
	public:
		Host(const char *host, int port) : host(host), port(port) {}
		virtual Result connect(interface::Connection *&result, const char *user, const char *passwd, const char *db, ...);
	private:
		std::string const host;
		int const port;
	};
}
