#include "includes.h"

void insert(sqlite3 *db, int id, char* firstname, char* lastname, char* city, char* dateofbirth, char* sex, char* eyecolor, int shoesize, int height)
{
	char sql[1024];
	sprintf(sql, "INSERT INTO 'main'.'dbo.Person' (Id, FirstName, LastName, City, DateOfBirth, Sex, EyeColor, ShoeSize, Height) VALUES ('%d', '%s', '%s', '%s', '%s', '%s', '%s', '%d', '%d')", id, firstname, lastname, city, dateofbirth, sex, eyecolor, shoesize, height);
	sql_execute(sql, db, "insert", 0);
}

void listall(sqlite3 *db)
{
	char* sql = "SELECT * FROM 'main'.'dbo.Person'";
	sql_execute(sql, db, "list all", 0);
}

void listallids(sqlite3 *db)
{
	char* sql = "SELECT Id FROM 'main'.'dbo.Person'";
	sql_execute(sql, db, "listing ids", 0);
}

int getlastid(sqlite3 *db)
{
	char* sql = "SELECT Id FROM 'main'.'dbo.Person' WHERE ROWID IN ( SELECT max( ROWID ) FROM 'main'.'dbo.Person' );";

	/* https://stackoverflow.com/questions/12005902/c-program-linux-get-command-line-output-to-a-variable-and-filter-data */
	char result[16];
	FILE *p;
	p = popen("sqlite3 ./data.sqlite \"SELECT Id FROM 'main'.'dbo.Person' WHERE ROWID IN ( SELECT max( ROWID ) FROM 'main'.'dbo.Person' );\"", "r");

	if (!p)
	{
		fprintf(stderr, "Error opening pipe.\n");
		return 1;
	}

	int index = 0;
	while (!feof(p))
	{
		//printf("%c", fgetc(p));
		result[index] = fgetc(p);
		if(isdigit(result[index]))
		{
			index++;
		}
		else
		{
			result[index] = 0;
		}
	}
	//printf("Value length: %d\n", index);

	if (pclose(p) == -1)
	{
		fprintf(stderr, "Error!\n");
		return 1;
	}

	/* Print out the reuslt */
	//printf("Last ID = %s\n", result);

	int i;
	sscanf(result, "%d", &i);
	return i;
}

char buffer[1024];
char* getfieldvalue(sqlite3 *db, int id, char* field)
{
	char command[256];
	sprintf(command, "sqlite3 ./data.sqlite \"SELECT %s FROM 'main'.'dbo.Person' WHERE Id='%d'\"", field, id);

	FILE *p;
	p = popen(command, "r");

	if (!p)
	{
		fprintf(stderr, "Error opening pipe.\n");
		return "null";
	}

	int index = 0;
	while (!feof(p))
	{
		buffer[index] = fgetc(p);
		index++;
	}

	// Clean last char
	buffer[index-1] = 0;

	if (pclose(p) == -1)
	{
		fprintf(stderr, "Error!\n");
		return "null";
	}

	return buffer;
}

void findbyid(sqlite3 *db, int id)
{
	char sql[64];
	sprintf(sql, "SELECT * FROM 'main'.'dbo.Person' WHERE Id='%d'", id);
	sql_execute(sql, db, "search", 0);
}

void findbycity(sqlite3 *db, char* city)
{
	char sql[128];
	sprintf(sql, "SELECT * FROM 'main'.'dbo.Person' WHERE City='%s'", city);
	sql_execute(sql, db, "search", 0);
}
