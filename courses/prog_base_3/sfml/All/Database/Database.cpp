#include "Database.hpp"

Database:: Database(const char * dbFile)
{
    sqlite3_open(dbFile, & db);
}

Database:: ~Database()
{
    sqlite3_close(db);
}

int Database:: count(const char * sqlQuery)
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
    {
        return -1;
    }
    int count = sqlite3_column_int(stmt, 0);

    sqlite3_finalize(stmt);
    return count;
}

int Database:: getData(const char * sqlQuery, char * name, int ID)
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, ID);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
    {
        return -1;
    }

    strcpy(this->Name, name);
    this->ID = ID;
    this->R = sqlite3_column_int(stmt, 2);
    this->x = sqlite3_column_int(stmt, 3);
    this->y = sqlite3_column_int(stmt, 4);
    this->Radius = sqlite3_column_int(stmt, 5);

    sqlite3_finalize(stmt);
    return 1;
}

int Database:: getDataByIndex(const char * sqlQuery, int index)
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    int i = 0;
    while (1)
    {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc)
        {
            return -1;
        }
        else if (SQLITE_DONE == rc)
        {
            break;
        }
        else if (SQLITE_ROW == rc)
        {
            if (index == i)
            {
                strcpy(this->Name, (char *)sqlite3_column_text(stmt, 0));
                this->ID = sqlite3_column_int(stmt, 1);
                this->R = sqlite3_column_int(stmt, 2);
                this->x = sqlite3_column_int(stmt, 3);
                this->y = sqlite3_column_int(stmt, 4);
                this->Radius = sqlite3_column_int(stmt, 5);

                break;
            }
            i++;
        }
    }

    sqlite3_finalize(stmt);
    return 1;
}

int Database:: insertData(const char * sqlQuery, char * name, int ID, int R, int x, int y, int Radius)
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, ID);
    sqlite3_bind_int(stmt, 3, R);
    sqlite3_bind_int(stmt, 4, x);
    sqlite3_bind_int(stmt, 5, y);
    sqlite3_bind_int(stmt, 6, Radius);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
    {
        return -1;
    }

    sqlite3_finalize(stmt);
    return sqlite3_last_insert_rowid(db);
}

int Database:: deleteData(const char * sqlQuery, char * name, int ID)
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, ID);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
    {
        return -1;
    }

    sqlite3_finalize(stmt);
    return 1;
}

int Database:: updateDataRadius(const char * sqlQuery, char * name, int ID, int Radius)
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    sqlite3_bind_int(stmt, 1, Radius);
    sqlite3_bind_text(stmt, 2, name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, ID);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
    {
        return -1;
    }

    sqlite3_finalize(stmt);
    return 1;
}

int Database:: updateDataID(const char * sqlQuery, char * name, int ID, int newID)
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    sqlite3_bind_int(stmt, 1, newID);
    sqlite3_bind_text(stmt, 2, name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, ID);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
    {
        return -1;
    }

    sqlite3_finalize(stmt);
    return 1;
}

int Database:: updateDataCoord(const char * sqlQuery, char * name, int ID, int x, int y)
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    sqlite3_bind_int(stmt, 1, x);
    sqlite3_bind_int(stmt, 2, y);
    sqlite3_bind_text(stmt, 3, name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, ID);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
    {
        return -1;
    }

    sqlite3_finalize(stmt);
    return 1;
}

int Database:: clearData(const char * sqlQuery)
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery), &stmt, NULL);

    sqlite3_bind_text(stmt, 1, "Castle", -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
    {
        return -1;
    }

    sqlite3_finalize(stmt);
    return 1;
}
