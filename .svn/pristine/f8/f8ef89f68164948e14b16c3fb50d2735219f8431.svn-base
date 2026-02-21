#include "mysql-plug.h"
#include "pilsplug/pilsplug_component.h"

namespace pilsplug
{
	Connection::Connection()
	{
		mysql_init(&mysql);
	}

	Connection::~Connection()
	{
		mysql_close(&mysql);
	}

	ResultSet::ResultSet(Connection &connection, MYSQL_RES *resultSet)
		: connection(&connection), resultSet(resultSet), fields(mysql_fetch_fields(resultSet)), fieldCount(mysql_num_fields(resultSet))
	{
		connection.acquire();
	}

	ResultSet::~ResultSet()
	{
		mysql_free_result(resultSet);
		connection->release();
	}

	Result Host::connect(interface::Connection *&result, const char *user, const char *passwd, const char *db, ...)
	{
		Connection *connection = new Connection();
		result = connection;
		if (mysql_real_connect(&connection->mysql, &host[0], user, passwd, db, port, NULL, 0))
		{
			mysql_set_character_set(&connection->mysql, "utf8");
			return NULL;
		}
		else return new Error(&connection->mysql);
	}

	Result Connection::get_server_version(int &result, ...)
	{
		result = (int)mysql_get_server_version(&mysql);
		return NULL;
	}

	Result Connection::query(void *result, const BlobReference &query, ...)
	{
		if (mysql_real_query(&mysql, (const char *)query.data, query.count)== 0)
			return NULL;
		else return new Error(&mysql);
	}

	Result Connection::use_result(interface::ResultSet *&result, ...)
	{
		MYSQL_RES *resultSet = mysql_use_result(&mysql);
		if (resultSet)
		{
			result = new ResultSet(*this, resultSet);
			return NULL;
		}
		else
		{
			result = NULL;
			return new Error(&mysql);
		}
	}

	Result Connection::statement(pilsplug::interface::Statement *&result, const BlobReference &text, ...)
	{
		MYSQL_STMT *stmt = mysql_stmt_init(&mysql);
		if (mysql_stmt_prepare(stmt, (const char*)text.data, text.count) == 0)
		{
			result = new Statement(stmt, *this);
			return NULL;
		}
		else
		{
			Error *error = new Error(stmt);
			mysql_stmt_close(stmt);
			result = NULL;
			return error;
		}
	}

	Statement::Statement(MYSQL_STMT *stmt, Connection &owner)
		: stmt(stmt), owner(owner), bindVector(mysql_stmt_param_count(stmt)), boundVector(mysql_stmt_param_count(stmt)), boundCount(0)
	{
		owner.acquire();
		if (size_t count = bindVector.size())
		{
			memset(&bindVector[0], 0, sizeof(MYSQL_BIND) * count);
			memset(&boundVector[0], 0, sizeof(Bound *) * count);
		}
	}

	Statement::~Statement()
	{
		for (size_t i = 0; i < boundVector.size(); i++)
			delete boundVector[i];
		mysql_stmt_close(stmt);
		owner.release();
	}

	Result Statement::parameters(int &result, ...)
	{
		result = bindVector.size();
		return NULL;
	}

	Result Statement::bind_int(void *result, const int &value, ...)
	{
		class BoundInt : public Bound
		{
		public:
			BoundInt(const int value) : value(value) {}
			int value;
		};
		if (boundCount < boundVector.size())
		{
			MYSQL_BIND &bind = bindVector[boundCount];
			BoundInt *bound = new BoundInt(value);
			boundVector[boundCount++] = bound;
			bind.buffer = &bound->value;
			bind.buffer_type = MYSQL_TYPE_LONG;
			bind.is_unsigned = false;
		}
		return NULL;
	}

	Result Statement::bind_double(void *result, const double &value, ...)
	{
		class BoundDouble : public Bound
		{
		public:
			BoundDouble(const double value) : value(value) {}
			double value;
		};
		if (boundCount < boundVector.size())
		{
			MYSQL_BIND &bind = bindVector[boundCount];
			BoundDouble *bound = new BoundDouble(value);
			boundVector[boundCount++] = bound;
			bind.buffer = &bound->value;
			bind.buffer_type = MYSQL_TYPE_DOUBLE;
		}
		return NULL;
	}

	Result Statement::bind_blob(void *result, const BlobReference &value, ...)
	{
		class BoundBlob : public Bound
		{
		public:
			BoundBlob(const BlobReference &value) : value((const char *)value.data, value.count) {}
			std::string value;
		};
		if (boundCount < boundVector.size())
		{
			MYSQL_BIND &bind = bindVector[boundCount];
			BoundBlob *bound = new BoundBlob(value);
			boundVector[boundCount++] = bound;
			bind.buffer_type = MYSQL_TYPE_BLOB;
			if (bind.buffer_length = bound->value.size())
				bind.buffer = &bound->value[0];
			bind.length = &bind.buffer_length;
		}
		return NULL;
	}

	Result Statement::run(void *result, ...)
	{
		if (boundCount != bindVector.size())
			return new Error("Mysql-plug: Not all parameters bound");
		if (boundCount && mysql_stmt_bind_param(stmt, &bindVector[0]))
			return new Error(stmt);
		if (mysql_stmt_execute(stmt))
			return new Error(stmt);
		return NULL;
	}

	Result ResultSet::eof(void *result, ...)
	{
		if(mysql_eof(resultSet))
			return NULL;
		else return new Error(&connection->mysql);
	}

	Result ResultSet::fetch_row(interface::Row *&result, ...)
	{
		MYSQL_ROW row = mysql_fetch_row(resultSet);
		if (row)
		{
			result = new Row(row, *this);
			return NULL;
		}
		result = NULL;
		return new Error(&connection->mysql);
	}

	Row::Row(MYSQL_ROW row, const ResultSet &resultSet)
		: row(row), resultSet(&resultSet), lengths(mysql_fetch_lengths(resultSet.resultSet))
	{
		resultSet.acquire();
	}

	Row::~Row()
	{
		resultSet->release();
	}

	Result Row::count(int &result, ...)
	{
		result = resultSet->fieldCount;
		return NULL;
	}

	Result Row::item(BlobReference &result, const int &index, ...)
	{
		if (index > 0 && index <= resultSet->fieldCount)
		{
			result.count = lengths[index-1];;
			result.data = row[index-1];
		}
		else
		{
			result.count = 0;
			result.data = NULL;
		}
		return NULL;
	}

	Root::Root()
	{
		mysql_library_init(0, NULL, NULL);
	}

	Root::~Root()
	{
		mysql_library_end();
	}

	interface::Object *Plug::root() const
	{
		return new Root();
	}

	Result Root::hostport(interface::Host *&result, const char *hostname, const int &port,  ...)
	{
		result = new Host(hostname, port);
		return NULL;
	}

	Result Root::host(interface::Host *&result, const char *hostname,  ...)
	{
		result = new Host(hostname, MYSQL_PORT);
		return NULL;
	}
}
