#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <cstring>

#include "sqlite3/sqlite3.h"

class Database
{
public:

    sqlite3 * db;

    char Name[20];
    int ID;
    int R;
    int x;
    int y;
    int Radius;

    Database(const char * dbFile);
    ~Database();

    int count(const char * sqlQuery);
    int getData(const char * sqlQuery, char * name, int ID);
    int getDataByIndex(const char * sqlQuery, int index);
    int insertData(const char * sqlQuery, char * name, int ID, int R, int x, int y, int Radius);
    int deleteData(const char * sqlQuery, char * name, int ID);
    int updateDataRadius(const char * sqlQuery, char * name, int ID, int Radius);
    int updateDataID(const char * sqlQuery, char * name, int ID, int newID);
    int updateDataCoord(const char * sqlQuery, char * name, int ID, int x, int y);
    int clearData(const char * sqlQuery);
};

#endif
