#include "includes.h"

void menu_insertnewperson(sqlite3 *db)
{
	printf("# Insert new person #\n");

	// Increment ID from the last record
	int ID = getlastid(db) + 1;
	printf("ID: %d\n", ID);

	// First name
	printf("First name: ");
	char firstname[64];
	scanf("%s", firstname);

	// First name
	printf("Last name: ");
	char lastname[64];
	scanf("%s", lastname);

	// City
	printf("City: ");
	char city[64];
	scanf("%s", city);

	// Date of birth
	printf("Date of birth [yyyy-mm-dd]: ");
	char dateofbirth[10];
	scanf("%s", dateofbirth);

	// Sex
	printf("Sex: ");
	char sex[16];
	scanf("%s", sex);
	
	// Eye color
	printf("Eye color: ");
	char eyecolor[16];
	scanf("%s", eyecolor);

	// Shoesize
	printf("Shoesize [0-99]: ");
	int shoesize;
	scanf("%d", &shoesize);

	// Height
	printf("Height [0-999]: ");
	int height;
	scanf("%d", &height);

	insert(db, ID, firstname, lastname, city, dateofbirth, sex, eyecolor, shoesize, height);
}

void askfield(char* field, sqlite3* db, int ID, char* result)
{
	printf(" = %s =\n", field);
	char* oldvalue = getfieldvalue(db, ID, field);
	printf("Old value: %s", oldvalue);
	printf("New value: ");
	scanf("%s", result);

	printf("Result: (%s)\n", result);

	if (strcmp(result,"x") == 0)
	{
		result = oldvalue;
		printf("> New result: (%s)", result);
	}
	printf("\n");
}

void menu_modifyperson(sqlite3 *db)
{
	char* field;

	printf("ID: ");
	int ID;
	scanf("%d", &ID);
	printf("\n");

	printf("To keep the old value, type 'x'\n");

	char firstname[32];
	askfield("FirstName", db, ID, firstname);

	char lastname[32];
	askfield("LastName", db, ID, lastname);

	char city[32];
	askfield("City", db, ID, city);

	char dateofbirth[32];
	askfield("DateOfBirth", db, ID, dateofbirth);

	char sex[16];
	askfield("Sex", db, ID, sex);

	char eyecolor[16];
	askfield("EyeColor", db, ID, eyecolor);

	char shoesize[4];
	askfield("ShoeSize", db, ID, shoesize);
	int shoesize_num;
	sscanf(shoesize, "%d", &shoesize_num);

	char height[4];
	askfield("Height", db, ID, height);
	int height_num;
	sscanf(height, "%d", &height_num);

	char sql[256];
	sprintf(sql, "DELETE FROM 'main'.'dbo.Person' WHERE Id=%d", ID);
	sql_execute(sql, db, "modify", 0);
	insert(db, ID, firstname, lastname, city, dateofbirth, sex, eyecolor, shoesize_num, height_num);
}

void menu_searchbyid(sqlite3 *db)
{
	printf("ID: ");
	int ID;
	scanf("%d", &ID);

	findbyid(db, ID);
}

void menu_searchbycity(sqlite3 *db)
{
	printf("City: ");
	char city[64];
	scanf("%s", city);

	/* Make sure the first character is uppercase */
	city[0] = toupper(city[0]);

	findbycity(db, city);
}
