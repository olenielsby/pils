#include "odbc-plug.h"
#include "pilsplug/pilsplug_component.h"

namespace pilsplug {

	Error::Error(SQLSMALLINT handletype, SQLHANDLE handle)
	{
		SQLCHAR message[SQL_MAX_MESSAGE_LENGTH + 1];
		SQLSMALLINT size = 0;
		for (int i = 1; SQL_SUCCEEDED(SQLGetDiagField(handletype, handle, i, SQL_DIAG_MESSAGE_TEXT, message, sizeof(message), &size)); i++)
		{
			message[size++] = '\n';
			this->message.append((const char *)message, size);
		}
	}

	interface::Object *Plug::root() const
	{
		SQLHENV sql_env;
		if (SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sql_env)))
		{
			if (SQL_SUCCEEDED(SQLSetEnvAttr(sql_env, SQL_ATTR_ODBC_VERSION,(void*)SQL_OV_ODBC3,0)))
			{
				return new Root(sql_env);
			}
			SQLFreeHandle(SQL_HANDLE_ENV, sql_env);
		}
		return NULL;
	}

	Root::Root(SQLHENV sql_env)
		: sql_env(sql_env)
	{}

	Root::~Root()
	{
		SQLFreeHandle(SQL_HANDLE_ENV, sql_env);
	}

	Result Root::connect(interface::Connection *&result, BlobReference &connectionString, ...)
	{
		result = NULL;
		SQLHDBC dbc;
		if(!SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_DBC, sql_env, &dbc)))
		{
			return new Error(SQL_HANDLE_ENV, sql_env);
		}
		SQLCHAR x[1024];
		SQLSMALLINT xLength = 0;
		if(!SQL_SUCCEEDED(SQLDriverConnect(dbc, GetDesktopWindow(), (SQLCHAR *)connectionString.data, connectionString.count, x, 1024, &xLength, SQL_DRIVER_COMPLETE)))
		{
			Error *error = new Error(SQL_HANDLE_DBC, dbc);
			SQLFreeHandle(SQL_HANDLE_DBC, dbc);
			return error;
		}
		result = new Connection(*this, dbc);
		return NULL;
	}

	Result Root::connection(interface::Connection *&result, ...)
	{
		SQLHDBC dbc;
		if(SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_DBC, sql_env, &dbc)))
		{
			result = new Connection(*this, dbc);
			return NULL;
		}
		result = NULL;
		return new Error(SQL_HANDLE_ENV, sql_env);
	}

	Connection::Connection(Root &root, SQLHDBC dbc)
		: root(root), dbc(dbc)
	{
		root.acquire();
	}

	Connection::~Connection()
	{
		SQLFreeHandle(SQL_HANDLE_DBC, dbc);
		root.release();
	}

	Result Connection::connect(void *result, BlobReference const &source, BlobReference const &user, BlobReference const &password, ...)
	{
		if (SQL_SUCCEEDED(SQLConnect(dbc, (SQLCHAR *)source.data, source.count, (SQLCHAR *)user.data, user.count, (SQLCHAR *)password.data, password.count)))
		{
			return NULL;
		}
		return new Error(SQL_HANDLE_DBC, dbc);
	}

	Result Connection::statement(interface::Statement *&result, ...)
	{
		SQLHSTMT stmt;
		if(SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt)))
		{
			result = new Statement(*this, stmt);
			return NULL;
		}
		result = NULL;
		return new Error(SQL_HANDLE_DBC, dbc);
	}

	Statement::Statement(Connection &connection, SQLHSTMT stmt)
		: connection(connection), stmt(stmt)
	{
		connection.acquire();
	}

	Statement::~Statement()
	{
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		connection.release();
	}

	Result Statement::execDirect(void *result, BlobReference &query, ...)
	{
		if (SQL_SUCCEEDED(SQLExecDirect(stmt, (SQLCHAR*)query.data, query.count)))
		{
			return NULL;
		}
		return new Error(SQL_HANDLE_STMT, stmt);
	}

	Result Statement::fetch(void *result, ...)
	{
		if (SQL_SUCCEEDED(SQLFetch(stmt)))
		{
			return NULL;
		}
		return new Error(SQL_HANDLE_STMT, stmt);
	}

	Result Statement::getNumber(double &result, const int &columnIndex, ...)
	{
		if (SQL_SUCCEEDED(SQLGetData(stmt, columnIndex, SQL_C_DOUBLE, &result, sizeof(double), NULL)))
		{
			return NULL;
		}
		return new Error(SQL_HANDLE_STMT, stmt);
	}

	Result Statement::getText(BlobReference &result, const int &columnIndex, ...)
	{
		text.clear();
		char buffer[1024];
		SQLINTEGER count;
		SQLRETURN code;
		while (SQL_SUCCEEDED(code = SQLGetData(stmt, columnIndex, SQL_C_BINARY, buffer, 1024, &count)))
		{
			if (count < 0)
			{
				result.count = 0;
				result.data = NULL;
				return NULL;
			}
			text.append(buffer, count);
			if (code == SQL_SUCCESS)
			{
				result.data = text.size()?&text[0]:buffer;
				result.count = count;
				return NULL;
			}
		}
		return new Error(SQL_HANDLE_STMT, stmt);
	}
}
