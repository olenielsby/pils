#include "pilsplug/pilsplug_component.h"
#include "sqlite-plug.h"

class Root : public pilsplug::interface::Root
{
public:
	pilsplug::Result database(pilsplug::interface::Database *&result, const char *filename, ...);
};

pilsplug::interface::Object *pilsplug::Plug::root() const
{
	return new Root();
}

pilsplug::Result Root::database(pilsplug::interface::Database *&result, const char *filename, ...)
{
	sqlite3 *db = NULL;
	int code = sqlite3_open(filename, &db);
	if (code != SQLITE_OK)
	{
		if (db) sqlite3_close(db);
		return new Error(db);
	}
	result = new Database(db);
	return NULL;
}
