#ifndef DB_MANAGER_H_INCLUDED
#define DB_MANAGER_H_INCLUDED

#include "sqlite3.h"
#include "list.h"
#include "ScrumMaster.h"

typedef struct db_s db_t;

db_t * db_new(const char * dbFile);
void db_free(db_t * self);

void db_parse(db_t * self, list_t * masters);
int db_count(db_t * self);
master_t * db_getDataById(db_t * self, int index);
int db_insertData(db_t * self, char * name, char * surname, int countK, int countP);
void db_deleteData(db_t * self, int index);
void db_filtration(db_t * self, list_t * masters, int countK, int countP);

#endif // DB_MANAGER_H_INCLUDED

