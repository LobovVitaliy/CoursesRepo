#ifndef DB_MANAGER_H_INCLUDED
#define DB_MANAGER_H_INCLUDED

#include "sqlite3.h"

typedef struct db_s db_t;
typedef struct entity_s entity_t;

entity_t * entity_new();
void entity_free(entity_t * self);
int entity_getID(entity_t * self);
char * entity_getName(entity_t * self);
char * entity_getSurname(entity_t * self);

db_t * db_new(const char * dbFile);
void db_free(db_t * self);
int db_name(db_t * self, char ** names);
int db_count(db_t * self, char * sqlQuery);
entity_t * db_getDataById(db_t * self, char * sqlQuery, int index);
int db_insertData(db_t * self, char * sqlQuery, int id, char * name, char * surname);
void db_deleteData(db_t * self, char * sqlQuery, int id);
void db_updateData(db_t * self, char * sqlQuery, int id, char * name, char * surname);

#endif // DB_MANAGER_H_INCLUDED

