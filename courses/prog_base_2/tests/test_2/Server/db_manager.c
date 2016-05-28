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

void db_parse(db_t * self, list_t * master)
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
            const unsigned char * name = sqlite3_column_text(stmt, 1);
            const unsigned char * surname = sqlite3_column_text(stmt, 2);
            int count = sqlite3_column_int(stmt, 3);
            double score = sqlite3_column_double(stmt, 4);
            const unsigned char * date = sqlite3_column_text(stmt, 5);

            master_t * sm = master_new();
            master_set(sm, id, name, surname, count, date, score);
            list_add(master, sm);
        }
    }

    sqlite3_finalize(stmt);
}

/*int db_name(db_t * self, char ** names)
{
    const char * sqlQuery = "SELECT name FROM sqlite_master WHERE type = \"table\"";
    sqlite3_stmt * stmt = NULL;

    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    int i = 0;
    int count = 0;

    while (1)
    {
        int status = sqlite3_step(stmt);

        if (SQLITE_ROW == status)
        {
            if(i != 0) strcpy(names[count++], (const char*)sqlite3_column_text(stmt, 0));
            i++;
        }
        else if (SQLITE_DONE == status)
        {
            break;
        }
    }

    sqlite3_finalize(stmt);
    return count;
}

int db_count(db_t * self, char * sqlQuery)
{
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

entity_t * db_getDataById(db_t * self, char * sqlQuery, int index)
{
    sqlite3_stmt * stmt = NULL;
    entity_t * entity = entity_new();

    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

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
                int ID = sqlite3_column_int(stmt, 0);
                const unsigned char * name = sqlite3_column_text(stmt, 1);
                const unsigned char * surname = sqlite3_column_text(stmt, 2);

                entity->ID = ID;
                strcpy(entity->name, (const char *)name);
                strcpy(entity->surname, (const char *)surname);
                break;
            }
            i++;
        }
    }

    sqlite3_finalize(stmt);
    return entity;
}

int db_insertData(db_t * self, char * sqlQuery, int id, char * name, char * surname)
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    if(id < 1) id = 0;
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_bind_text(stmt, 2, name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, surname, -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
    {
        puts("Not inserted!");
        exit(1);
    }

    sqlite3_finalize(stmt);
    return sqlite3_last_insert_rowid(self->db);
}

void db_deleteData(db_t * self, char * sqlQuery, int id)
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    sqlite3_bind_int(stmt, 1, id);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
    {
        puts("Not deleted!");
        exit(1);
    }

    sqlite3_finalize(stmt);
}

void db_updateData(db_t * self, char * sqlQuery, int id, char * name, char * surname)
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, surname, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, id);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
    {
        puts("Not updated!");
        exit(1);
    }

    sqlite3_finalize(stmt);
}*/
