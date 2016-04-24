#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sqlite3.h"
#include "db_manager.h"

static void _fillScrumMaster(sqlite3_stmt * stmt, master_t * sm);

struct db_s {
    sqlite3 * db;
};

db_t * db_new(const char * dbFile)
{
    db_t * self = malloc(sizeof(struct db_s));
    int rc = sqlite3_open(dbFile, & self->db);
    if (SQLITE_ERROR == rc) {
        puts("Can't open database");
        exit(1);
    }
    return self;
}

void db_free(db_t * self)
{
    sqlite3_close(self->db);
    free(self);
}

int db_insertScrumMaster(db_t * self, master_t * sm)
{
    const char * insertSM = "INSERT INTO ScrumMaster (Name, Surname, CountS, CountF, Score, Date) VALUES (?, ?, ?, ?, ?, ?);";
    sqlite3_stmt * stmt = NULL;

    sqlite3_prepare_v2(self->db, insertSM, strlen(insertSM), &stmt, NULL);

    sqlite3_bind_text(stmt, 1, sm->name, strlen(sm->name), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, sm->surname, strlen(sm->surname), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, sm->countS);
    sqlite3_bind_int(stmt, 4, sm->countF);
    sqlite3_bind_double(stmt, 5, sm->score);
    sqlite3_bind_text(stmt, 6, sm->date, strlen(sm->date), SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);

    if (SQLITE_ERROR == rc) {
        printf("Not inserted! %i\n", rc);
        exit(1);
    }

    sqlite3_finalize(stmt);
    return sqlite3_last_insert_rowid(self->db);
}

master_t * db_getScrumMasterById(db_t * self, int id)
{
    const char * getSM = "SELECT * FROM ScrumMaster WHERE ID = ?;";
    master_t * sm = malloc(sizeof(struct ScrumMaster));
    sqlite3_stmt * stmt = NULL;

    sqlite3_prepare_v2(self->db, getSM, strlen(getSM) + 1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
            puts("Can't select ScrumMaster");
            exit(1);
    }
    _fillScrumMaster(stmt, sm);

    sqlite3_finalize(stmt);
    return sm;
}

void db_updateScrumMaster(db_t * self, master_t * sm, int id)
{
    const char * updateSM = "UPDATE ScrumMaster SET Name = ?, Surname = ?, CountS = ?, CountF = ?, Score = ?, Date = ? WHERE ID = ?;";
    sqlite3_stmt * stmt = NULL;

    sqlite3_prepare_v2(self->db, updateSM, strlen(updateSM) + 1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, sm->name, strlen(sm->name), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, sm->surname, strlen(sm->surname), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, sm->countS);
    sqlite3_bind_int(stmt, 4, sm->countF);
    sqlite3_bind_double(stmt, 5, sm->score);
    sqlite3_bind_text(stmt, 6, sm->date, strlen(sm->date), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 7, id);

    int rc = sqlite3_step(stmt);

    if (SQLITE_ERROR == rc) {
        printf("Not updated! %i\n", rc);
        exit(1);
    }

    sqlite3_finalize(stmt);
}

void db_deleteScrumMaster(db_t * self, int id)
{
    const char * deleteSM = "DELETE FROM ScrumMaster WHERE ID = ?;";
    sqlite3_stmt * stmt = NULL;

    sqlite3_prepare_v2(self->db, deleteSM, strlen(deleteSM) + 1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);
    int rc = sqlite3_step(stmt);

    if (SQLITE_ERROR == rc) {
        printf("Not deleted! %i\n", rc);
        exit(1);
    }

    sqlite3_finalize(stmt);
}

int db_countScrumMaster(db_t * self)
{
    const char * countSM = "SELECT COUNT(*) FROM ScrumMaster;";
    sqlite3_stmt * stmt = NULL;

    sqlite3_prepare_v2(self->db, countSM, strlen(countSM) + 1, &stmt, NULL);
    int rc = sqlite3_step(stmt);

    if (SQLITE_ERROR == rc) {
        printf("Can't select count! %i\n", rc);
        exit(1);
    }
    int count = sqlite3_column_int(stmt, 0);

    sqlite3_finalize(stmt);
    return count;
}


static void _fillScrumMaster(sqlite3_stmt * stmt, master_t * sm)
{
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char * name = sqlite3_column_text(stmt, 1);
    const unsigned char * surname = sqlite3_column_text(stmt, 2);
    int countS = sqlite3_column_int(stmt, 3);
    int countF = sqlite3_column_int(stmt, 4);
    double score = sqlite3_column_double(stmt, 5);
    const unsigned char * date = sqlite3_column_text(stmt, 6);

    sm->id = id;
    strcpy(sm->name, (const char *)name);
    strcpy(sm->surname, (const char *)surname);
    sm->countS = countS;
    sm->countF = countF;
    sm->score = score;
    strcpy(sm->date, (const char *)date);
}

int db_getScrumMasterTask(db_t * self, int K, int P, master_t * arr, int arrMax)
{
    const char * sqlQuery = "SELECT * FROM ScrumMaster WHERE CountS > ? AND CountF < ?;";
    sqlite3_stmt * stmt = NULL;
    int count = 0;

    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery) + 1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, K);
    sqlite3_bind_int(stmt, 2, P);

    while (1) {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc) {
            puts("Can't select ScrumMaster");
            exit(1);
        } else if (SQLITE_DONE == rc) {
            break;
        } else {
            _fillScrumMaster(stmt, &arr[count]);
            count++;
        }
    }

    sqlite3_finalize(stmt);
    return count;
}
