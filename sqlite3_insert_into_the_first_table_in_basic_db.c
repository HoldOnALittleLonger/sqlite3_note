#include <sqlite3/sqlite3.h>
#include <stdio.h>
#include <stddef.h>

int main(void)
{
	const char *sql_stmt = "INSERT INTO the_first_table (ID, field1, field2) "
		"VALUES (0, 'first', 'second')";
	const char *db_name = "basic_db.db";
	sqlite3 *db = NULL;
	sqlite3_stmt *pSqlite3_stmt = NULL;

	if (sqlite3_open_v2(db_name, &db, SQLITE_OPEN_READWRITE, NULL) != SQLITE_OK) {
		fprintf(stderr, "FAILED TO OPEN DATABASE %s .\n", db_name);
		return -1;
	}

	int ret = sqlite3_prepare_v2(db, sql_stmt, -1, &pSqlite3_stmt, NULL);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "FAILED TO PREPARE SQL STATEMENT : \n%s\n", sql_stmt);
		fprintf(stderr, "ERROR : %s \n", sqlite3_errmsg(db));
		(void)sqlite3_close_v2(db);
		return ret;
	}

	ret = sqlite3_step(pSqlite3_stmt);
	if (ret != SQLITE_DONE) {
		fprintf(stderr, "FAILED TO EXECUTE SQL STATEMENT : \n%s\n", sql_stmt);
		fprintf(stderr, "ERROR : %s \n", sqlite3_errmsg(db));
		(void)sqlite3_finalize(pSqlite3_stmt);
		(void)sqlite3_close_v2(db);
		return ret;
	}

	(void)sqlite3_finalize(pSqlite3_stmt);
	(void)sqlite3_close_v2(db);
	return 0;
}
