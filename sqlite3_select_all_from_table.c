#include <sqlite3/sqlite3.h>
#include <stdio.h>
#include <stddef.h>

int main(void)
{
	const char *sql_stmt = "SELECT * FROM the_first_table";
	const char *db_name = "basic_db.db";
	sqlite3 *db = NULL;
	sqlite3_stmt *pSqlite3_stmt = NULL;

	int ret = sqlite3_open_v2(db_name, &db, SQLITE_OPEN_READONLY, NULL);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "FAILED TO OPEN DATABASE : %s\n", db_name);
		return ret;
	}

	ret = sqlite3_prepare_v2(db, sql_stmt, -1, &pSqlite3_stmt, NULL);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "FAILED TO PREPARE SQL : \n%s\n", sql_stmt);
		fprintf(stderr, "ERROR : %s \n", sqlite3_errmsg(db));
		(void)sqlite3_close_v2(db);
		return ret;
	}

	ret = sqlite3_step(pSqlite3_stmt);
	if (ret != SQLITE_ROW) {
		fprintf(stderr, "FAILED TO EVALUATE SQL : \n%s\n", sql_stmt);
		fprintf(stderr, "ERROR : %s \n", sqlite3_errmsg(db));
	        (void)sqlite3_finalize(pSqlite3_stmt);
		(void)sqlite3_close_v2(db);
		return ret;
	}

	printf("%d %s %s \n",
	       sqlite3_column_int(pSqlite3_stmt, 0),
	       sqlite3_column_text(pSqlite3_stmt, 1),
	       sqlite3_column_text(pSqlite3_stmt, 2));

	(void)sqlite3_finalize(pSqlite3_stmt);
	(void)sqlite3_close_v2(db);
	return 0;
}
