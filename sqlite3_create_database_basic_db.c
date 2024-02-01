#include <sqlite3/sqlite3.h>
#include <stddef.h>
#include <stdio.h>

int main(void)
{
	const char *new_db = "basic_db.db";
	sqlite3 *db = NULL;
	int ret = 0;
	if ((ret = sqlite3_open_v2(new_db, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL)) != SQLITE_OK) {
		fprintf(stderr, "FAILED TO CREATE DATABASE %s \n", new_db);
		return ret;
	}
	(void)sqlite3_close_v2(db);
	return 0;
}
