#ifndef DB_MANAGER_H_INCLUDED
#define DB_MANAGER_H_INCLUDED

#include "sqlite3.h"
#include "list.h"
#include "ScrumMaster.h"

typedef struct db_s db_t;

db_t * db_new(const char * dbFile);
void db_free(db_t * self);

void db_parse(db_t * self, list_t * master);

/*int db_name(db_t * self, char ** names);
int db_count(db_t * self, char * sqlQuery);
entity_t * db_getDataById(db_t * self, char * sqlQuery, int index);
int db_insertData(db_t * self, char * sqlQuery, int id, char * name, char * surname);
void db_deleteData(db_t * self, char * sqlQuery, int id);
void db_updateData(db_t * self, char * sqlQuery, int id, char * name, char * surname);*/

#endif // DB_MANAGER_H_INCLUDED

