#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "db_manager.h"

struct db_s
{
    sqlite3 * db;
};

db_t * db_new(const char * dbFile)
{
    db_t * self = malloc(sizeof(struct db_s));
    int rc = sqlite3_open(dbFile, & self->db);
    if (SQLITE_ERROR == rc)
    {
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

void db_parse(db_t * self, list_t * masters)
{
    const char * sqlQuery = "SELECT * FROM ScrumMaster;";
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    while (1)
    {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc)
        {
            exit(1);
        }
        else if (SQLITE_DONE == rc)
        {
            break;
        }
        else if (SQLITE_ROW == rc)
        {
            int id = sqlite3_column_int(stmt, 0);
            char * name = (char *)sqlite3_column_text(stmt, 1);
            char * surname = (char *)sqlite3_column_text(stmt, 2);
            int countK = sqlite3_column_int(stmt, 3);
            int countP = sqlite3_column_int(stmt, 4);

            master_t * master = master_new();
            master_set(master, id, name, surname, countK, countP);
            list_add(masters, master);
        }
    }

    sqlite3_finalize(stmt);
}

int db_count(db_t * self)
{
    const char * sqlQuery = "SELECT COUNT(*) FROM ScrumMaster;";
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
    {
        puts("Can't select count!");
        exit(1);
    }
    int count = sqlite3_column_int(stmt, 0);

    sqlite3_finalize(stmt);
    return count;
}

master_t * db_getDataById(db_t * self, int index)
{
    const char * sqlQuery = "SELECT * FROM ScrumMaster;";
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    master_t * master = master_new();

    int i = 0;
    while (1)
    {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc)
        {
            puts("Can't select!");
            exit(1);
        }
        else if (SQLITE_DONE == rc)
        {
            break;
        }
        else if (SQLITE_ROW == rc)
        {
            if(index == i)
            {
                int id = sqlite3_column_int(stmt, 0);
                char * name = (char *)sqlite3_column_text(stmt, 1);
                char * surname = (char *)sqlite3_column_text(stmt, 2);
                int countK = sqlite3_column_int(stmt, 3);
                int countP = sqlite3_column_int(stmt, 4);

                master_set(master, id, name, surname, countK, countP);
                break;
            }
            i++;
        }
    }

    sqlite3_finalize(stmt);
    return master;
}

int db_insertData(db_t * self, char * name, char * surname, int countK, int countP)
{
    const char * sqlQuery = "INSERT INTO ScrumMaster (Name, Surname, countK, countP) VALUES (?, ?, ?, ?);";
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, surname, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, countK);
    sqlite3_bind_int(stmt, 4, countP);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
    {
        puts("Not inserted!");
        exit(1);
    }

    sqlite3_finalize(stmt);
    return sqlite3_last_insert_rowid(self->db);
}

void db_deleteData(db_t * self, int index)
{
    const char * sqlQuery = "DELETE FROM ScrumMaster WHERE ID = ?;";
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    sqlite3_bind_int(stmt, 1, index);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
    {
        puts("Not deleted!");
        exit(1);
    }

    sqlite3_finalize(stmt);
}

void db_filtration(db_t * self, list_t * masters, int countK, int countP)
{
    const char * sqlQuery = "SELECT * FROM ScrumMaster WHERE countK > ? AND countP < ?;";
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    sqlite3_bind_int(stmt, 1, countK);
    sqlite3_bind_int(stmt, 2, countP);

    while (1)
    {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc)
        {
            exit(1);
        }
        else if (SQLITE_DONE == rc)
        {
            break;
        }
        else if (SQLITE_ROW == rc)
        {
            int id = sqlite3_column_int(stmt, 0);
            char * name = (char *)sqlite3_column_text(stmt, 1);
            char * surname = (char *)sqlite3_column_text(stmt, 2);
            int countK = sqlite3_column_int(stmt, 3);
            int countP = sqlite3_column_int(stmt, 4);

            master_t * master = master_new();
            master_set(master, id, name, surname, countK, countP);
            list_add(masters, master);
        }
    }

    sqlite3_finalize(stmt);
}
