#ifndef DB_MANAGER_H_INCLUDED
#define DB_MANAGER_H_INCLUDED

#include "ScrumMaster.h"

typedef struct db_s db_t;

db_t * db_new(const char * dbFile);
void db_free(db_t * self);

int db_insertScrumMaster(db_t * self, master_t * sm);
master_t * db_getScrumMasterById(db_t * self, int id);
void db_updateScrumMaster(db_t * self, master_t * sm, int id);
void db_deleteScrumMaster(db_t * self, int id);
int db_countScrumMaster(db_t * self);
int db_getScrumMasterTask(db_t * self, int K, int P, master_t * arr, int arrMax);

#endif // DB_MANAGER_H_INCLUDED
