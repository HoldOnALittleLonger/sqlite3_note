#include <stddef.h>
#include <stdio.h>
#include <sqlite3/sqlite3.h>

int main(void)
{
	sqlite3 *db = NULL;
	if (sqlite3_open("sqlite3_first_time_open_close.db", &db) != SQLITE_OK) {
		fprintf(stderr, "Open database was failed.\n");
		return 1;
	}
	fprintf(stdout, "Opened database.\n");
	sqlite3_close(db);
	fprintf(stderr, "Closed databse.\n");
	return 0;
}
