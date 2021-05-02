#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


//void sql_execute(char* sql, sqlite3 *db, char* data, int silent_output);
void sql_execute(char* sql, sqlite3 *db, char* data, int silent_output);

// Operations
void insert(sqlite3 *db, int id, char* firstname, char* lastname, char* city, char* dateofbirth, char* sex, char* eyecolor, int shoesize, int height);
void listall(sqlite3 *db);
void findbyid(sqlite3 *db, int id);
void findbycity(sqlite3 *db, char* city);
void listallids(sqlite3 *db);
int getlastid(sqlite3 *db);
char* getfieldvalue(sqlite3 *db, int id, char* field);

// Menus
void menu_insertnewperson(sqlite3 *db);
void menu_modifyperson(sqlite3 *db);
void menu_searchbyid(sqlite3 *db);
void menu_searchbycity(sqlite3 *db);
