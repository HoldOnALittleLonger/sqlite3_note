#include <stdio.h>
#include <sqlite3/sqlite3.h>

int main(void)
{
	const char *db_name = "basic_db.db";
	const char *table_name = "the_first_table";
	const char *sql_statement = "SELECT ? FROM the_first_table";

	sqlite3 *db_handler = NULL;
	sqlite3_stmt * pSqlite3_stmt = NULL;

	int ret = sqlite3_open_v2(db_name, &db_handler, SQLITE_OPEN_READONLY, NULL);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "FAILED TO OPEN DATABASE : %s\n", db_name);
		return 1;
	}

	ret = sqlite3_prepare_v2(db_handler, sql_statement, -1, &pSqlite3_stmt, NULL);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "PREPARE SQL STATEMENT FAILED : %s\n", sql_statement);
		fprintf(stderr, "ERROR : %s\n", sqlite3_errmsg(db_handler));
		ret = 1;
		goto out;
	}

	ret = sqlite3_bind_text(pSqlite3_stmt, 1, "ID", -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "BIND PARAMETERS FAILED : \"ID\", %s\n", table_name);
		fprintf(stderr, "ERROR : %s\n", sqlite3_errmsg(db_handler));
		ret = 1;
		goto destroy_and_out;
	}

	ret = sqlite3_step(pSqlite3_stmt);
	if (ret != SQLITE_ROW) {
		fprintf(stderr, "STEP SQL STATEMENT FAILED : %s\n", sql_statement);
		fprintf(stderr, "ERROR : %s\n", sqlite3_errmsg(db_handler));
		ret = 1;
		goto destroy_and_out;
	}

	fprintf(stdout, "ID\n%d\n", sqlite3_column_int(pSqlite3_stmt, 0));
	
destroy_and_out:
	sqlite3_finalize(pSqlite3_stmt);
out:
	sqlite3_close_v2(db_handler);
	return ret;
}
