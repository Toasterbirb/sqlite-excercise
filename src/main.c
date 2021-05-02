#include "includes.h"

int silent;

FILE* sqlbuffer;

int callback(void *data, int argc, char **argv, char **azColName)
{
	int i;

	if (!silent)
	{
		for (i = 0; i < argc; i++)
		{
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		}
		printf("\n");
	}
	return 0;
}

int main()
{
	sqlite3 *db;
	char *errorMsg = 0;
	int rc;
	char *sql;
	const char* data = "Callback function called";

	/* Open the database */
	rc = sqlite3_open("data.sqlite", &db);

	if ( rc )
	{
		fprintf(stderr, "Can't open database %s\n", sqlite3_errmsg(db));
		return (0);
	}
	else
	{
		fprintf(stderr, "Opened database successfully\n");
	}

	// Application loop
	while (1)
	{
		printf("[L] List all\n");
		printf("[I] Insert new person\n");
		printf("[M] Modify person data\n");
		printf("[F] Find person by ID\n");
		printf("[C] Find person by city\n");
		printf("[X] Quit\n");
		
		char selection;
		scanf("%s", &selection);
		selection = tolower(selection);

		switch (selection)
		{
			case ('x'):
				sqlite3_close(db);
				return 0;

			case ('l'):
				listall(db);
				break;

			case ('i'):
				menu_insertnewperson(db);
				break;

			case ('f'):
				menu_searchbyid(db);
				break;

			case ('c'):
				menu_searchbycity(db);
				break;

			case ('m'):
				menu_modifyperson(db);
				break;
		}
	}

	// Print out dbo.Person
	/* Create SQL statement */
	//sql = "SELECT * FROM 'main'.'dbo.Person'";
	//insert(db, 5001, "Antti", "Tuusula", "Jyväskylä", "2001-05-24", "Male", "Green", 36, 165);
	//sql_execute(sql, db);
	//listall(db);
	//listallids(db);
	//findbyid(db, 5000);
	//findbycity(db, "Lappeenranta");
	

	sqlite3_close(db);
	return 0;
}

void sql_execute(char* sql, sqlite3 *db, char* data, int silent_output)
{
	int rc;
	char* errorMsg = 0;
	silent = silent_output;
	char* buffer;

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, (void*)data, &errorMsg);

	if ( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", errorMsg);
		sqlite3_free(errorMsg);
	}
	else
	{
		fprintf(stdout, "Operation done successfully\n");
	}
}
