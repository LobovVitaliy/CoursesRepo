#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <list>

using namespace std;
using namespace sf;

double length(int x1, int y1, int x2, int y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

///////////////FILE MAP///////////////
/*void saveMap(int R, int x, int y, int RT = 0)
{
    ofstream fout("map.txt", std::ios_base::app);
    fout << "R = " << R << "; x = " << x << "; y = " << y << "; RT = " << RT << "\n";
    fout.close();
}

void fileMapCleaning()
{
    fstream file;
    file.open("map.txt", ios::out);
    file << "";
    file.close();
}*/



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

    Database(const char * dbFile)
    {
        sqlite3_open(dbFile, & db);
    }

    ~Database()
    {
        sqlite3_close(db);
    }

    int count(char * sqlQuery)
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

    int getData(char * sqlQuery, char * name, int ID)
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

    int getDataById(char * sqlQuery, int index)
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

    int insertData(char * sqlQuery, char * name, int ID, int R, int x, int y, int Radius)
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

    int deleteData(char * sqlQuery, char * name, int ID)
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

    int updateDataRadius(char * sqlQuery, char * name, int ID, int Radius) //"UPDATE Map SET Radius = ? WHERE Name = ? AND ID = ?;"
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

    int updateDataID(char * sqlQuery, char * name, int ID, int newID) //"UPDATE Map SET ID = ? WHERE Name = ? AND ID = ?;"
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

    int updateDataCoord(char * sqlQuery, char * name, int ID, int x, int y) //"UPDATE Player SET x = ?, y = ? WHERE Name = ? AND ID = ?;"
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

    int clearData(char * sqlQuery)
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
};



///////////////FILE HERO///////////////
void saveHero(char * file, int Name, int R, int x, int y)
{
    ofstream fout(file, std::ios_base::app);
    fout << "Name = " << Name << "; R = " << R << "; x = " << x << "; y = " << y << "\n";
    fout.close();
}

void fileHeroCleaning(char * file)
{
    fstream fileClean;
    fileClean.open(file, ios::out);
    fileClean << "";
    fileClean.close();
}

void heroCleaning(char * file, int index)
{
    int Name, R, x, y;

    const int len = 50, strings = 1000;
    int countStr = 0;
    int delIndex = -1;
    char buffer[len][strings];

    ifstream fs(file, ios::in | ios::binary);
    while (fs.getline(buffer[countStr], 50))
    {
        char * pointName = strstr(buffer[countStr], "Name = ");
        pointName += 7;
        Name = atoi(pointName);

        char * pointR = strstr(buffer[countStr], "R = ");
        pointR += 4;
        R = atoi(pointR);

        char * pointX = strstr(buffer[countStr], "x = ");
        pointX += 4;
        x = atoi(pointX);

        char * pointY = strstr(buffer[countStr], "y = ");
        pointY += 4;
        y = atoi(pointY);

        if(Name == index)
        {
            delIndex = countStr;
        }
        countStr++;
    }
    fs.close();

    fileHeroCleaning(file);

    ofstream fout(file, std::ios_base::app);
    for(int k = 0; k < countStr; k++)
    {
        if(k != delIndex) fout << buffer[k] << "\n";
    }
    fout.close();
}

bool checkPos(char * file, int posX, int posY, int index)
{
    int Name, R, x, y;

    const int len = 50, strings = 100;
    int countStr = 0;
    char buffer[len][strings];

    ifstream fs(file, ios::in | ios::binary);
    while (fs.getline(buffer[countStr], 50))
    {
        char * pointName = strstr(buffer[countStr], "Name = ");
        pointName += 7;
        Name = atoi(pointName);

        char * pointR = strstr(buffer[countStr], "R = ");
        pointR += 4;
        R = atoi(pointR);

        char * pointX = strstr(buffer[countStr], "x = ");
        pointX += 4;
        x = atoi(pointX);

        char * pointY = strstr(buffer[countStr], "y = ");
        pointY += 4;
        y = atoi(pointY);

        if(Name != index)
        {
            if ( (((posX - x)*(posX - x)) + ((posY - y)*(posY - y))) <= R * R )
            {
                fs.close();
                return false;
            }
        }
        countStr++;
    }
    fs.close();
    return true;
}




class Images
{
public:             // private
    int x, y, w, h;

    //int originX;
    //int originY;    // public
    //String File;
    Image image;
    Texture texture;
    Sprite sprite;

    Images(String file, int positionX = 0, int positionY = 0, int width = 0, int height = 0)
    {
        image.loadFromFile(file);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setPosition(positionX, positionY);
        sprite.setOrigin(Vector2f(width/2, height/2));
        x = positionX;
        y = positionY;
        w = width;
        h = height;
    }
};
/////////////////HERO////////////////////////
///////КЛАСС ИГРОКА///////
class Player
{
public:
    char Name[20];

    Image image;
    Texture texture;
    Sprite sprite;

    int x, y, w, h, R;

    int begX, begY;
    int endX, endY;
    int dx, dy;
    float angle;
    int stopAngle = 360; // float

    int life = 3;
    bool isMove, isSelect, isLive;
    float CurrentFrame;

    /// health
    Images * scaleUpdate;

    Database * db;

    //float speed;
    //int dir;

    Player(String file, char * name, int ID, int positionX, int positionY, int width, int height)
    {
        db = new Database("Data.db");
        scaleUpdate = new Images("Images/scaleUpdate.png", 683, 200, 54, 7);
        strcpy(this->Name, name);
        x = positionX;
        y = positionY;
        w = width;
        h = height;
        image.loadFromFile(file);
        image.createMaskFromColor(Color::White);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setPosition(positionX, positionY);
        sprite.setTextureRect(IntRect(0, 200, w, h));
        sprite.setOrigin(w/2, h/2);
        R = 20;
        CurrentFrame = 0;
        isMove = false;
        isSelect = false;
        isLive = true;
        angle = 45;

        char * sqlQuery = "INSERT INTO Player (Name, ID, R, x, y, Radius) VALUES (?, ?, ?, ?, ?, ?);";
        db->insertData(sqlQuery, Name, ID, R, x, y, 50);
    }

    Player(Sprite spr, char * name, int ID, int positionX, int positionY, int width, int height)
    {
        db = new Database("Data.db");
        scaleUpdate = new Images("Images/scaleUpdate.png", 683, 200, 54, 7);
        strcpy(this->Name, name);
        x = positionX;
        y = positionY;
        w = width;
        h = height;
        sprite = spr;
        sprite.setPosition(positionX, positionY);
        sprite.setTextureRect(IntRect(0, 200, w, h));
        sprite.setOrigin(w/2, h/2);
        R = 20;
        CurrentFrame = 0;
        isMove = false;
        isSelect = false;
        isLive = true;
        angle = 45;

        //char * sqlQuery = "INSERT INTO Player (Name, ID, R, x, y, Radius) VALUES (?, ?, ?, ?, ?, ?);";
        //db->insertData(sqlQuery, Name, ID, R, x, y, 50);
    }

    ~Player()
    {
        delete db;
    }


    void update(float time, int numImage, int posX, int posY)
    {
        CurrentFrame += 0.02*time;
        if (CurrentFrame > 10) CurrentFrame -= 10;
        sprite.setTextureRect(IntRect(w * int(CurrentFrame), numImage, w, h));
        sprite.setPosition(posX, posY);
    }

    void stop()
    {
        if (-90 < angle && angle <= 0)
            sprite.setTextureRect(IntRect(0, 280, w, h));
        else if (-180 < angle && angle <= -90)
            sprite.setTextureRect(IntRect(0, 120, w, h));
        else if (0 < angle && angle <= 90)
            sprite.setTextureRect(IntRect(0, 200, w, h));
        else if (90 < angle && angle <= 180)
            sprite.setTextureRect(IntRect(0, 40, w, h));
    }

    void movement(float time)
    {
        if (isMove)
        {
            int status = 1;

            char * sqlQuery = "SELECT * FROM Map;";
            for(int j = 0; j < db->count("SELECT COUNT(*) FROM Map;"); j++)
            {
                db->getDataById(sqlQuery, j);

                if (x < -1475 + R)
                {
                    stopAngle = 180;
                    status = 0;
                    break;
                }
                else if (x > 2841 - R)
                {
                    stopAngle = 0;
                    status = 0;
                    break;
                }
                else if (y < -750 + R)
                {
                    stopAngle = -90;
                    status = 0;
                    break;
                }
                else if (y > 1593 - R)
                {
                    stopAngle = 90;
                    status = 0;
                    break;
                }

                if ( (((x - db->x)*(x - db->x)) + ((y - db->y)*(y - db->y))) < (db->R + 20)*(db->R + 20) )
                {
                    int stopX = db->x - x;
                    int stopY = db->y - y;

                    stopAngle = (180 / M_PI) * atan2(float(stopY), float(stopX));
                    status = 0;
                    break;
                }
            }

            /*char buffer[50];
            int bR, bx, by;

            ifstream fin("map.txt");
            while (fin.getline(buffer, 50))
            {
                char * pointR = strstr(buffer, "R = ");
                pointR += 4;
                bR = atoi(pointR);

                char * pointX = strstr(buffer, "x = ");
                pointX += 4;
                bx = atoi(pointX);

                char * pointY = strstr(buffer, "y = ");
                pointY += 4;
                by = atoi(pointY);
                if(bR == 220) bR = 84;
                if ( (((x - bx)*(x - bx)) + ((y - by)*(y - by))) < (bR + 20)*(bR + 20) )
                {
                    int stopX = bx - x;
                    int stopY = by - y;

                    stopAngle = (180 / M_PI) * atan2(float(stopY), float(stopX));

                    status = 0;
                    break;
                }
            }
            fin.close();*/

            if(stopAngle != 360)
            {
                int stopAngleR = stopAngle - 90;
                int stopAngleL = stopAngle + 90;

                if(stopAngleL > 180) stopAngleL -= 360;
                if(stopAngleR < -180) stopAngleR += 360;

                if(-90 <= stopAngle && stopAngle <= 90)
                {
                    if(stopAngleR <= angle && angle <= stopAngleL)
                    {
                        status = 0;
                    }
                    else
                    {
                        status = 1;
                        stopAngle = 360;
                    }
                }
                else
                {
                    if(stopAngleL <= angle && angle <= stopAngleR)
                    {
                        status = 1;
                        stopAngle = 360;
                    }
                    else
                    {
                        status = 0;
                    }
                }
            }

            if(status == 0)
            {
                stop();
                isMove = false;
                return;
            }

            if (x != endX || y != endY)
            {
                if (-45 < angle && angle <= 0)
                {
                    if (x <= begX + abs(dy)/2)
                        update(time, 280, x++, y--);
                    else if (x <= endX - abs(dy)/2)
                        update(time, 240, x++, y);
                    else if (x <= endX)
                        update(time, 280, x++, y--);
                }
                else if (-90 < angle && angle <= -45)
                {
                    if (y >= begY - abs(dx)/2)
                        update(time, 280, x++, y--);
                    else if (y >= endY + abs(dx)/2)
                        update(time, 160, x, y--);
                    else if (y >= endY)
                        update(time, 280, x++, y--);
                }
                else if (-135 < angle && angle <= -90)
                {
                    if (y >= begY - abs(dx)/2)
                        update(time, 120, x--, y--);
                    else if (y >= endY + abs(dx)/2)
                        update(time, 160, x, y--);
                    else if (y >= endY)
                        update(time, 120, x--, y--);
                }
                else if (-180 < angle && angle <= -135)
                {
                    if (x >= begX - abs(dy)/2)
                        update(time, 120, x--, y--);
                    else if (x >= endX + abs(dy)/2)
                        update(time, 80, x--, y);
                    else if (x >= endX)
                        update(time, 120, x--, y--);
                }
                else if (0 < angle && angle <= 45)
                {
                    if (x <= begX + abs(dy)/2)
                        update(time, 200, x++, y++);
                    else if (x <= endX - abs(dy)/2)
                        update(time, 240, x++, y);
                    else if (x <= endX)
                        update(time, 200, x++, y++);
                }
                else if (45 < angle && angle <= 90)
                {
                    if (y <= begY + abs(dx)/2)
                        update(time, 200, x++, y++);
                    else if (y <= endY - abs(dx)/2)
                        update(time, 0, x, y++);
                    else if (y <= endY)
                        update(time, 200, x++, y++);
                }
                else if (90 < angle && angle <= 135)
                {
                    if (y <= begY + abs(dx)/2)
                        update(time, 40, x--, y++);
                    else if (y <= endY - abs(dx)/2)
                        update(time, 0, x, y++);
                    else if (y <= endY)
                        update(time, 40, x--, y++);
                }
                else if (135 < angle && angle <= 180)
                {
                    if (x >= begX - abs(dy)/2)
                        update(time, 40, x--, y++);
                    else if (x >= endX + abs(dy)/2)
                        update(time, 80, x--, y);
                    else if (x >= endX)
                        update(time, 40, x--, y++);
                }
            }
            else
            {
                stop();
                isMove = false;
            }
        }
        else
        {
            stop();
        }
    }

    void mouseRight()
    {
        begX = x;
        begY = y;

        dx = endX - begX;
        dy = endY - begY;

        angle = (180 / M_PI) * atan2(float(dy), float(dx));
        //isSelect = false;
        //sprite.setColor(Color::White);
    }



    void changeLife()
    {
        life--;
        if(life == 0) isLive = false;
    }

    void checkLife(int RadiusTower)
    {
        char * sqlQuery = "SELECT * FROM Map;";
        for(int j = 0; j < db->count("SELECT COUNT(*) FROM Map;"); j++)
        {
            db->getDataById(sqlQuery, j);
            if(strcmp(db->Name, "EnemyTower") == 0)
            {
                if(pow(x - db->x, 2) + pow(y - db->y, 2) <= pow(db->Radius, 2))
                {
                    changeLife();
                    //break; // без break, так как при установки нескольких башень урон сумируется
                }
            }
            else if(strcmp(db->Name, "Fountain") == 0)
            {
                if(pow(x - db->x, 2) + pow(y - db->y, 2) <= pow(db->Radius, 2))
                {
                    if(life < 3) life++;
                    break;
                }
            }
        }
    }

    int getLife()
    {
        return life;
    }



    void stopHero()
    {
        isSelect = false;
        sprite.setColor(Color::White);
    }

    void selectHero(int posX, int posY)
    {
        if(isLive == true)
        {
            if(pow((posX - x), 2) + pow((posY - y), 2) <= pow(R, 2)) //if( (((posX - x)*(posX - x)) + ((posY - y)*(posY - y))) <= (R)*(R) )
            {
                isSelect = true;
                sprite.setColor(Color::Red);
            }
        }
    }

    void selectHero(int pressed_LKM_X, int pressed_LKM_Y, int released_LKM_X, int released_LKM_Y)
    {
        if(isLive == true)
        {
            if (((pressed_LKM_X <= x) && (x <= released_LKM_X) && (pressed_LKM_Y <= y) && (y <= released_LKM_Y))
                     || ((released_LKM_X <= x) && (x <= pressed_LKM_X) && (released_LKM_Y <= y) && (y <= pressed_LKM_Y))
                     || ((pressed_LKM_X <= x) && (pressed_LKM_Y >= y) && (released_LKM_X >= x) && (released_LKM_Y <= y))
                     || ((pressed_LKM_X >= x) && (pressed_LKM_Y <= y) && (released_LKM_X <= x) && (released_LKM_Y >= y))
                    )
            {
                isSelect = true;
                sprite.setColor(Color::Red);
            }
        }
    }

    void endPosHero(int posX, int posY, int index)
    {
        if(isLive == true && isSelect == true)
        {
            heroCleaning("hero.txt", index);
            isMove = true;

            while(checkPos("hero.txt", posX, posY, index) == false)
            {
                int vX = -1 + rand() % 2;
                posX += vX * (20 + rand() % 10);
                int vY = -1 + rand() % 2;
                posY += vY * (20 + rand() % 10);
            }

            endX = posX;
            endY = posY;

            mouseRight();
            saveHero("hero.txt", index, R, endX, endY);
        }
    }

    void updateHero(float time)
    {
        if(isLive == true) movement(time);
    }

    void drawHero(RenderWindow & window)
    {
        if(isLive == true)
        {
            scaleUpdate->sprite.setPosition(x + 17, y - 25);
            scaleUpdate->sprite.setTextureRect(IntRect(18 * (3 - life), 0, 18, 7));
            window.draw(scaleUpdate->sprite);
            window.draw(sprite);
        }
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }
};

/*class Hero
{
public:
    int maxCount = 7;
    Player * hero[7];
    int index = -1;

    Hero(String file, int positionX, int positionY, int width, int height)
    {
        hero[0] = new Player(file, positionX - 30, positionY - 50, width, height);
        hero[1] = new Player(file, positionX + 20, positionY - 50, width, height);
        hero[2] = new Player(file, positionX - 50, positionY, width, height);
        hero[3] = new Player(file, positionX, positionY, width, height);
        hero[4] = new Player(file, positionX + 50, positionY, width, height);
        hero[5] = new Player(file, positionX - 30, positionY + 50, width, height);
        hero[6] = new Player(file, positionX + 20, positionY + 50, width, height);
    }

    ~Hero()
    {
        for(int i = 0; i < maxCount; i++)
        {
            delete hero[i];
        }
    }

    void stop()
    {
        bool check = false;

        for(int i = 0; i < maxCount; i++)
        {
            if (hero[i]->isSelect ==  true)
            {
                check = true;
                break;
            }
        }

        if (check == true)
        {
            for(int i = 0; i < maxCount; i++)
            {
                hero[i]->isSelect = false;
                hero[i]->sprite.setColor(Color::White);
            }
        }
    }

    void select(int posX, int posY)
    {
        bool check = false;

        for(int i = 0; i < maxCount; i++)
        {
            if ( (((posX - hero[i]->x)*(posX - hero[i]->x)) + ((posY - hero[i]->y)*(posY - hero[i]->y))) <= (hero[i]->R)*(hero[i]->R) )
            {
                check = true;
                break;
            }
        }

        if (check == true)
        {
            for(int i = 0; i < maxCount; i++)
            {
                hero[i]->isSelect = true;
                hero[i]->sprite.setColor(Color::Red);
            }
        }
    }

    void select(int pressed_LKM_X, int pressed_LKM_Y, int released_LKM_X, int released_LKM_Y)
    {
        bool check = false;

        for(int i = 0; i < maxCount; i++)
        {
            if (((pressed_LKM_X <= hero[i]->x) && (hero[i]->x <= released_LKM_X) && (pressed_LKM_Y <= hero[i]->y) && (hero[i]->y <= released_LKM_Y))
                     || ((released_LKM_X <= hero[i]->x) && (hero[i]->x <= pressed_LKM_X) && (released_LKM_Y <= hero[i]->y) && (hero[i]->y <= pressed_LKM_Y))
                     || ((pressed_LKM_X <= hero[i]->x) && (pressed_LKM_Y >= hero[i]->y) && (released_LKM_X >= hero[i]->x) && (released_LKM_Y <= hero[i]->y))
                     || ((pressed_LKM_X >= hero[i]->x) && (pressed_LKM_Y <= hero[i]->y) && (released_LKM_X <= hero[i]->x) && (released_LKM_Y >= hero[i]->y))
                    )
            {
                check = true;
                break;
            }
        }

        if (check == true)
        {
            for(int i = 0; i < maxCount; i++)
            {
                hero[i]->isSelect = true;
                hero[i]->sprite.setColor(Color::Red);
            }
        }
    }

    void endPos(int posX, int posY, int index)
    {
        int check = 0;

        for(int i = 0; i < maxCount; i++)
        {
            if(hero[i]->isSelect)
            {
                check++;
            }
        }
        if(check == maxCount)
        {
            heroCleaning(index);

            for(int i = 0; i < maxCount; i++)
            {
                hero[i]->isMove = true;
            }

            while(checkPos(posX, posY, index) == false)
            {
                int vX = -1 + rand() % 2;
                posX += vX * (20 + rand() % 10);
                int vY = -1 + rand() % 2;
                posY += vY * (20 + rand() % 10);
            }

            hero[0]->endX = posX - 30;
            hero[0]->endY = posY - 50;

            hero[1]->endX = posX + 20;
            hero[1]->endY = posY - 50;

            hero[2]->endX = posX - 50;
            hero[2]->endY = posY;

            hero[3]->endX = posX;
            hero[3]->endY = posY;

            hero[4]->endX = posX + 50;
            hero[4]->endY = posY;

            hero[5]->endX = posX - 30;
            hero[5]->endY = posY + 50;

            hero[6]->endX = posX + 20;
            hero[6]->endY = posY + 50;


            for(int i = 0; i < maxCount; i++)
            {
                //hero[i]->mouseRight(posX, posY);
            }
            saveHero(index, hero[3]->R, hero[3]->endX, hero[3]->endY);
        }
    }

    void update(float time)
    {
        for(int i = 0; i < maxCount; i++)
        {
            //hero[i]->movement(time);
        }
    }

    void draw(RenderWindow & window)
    {
        for(int i = 0; i < maxCount; i++)
        {
            window.draw(hero[i]->sprite);
        }
    }
};*/

class Enemy
{
public:
    Image image;
    Texture texture;
    Sprite sprite;

    int x, y, w, h, R;

    int begX, begY;
    int endX, endY;
    int dx, dy;
    float angle;
    float stopAngle = 360;

    int life = 3;
    bool isMove, isSelect, isLive;
    float CurrentFrame;

    /// health
    Images * scaleUpdate;

    Database * db;

    //float speed;
    //int dir;

    Enemy(String file, int positionX, int positionY, int width, int height)
    {
        db = new Database("Data.db");
        scaleUpdate = new Images("Images/scaleUpdate.png", 683, 200, 54, 7);
        x = positionX;
        y = positionY;
        w = width;
        h = height;
        image.loadFromFile(file);
        image.createMaskFromColor(Color::White);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setPosition(positionX, positionY);
        sprite.setTextureRect(IntRect(0, 200, w, h));
        sprite.setOrigin(w/2, h/2);
        sprite.setColor(Color(80, 80, 80));
        R = 20;
        CurrentFrame = 0;
        isMove = false;
        isSelect = false;
        isLive = true;
        angle = 45;
    }

    Enemy(Sprite spr, int positionX, int positionY, int width, int height)
    {
        db = new Database("Data.db");
        scaleUpdate = new Images("Images/scaleUpdate.png", 683, 200, 54, 7);
        x = positionX;
        y = positionY;
        w = width;
        h = height;
        sprite = spr;
        sprite.setPosition(positionX, positionY);
        sprite.setTextureRect(IntRect(0, 200, w, h));
        sprite.setOrigin(w/2, h/2);
        sprite.setColor(Color(80, 80, 80));
        R = 20;
        CurrentFrame = 0;
        isMove = false;
        isSelect = false;
        isLive = true;
        angle = 45;
    }

    ~Enemy()
    {
        delete db;
    }

    void update(float time, int numImage, int posX, int posY)
    {
        CurrentFrame += 0.02*time;
        if (CurrentFrame > 10) CurrentFrame -= 10;
        sprite.setTextureRect(IntRect(w * int(CurrentFrame), numImage, w, h));
        sprite.setPosition(posX, posY);
    }

    void stop()
    {
        if (-90 < angle && angle <= 0)
            sprite.setTextureRect(IntRect(0, 280, w, h));
        else if (-180 < angle && angle <= -90)
            sprite.setTextureRect(IntRect(0, 120, w, h));
        else if (0 < angle && angle <= 90)
            sprite.setTextureRect(IntRect(0, 200, w, h));
        else if (90 < angle && angle <= 180)
            sprite.setTextureRect(IntRect(0, 40, w, h));
    }

    void movement(float time)
    {
        if (isMove)
        {
            int status = 1;

            char * sqlQuery = "SELECT * FROM Map;";
            for(int j = 0; j < db->count("SELECT COUNT(*) FROM Map;"); j++)
            {
                db->getDataById(sqlQuery, j);

                if ( (((x - db->x)*(x - db->x)) + ((y - db->y)*(y - db->y))) < (db->R + 20)*(db->R + 20) )
                {
                    int stopX = db->x - x;
                    int stopY = db->y - y;

                    stopAngle = (180 / M_PI) * atan2(float(stopY), float(stopX));

                    status = 0;
                    break;
                }
            }

            /*char buffer[50];
            int bR, bx, by;

            ifstream fin("map.txt");
            while (fin.getline(buffer, 50))
            {
                char * pointR = strstr(buffer, "R = ");
                pointR += 4;
                bR = atoi(pointR);

                char * pointX = strstr(buffer, "x = ");
                pointX += 4;
                bx = atoi(pointX);

                char * pointY = strstr(buffer, "y = ");
                pointY += 4;
                by = atoi(pointY);
                if(bR == 220) bR = 84;
                if ( (((x - bx)*(x - bx)) + ((y - by)*(y - by))) < (bR + 20)*(bR + 20) )
                {
                    int stopX = bx - x;
                    int stopY = by - y;

                    stopAngle = (180 / M_PI) * atan2(float(stopY), float(stopX));

                    status = 0;
                    break;
                }
            }
            fin.close();*/

            if(stopAngle != 360)
            {
                int stopAngleR = stopAngle - 90;
                int stopAngleL = stopAngle + 90;

                if(stopAngleL > 180) stopAngleL -= 360;
                if(stopAngleR < -180) stopAngleR += 360;

                if(-90 <= stopAngle && stopAngle <= 90)
                {
                    if(stopAngleR <= angle && angle <= stopAngleL)
                    {
                        status = 0;
                    }
                    else
                    {
                        status = 1;
                        stopAngle = 360;
                    }
                }
                else
                {
                    if(stopAngleL <= angle && angle <= stopAngleR)
                    {
                        status = 1;
                        stopAngle = 360;
                    }
                    else
                    {
                        status = 0;
                    }
                }
            }

            if(status == 0)
            {
                stop();
                isMove = false;
                return;
            }

            if (x != endX || y != endY)
            {
                if (-45 < angle && angle <= 0)
                {
                    if (x <= begX + abs(dy)/2)
                        update(time, 280, x++, y--);
                    else if (x <= endX - abs(dy)/2)
                        update(time, 240, x++, y);
                    else if (x <= endX)
                        update(time, 280, x++, y--);
                }
                else if (-90 < angle && angle <= -45)
                {
                    if (y >= begY - abs(dx)/2)
                        update(time, 280, x++, y--);
                    else if (y >= endY + abs(dx)/2)
                        update(time, 160, x, y--);
                    else if (y >= endY)
                        update(time, 280, x++, y--);
                }
                else if (-135 < angle && angle <= -90)
                {
                    if (y >= begY - abs(dx)/2)
                        update(time, 120, x--, y--);
                    else if (y >= endY + abs(dx)/2)
                        update(time, 160, x, y--);
                    else if (y >= endY)
                        update(time, 120, x--, y--);
                }
                else if (-180 < angle && angle <= -135)
                {
                    if (x >= begX - abs(dy)/2)
                        update(time, 120, x--, y--);
                    else if (x >= endX + abs(dy)/2)
                        update(time, 80, x--, y);
                    else if (x >= endX)
                        update(time, 120, x--, y--);
                }
                else if (0 < angle && angle <= 45)
                {
                    if (x <= begX + abs(dy)/2)
                        update(time, 200, x++, y++);
                    else if (x <= endX - abs(dy)/2)
                        update(time, 240, x++, y);
                    else if (x <= endX)
                        update(time, 200, x++, y++);
                }
                else if (45 < angle && angle <= 90)
                {
                    if (y <= begY + abs(dx)/2)
                        update(time, 200, x++, y++);
                    else if (y <= endY - abs(dx)/2)
                        update(time, 0, x, y++);
                    else if (y <= endY)
                        update(time, 200, x++, y++);
                }
                else if (90 < angle && angle <= 135)
                {
                    if (y <= begY + abs(dx)/2)
                        update(time, 40, x--, y++);
                    else if (y <= endY - abs(dx)/2)
                        update(time, 0, x, y++);
                    else if (y <= endY)
                        update(time, 40, x--, y++);
                }
                else if (135 < angle && angle <= 180)
                {
                    if (x >= begX - abs(dy)/2)
                        update(time, 40, x--, y++);
                    else if (x >= endX + abs(dy)/2)
                        update(time, 80, x--, y);
                    else if (x >= endX)
                        update(time, 40, x--, y++);
                }
            }
            else
            {
                stop();
                isMove = false;
            }
        }
        else
        {
            stop();
        }
    }

    void mouseRight()
    {
        begX = x;
        begY = y;

        dx = endX - begX;
        dy = endY - begY;

        angle = (180 / M_PI) * atan2(float(dy), float(dx));
        //isSelect = false;
        //sprite.setColor(Color::White);
    }



    void changeLife()
    {
        life--;
        if(life == 0) isLive = false;
    }

    void checkLife(int RadiusTower) //убрать входные параметры
    {
        char * sqlQuery = "SELECT * FROM Map;";
        for(int j = 0; j < db->count("SELECT COUNT(*) FROM Map;"); j++)
        {
            db->getDataById(sqlQuery, j);
            if(strcmp(db->Name, "Tower") == 0)
            {
                if(pow(x - db->x, 2) + pow(y - db->y, 2) <= pow(db->Radius, 2))
                {
                    changeLife();
                    //break; // без break, так как при установки нескольких башень урон сумируется
                }
            }
        }

        /*char buffer[50];
        int bR, bx, by;

        ifstream fin("map.txt");
        while (fin.getline(buffer, 50))
        {
            char * pointR = strstr(buffer, "R = ");
            pointR += 4;
            bR = atoi(pointR);

            char * pointX = strstr(buffer, "x = ");
            pointX += 4;
            bx = atoi(pointX);

            char * pointY = strstr(buffer, "y = ");
            pointY += 4;
            by = atoi(pointY);

            if(bR == 53)
            {
                if(pow(x - bx, 2) + pow(y - by, 2) <= pow(RadiusTower, 2))
                {
                    if(life == 1) isLive = false;
                    life--;
                    break;
                }
            }
        }
        fin.close();*/
    }

    bool checkLife(int posX, int posY)
    {
        if(pow(posX - x, 2) + pow(posY - y, 2) <= 2500)
        {
            changeLife();
            return true;
        }
        return false;
    }

    int getLife()
    {
        return life;
    }


    /*void stopEnemy()
    {
        isSelect = false;
        sprite.setColor(Color::White);
    }

    void selectEnemy(int posX, int posY)
    {
        if(pow((posX - x), 2) + pow((posY - y), 2) <= pow(R, 2)) //if( (((posX - x)*(posX - x)) + ((posY - y)*(posY - y))) <= (R)*(R) )
        {
            isSelect = true;
            sprite.setColor(Color::Red);
        }
    }

    void selectEnemy(int pressed_LKM_X, int pressed_LKM_Y, int released_LKM_X, int released_LKM_Y)
    {
        if (((pressed_LKM_X <= x) && (x <= released_LKM_X) && (pressed_LKM_Y <= y) && (y <= released_LKM_Y))
                 || ((released_LKM_X <= x) && (x <= pressed_LKM_X) && (released_LKM_Y <= y) && (y <= pressed_LKM_Y))
                 || ((pressed_LKM_X <= x) && (pressed_LKM_Y >= y) && (released_LKM_X >= x) && (released_LKM_Y <= y))
                 || ((pressed_LKM_X >= x) && (pressed_LKM_Y <= y) && (released_LKM_X <= x) && (released_LKM_Y >= y))
                )
        {
            isSelect = true;
            sprite.setColor(Color::Red);
        }
    }*/

    void endPosEnemy(int posX, int posY, int index)
    {
        if(isLive == true)
        {
            heroCleaning("enemy.txt", index);
            isMove = true;

            while(checkPos("enemy.txt", posX, posY, index) == false)
            {
                int vX = -1 + rand() % 2;
                posX += vX * (20 + rand() % 10);
                int vY = -1 + rand() % 2;
                posY += vY * (20 + rand() % 10);
            }

            endX = posX;
            endY = posY;

            mouseRight();
            saveHero("enemy.txt", index, R, endX, endY);
        }
    }

    void updateEnemy(float time)
    {
        if(isLive == true) movement(time);
    }

    void drawEnemy(RenderWindow & window)
    {
        if(isLive == true)
        {
            scaleUpdate->sprite.setPosition(x + 17, y - 25);
            scaleUpdate->sprite.setTextureRect(IntRect(18 * (3 - life), 0, 18, 7));
            window.draw(scaleUpdate->sprite);
            window.draw(sprite);
        }
    }
};

// обновить класс игрока:
// поправить спрайт
// исправить разность между скоростями по диагонали и по катетам (не критично!)

// скрол карты по диагонали (не критично!)
// увеличить карту
// отделить выдиление прямоугольником от выбора обьектов

// переписать сохрание игрока и зданий в базу дынных, потому что сохранение происходит неправильно !!! \
   когда персонаж стоит ровно под сданием, то он не может двигаться в любую из сторон !!!
// убрать получение денег с некоторых зданий !!!
// добавить жизнь и здоровье персонажа !!!
// добавить плюшки для других зданий !!!
// при нажатии на башню или фонтан, прорисовывать круг "разброса"
// добавить радиус башень !!!
// башни должны быть только по одному игроку, а не по всем сразу !!!
// замки врага разместить на задний план !!!
// ограеичить проходимость по краям карты !!!
// создать миникарту с возможностью тп !!!
// зависимость вражеских юнитов от вражеских строений
// увеличить радиус фонтана
// Изменить радиус основного круга вражеских обьектов !!!

/////////////////BUILDING////////////////////

void menu(RenderWindow & window);
void game(RenderWindow & window);
void settings(RenderWindow & window);

void menu(RenderWindow & window)
{
    Images Background("Images/Background.png");
    Images NewGame("Images/NewGame.png");
    Images LoadGame("Images/LoadGame.png");
    Images SettingsGame("Images/SettingsGame.png");
    Images QuitGame("Images/QuitGame.png");

    bool isMenu = true;
    int menuNum = 0;

    while (isMenu)
    {
        Vector2i pixelPosWindow = window.getPosition();
        Vector2f posWindow = window.mapPixelToCoords(pixelPosWindow);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    if (menuNum == 1)
                    {
                        game(window);
                    }
                    else if (menuNum == 2)
                    {
                        //to do
                    }
                    else if (menuNum == 3)
                    {
                        //to do
                        //settings(window);
                    }
                    else if (menuNum == 4)
                    {
                        isMenu = false;
                    }
                }
            }
        }

        NewGame.sprite.setColor(Color::White);
        LoadGame.sprite.setColor(Color::White);
        SettingsGame.sprite.setColor(Color::White);
        QuitGame.sprite.setColor(Color::White);

        menuNum = 0;

        if (IntRect(222, 252, 245, 78).contains(Mouse::getPosition(window)))
        {
            NewGame.sprite.setColor(Color(230, 100, 200));
            menuNum = 1;
        }
        else if (IntRect(222, 340, 245, 78).contains(Mouse::getPosition(window)))
        {
            LoadGame.sprite.setColor(Color(230, 100, 200));
            menuNum = 2;
        }
        else if (IntRect(222, 428, 245, 78).contains(Mouse::getPosition(window)))
        {
            SettingsGame.sprite.setColor(Color(230, 100, 200));
            menuNum = 3;
        }
        else if (IntRect(222, 516, 245, 78).contains(Mouse::getPosition(window)))
        {
            QuitGame.sprite.setColor(Color(230, 100, 200));
            menuNum = 4;
        }

        window.clear();

        Background.sprite.setPosition(posWindow.x, posWindow.y);
        NewGame.sprite.setPosition(posWindow.x, posWindow.y);
        LoadGame.sprite.setPosition(posWindow.x, posWindow.y);
        SettingsGame.sprite.setPosition(posWindow.x, posWindow.y);
        QuitGame.sprite.setPosition(posWindow.x, posWindow.y);

        window.draw(Background.sprite);
        window.draw(NewGame.sprite);
        window.draw(LoadGame.sprite);
        window.draw(SettingsGame.sprite);
        window.draw(QuitGame.sprite);

        window.display();
    }
}

void settings(RenderWindow & window)
{
    Images Settings("Images/Settings.png");
    Images SettingsBackground("Images/SettingsBackground.png");

    while (!Keyboard::isKeyPressed(Keyboard::Escape))
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.draw(SettingsBackground.sprite);
        window.draw(Settings.sprite);
        window.display();
    }
}

class ImagesBuild
{
public:             // private
    int x;
    int y;

    int w;
    int h;

    int R = 0;
    //int originX;
    //int originY;    // public
    //String File;
    Image image;
    Texture texture;
    Sprite sprite;

    bool isMove = false;
    bool isCreate = false;
    bool isLive = false;

    int coins = 0;

    ImagesBuild(String file, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int coins = 0)
    {
        //File = file;
        image.loadFromFile(file);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setPosition(positionX, positionY);
        x = positionX;
        y = positionY;
        w = width;
        h = height;
        isMove = false;
        isCreate = false;
        isLive = false;
        this->coins = coins;
        sprite.setOrigin(Vector2f(w/2, h/2));
    }

    ImagesBuild(Sprite spr, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int coins = 0)
    {
        //File = file;
        //image.loadFromFile(file);
        //texture.loadFromImage(image);
        sprite = spr;
        sprite.setPosition(positionX, positionY);
        sprite.setOrigin(Vector2f(width/2, height/2));
        x = positionX;
        y = positionY;
        w = width;
        h = height;
        isMove = false;
        isCreate = false;
        isLive = false;
        this->coins = coins;
    }

    void setPosition(int Radius, int posX, int posY)
    {
        R = Radius;
        x = posX;
        y = posY;
    }
};

class Building
{
public:
    ImagesBuild ** building;

    char Name[20];
    Database * db;

    int maxCount;
    int index = -1;
    //int coins = 0;

    Building(String file, char * name, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int maxCount = 0, int coins = 0)
    {
        db = new Database("Data.db");
        strcpy(this->Name, name);
        this->maxCount = maxCount;
        //this->coins = coins;
        building = new ImagesBuild* [maxCount];

        for(int i = 0; i < maxCount; i++)
        {
            building[i] = new ImagesBuild(file, positionX, positionY, width, height, coins);
        }
    }

    Building(Sprite spr, char * name, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int maxCount = 0, int coins = 0)
    {
        db = new Database("Data.db");
        strcpy(this->Name, name);
        this->maxCount = maxCount;
        //this->coins = coins;
        building = new ImagesBuild* [maxCount];

        for(int i = 0; i < maxCount; i++)
        {
            building[i] = new ImagesBuild(spr, positionX, positionY, width, height, coins);
        }
    }

    ~Building()
    {
        for (int i = 0; i < maxCount; i++)
        {
            delete building[i];
        }
        delete [] building;
        delete db;
    }


    int checkPosition(int posX, int posY)
    {
        for(int i = 0; i < index + 1; i++) // раньше было до maxCount, при удалени обьекта оставался выбор его улучшений
        {
            if ( (((posX - building[i]->x)*(posX - building[i]->x)) + ((posY - building[i]->y)*(posY - building[i]->y))) <= (building[i]->R)*(building[i]->R) )
            {
                return i;
            }
        }
        return -1;
    }

    int getX(int i)
    {
        if (building[i]->isLive)
            return building[i]->x;
        else
            return 5000;
    }

    int getY(int i)
    {
        if (building[i]->isLive)
            return building[i]->y;
        else
            return 5000;
    }

    void createAndMove(RenderWindow & window, int posX, int posY)
    {
        if (index < maxCount - 1)
        {
            index++;
            building[index]->isLive = true;
            building[index]->isMove = true;
            building[index]->isCreate = true;
            building[index]->sprite.setPosition(posX, posY);
            window.draw(building[index]->sprite);
        }
    }

    void deleteBuildingIndex(int indexBuilding) // db // change
    {
        char * sqlQuery = "DELETE FROM Map WHERE Name = ? AND ID = ?;";
        db->deleteData(sqlQuery, Name, indexBuilding); // change

        /*int RM, xM, yM;

        const int len = 50, strings = 50;
        int countStr = 0;
        int delIndex = 0;
        char buffer[len][strings];

        ifstream fs("map.txt", ios::in | ios::binary);
        while (fs.getline(buffer[countStr], 50))
        {
            char * pointR = strstr(buffer[countStr], "R = ");
            pointR += 4;
            RM = atoi(pointR);

            char * pointX = strstr(buffer[countStr], "x = ");
            pointX += 4;
            xM = atoi(pointX);

            char * pointY = strstr(buffer[countStr], "y = ");
            pointY += 4;
            yM = atoi(pointY);

            if(building[indexBuilding]->R == RM && building[indexBuilding]->x == xM && building[indexBuilding]->y == yM)
            {
                delIndex = countStr;
            }
            countStr++;
        }
        fs.close();

        fileMapCleaning();

        ofstream fout("map.txt", std::ios_base::app);
        for(int k = 0; k < countStr; k++)
        {
            if(k != delIndex) fout << buffer[k] << "\n";
        }
        fout.close();*/

        int x, y, w, h, R, coins;
        bool isMove, isCreate, isLive;

        Image image;
        Texture texture;
        Sprite sprite;

        char * sqlQueryUp = "UPDATE Map SET ID = ? WHERE Name = ? AND ID = ?;";

        for(int i = indexBuilding; i < index; i++)
        {
            ////////////////////////////////////////////
            x = building[i + 1]->x;
            y = building[i + 1]->y;
            w = building[i + 1]->w;
            h = building[i + 1]->h;
            R = building[i + 1]->R;
            coins = building[i + 1]->coins;

            image = building[i + 1]->image;
            texture = building[i + 1]->texture;
            sprite = building[i + 1]->sprite;

            isCreate = building[i + 1]->isCreate;
            isLive = building[i + 1]->isLive;
            isMove = building[i + 1]->isMove;

            ////////////////////////////////////////////
            building[i]->x = x;
            building[i]->y = y;
            building[i]->w = w;
            building[i]->h = h;
            building[i]->R = R;
            building[i]->coins = coins;

            building[i]->image = image;
            building[i]->texture = texture;
            building[i]->sprite = sprite;

            building[i]->isCreate = isCreate;
            building[i]->isLive = isLive;
            building[i]->isMove = isMove;

            db->updateDataID(sqlQueryUp, Name, i + 1, i);
        }

        building[index]->isCreate = false;
        building[index]->isLive = false;
        building[index]->isMove = false;

        index--;
    }

    void deleteBuilding()
    {
        if(index > -1)
        {
            if(building[index]->isMove)
            {
                building[index]->isMove = false;
                building[index]->isCreate = false;
                index--;
            }
        }
    }

    bool build(int Radius, int posX, int posY) // db
    {
        if(index > -1)
        {
            if(building[index]->isLive)
            {
                building[index]->isMove = false;
                building[index]->setPosition(Radius, posX, posY);
                //saveMap(Radius, posX, posY);

                char * sqlQuery = "INSERT INTO Map (Name, ID, R, x, y, Radius) VALUES (?, ?, ?, ?, ?, ?);";

                if(strcmp(Name, "Ambar") == 0)
                {
                    db->insertData(sqlQuery, Name, index, Radius, posX, posY, 220);
                }
                else if(strcmp(Name, "Fountain") == 0 || strcmp(Name, "Tower") == 0)
                {
                    db->insertData(sqlQuery, Name, index, Radius, posX, posY, 200);
                }
                else
                {
                    db->insertData(sqlQuery, Name, index, Radius, posX, posY, 0);
                }

                return true;
            }
        }
        return false;
    }

    void moveAndDraw(RenderWindow & window, int Radius, int posX, int posY) // db // change
    {
        char buffer[50];
        int R, x, y;

        for(int i = 0; i < maxCount; i++)
        {
            if (building[i]->isCreate)
            {
                if (building[index]->isMove)
                {
                    building[index]->sprite.setPosition(posX, posY);

                    char * sqlQuery = "SELECT * FROM Map;";
                    for(int j = 0; j < db->count("SELECT COUNT(*) FROM Map;"); j++)
                    {
                        db->getDataById(sqlQuery, j);
                        if(strcmp(db->Name, "Ambar") == 0) db->R = db->Radius; // change

                        // Проверяем краи карты и ближайшие обьекты на карте
                        if (posX < -1475 + Radius || posX > 2841 - Radius || posY < -750 + Radius || posY > 1593 - Radius)
                        {
                            building[index]->sprite.setColor(Color::Red);
                            building[index]->isLive = false;
                            break;
                        }
                        else if (db->R + Radius < length(posX, posY, db->x, db->y))
                        {
                            building[index]->sprite.setColor(Color::White);
                            building[index]->isLive = true;
                        }
                        else
                        {
                            building[index]->sprite.setColor(Color::Red);
                            building[index]->isLive = false;
                            break;
                        }
                    }

                    /*ifstream fin("map.txt");
                    while (fin.getline(buffer, 50))
                    {
                        char * pointR = strstr(buffer, "R = ");
                        pointR += 4;
                        R = atoi(pointR);

                        char * pointX = strstr(buffer, "x = ");
                        pointX += 4;
                        x = atoi(pointX);

                        char * pointY = strstr(buffer, "y = ");
                        pointY += 4;
                        y = atoi(pointY);

                        if (R + Radius < length(posX, posY, x, y))
                        {
                            building[index]->sprite.setColor(Color::White);
                            building[index]->isLive = true;
                        }
                        else
                        {
                            building[index]->sprite.setColor(Color::Red);
                            building[index]->isLive = false;
                            break;
                        }
                    }
                    fin.close();*/
                }
                window.draw(building[i]->sprite);
            }
        }
    }

    int setCoins(int indexBuilding, int newCoins)
    {
        building[indexBuilding]->coins += newCoins;
    }

    int getCoins()
    {
        int coins = 0;
        for(int i = 0; i < index + 1; i++)
        {
            if(building[i]->isMove == false)
            {
                 coins += building[i]->coins;
            }
        }
        return coins;
    }

    int getIndex()
    {
        return index;
    }
};

class BuildingEnemy
{
public:
    ImagesBuild ** building;

    char Name[20];
    Database * db;

    int maxCount;
    int index = -1;
    //int coins = 0;

    BuildingEnemy(String file, char * name, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int maxCount = 0, int coins = 0)
    {
        db = new Database("Data.db");
        strcpy(this->Name, name);
        this->maxCount = maxCount;
        //this->coins = coins;
        building = new ImagesBuild* [maxCount];

        for(int i = 0; i < maxCount; i++)
        {
            building[i] = new ImagesBuild(file, positionX, positionY, width, height, coins);
        }
    }

    ~BuildingEnemy()
    {
        for (int i = 0; i < maxCount; i++)
        {
            delete building[i];
        }
        delete [] building;
    }


    int getX(int i)
    {
        return building[i]->x;
    }

    int getY(int i)
    {
        return building[i]->y;
    }

    /*int setRadiusTower(int i, int RadiusTower)
    {
        building[i]->RadiusTower += RadiusTower;
    }*/

    void create(int Radius, int posX, int posY)
    {
        if (index < maxCount - 1)
        {
            index++;
            building[index]->isLive = true;
            building[index]->isCreate = true;
            building[index]->sprite.setPosition(posX, posY);

            char * sqlQuery = "INSERT INTO Map (Name, ID, R, x, y, Radius) VALUES (?, ?, ?, ?, ?, ?);";
            db->insertData(sqlQuery, Name, 0, Radius, posX, posY, 200);
        }
    }

    void deleteBuildingIndex(int indexBuilding) // db // change
    {
        char * sqlQuery = "DELETE FROM Map WHERE Name = ? AND ID = ?;";
        db->deleteData(sqlQuery, Name, indexBuilding); // change

        int x, y, w, h, R, coins;
        bool isMove, isCreate, isLive;

        Image image;
        Texture texture;
        Sprite sprite;

        char * sqlQueryUp = "UPDATE Map SET ID = ? WHERE Name = ? AND ID = ?;";

        for(int i = indexBuilding; i < index; i++)
        {
            ////////////////////////////////////////////
            x = building[i + 1]->x;
            y = building[i + 1]->y;
            w = building[i + 1]->w;
            h = building[i + 1]->h;
            R = building[i + 1]->R;
            coins = building[i + 1]->coins;

            image = building[i + 1]->image;
            texture = building[i + 1]->texture;
            sprite = building[i + 1]->sprite;

            isCreate = building[i + 1]->isCreate;
            isLive = building[i + 1]->isLive;
            isMove = building[i + 1]->isMove;

            ////////////////////////////////////////////
            building[i]->x = x;
            building[i]->y = y;
            building[i]->w = w;
            building[i]->h = h;
            building[i]->R = R;
            building[i]->coins = coins;

            building[i]->image = image;
            building[i]->texture = texture;
            building[i]->sprite = sprite;

            building[i]->isCreate = isCreate;
            building[i]->isLive = isLive;
            building[i]->isMove = isMove;

            db->updateDataID(sqlQueryUp, Name, i + 1, i);
        }

        building[index]->isCreate = false;
        building[index]->isLive = false;
        building[index]->isMove = false;

        index--;
    }

    void deleteBuilding()
    {
        if(index > -1)
        {
            if(building[index]->isMove)
            {
                building[index]->isCreate = false;
                index--;
            }
        }
    }

    bool build(int Radius, int posX, int posY) // db
    {
        if(index > -1)
        {
            if(building[index]->isLive)
            {
                building[index]->isMove = false;
                building[index]->setPosition(Radius, posX, posY);
                //saveMap(Radius, posX, posY);

                char * sqlQuery = "INSERT INTO Map (Name, ID, R, x, y, Radius) VALUES (?, ?, ?, ?, ?, ?);";

                if(strcmp(Name, "Ambar") == 0)
                {
                    db->insertData(sqlQuery, Name, index, Radius, posX, posY, 220);
                }
                else if(strcmp(Name, "Fountain") == 0 || strcmp(Name, "Tower") == 0)
                {
                    db->insertData(sqlQuery, Name, index, Radius, posX, posY, 200);
                }
                else
                {
                    db->insertData(sqlQuery, Name, index, Radius, posX, posY, 0);
                }

                return true;
            }
        }
        return false;
    }

    int getIndex()
    {
        return index;
    }

    void draw(RenderWindow & window)
    {
        for(int i = 0; i < maxCount; i++)
        {
            window.draw(building[i]->sprite);
        }
    }
};

void game(RenderWindow & window)
{
    //saveMap(135, 683, 384); // R - можно изменить
    //fileMapCleaning();
    fileHeroCleaning("hero.txt");
    fileHeroCleaning("enemy.txt");

    Images miniMap("Images/miniMap5.png", 0, 510);

    // Загружаю картинки только один раз, в дальнейшем использую только их спрайты
    Images imageCave("Building/cave.png", 0, 0, 90, 60);
    Images imageBuilding("Building/building.png", 0, 0, 95, 88);
    Images imageHouse("Building/house.png", 0, 0, 140, 115);
    Images imageFountain("Building/fountain.png", 0, 0, 60, 80);
    Images imageTower("Building/tower.png", 0, 0, 75, 105);
    Images imageAmbar("Building/ambar.png", 0, 0, 165, 134);

    Building cave(imageCave.sprite, "Cave", 0, 0, 90, 60, 5, 25);
    Building building(imageBuilding.sprite, "Building", 0, 0, 95, 88, 5, 50);
    Building house(imageHouse.sprite, "House", 0, 0, 140, 115, 5, 10);
    Building fountain(imageFountain.sprite, "Fountain", 0, 0, 60, 80, 5);
    Building tower(imageTower.sprite, "Tower", 0, 0, 75, 105, 5);
    Building ambar(imageAmbar.sprite, "Ambar", 0, 0, 165, 134, 5, 10);

    //Building cave("Building/cave.png", "Cave", 0, 0, 90, 60, 5, 25);
    //Building building("Building/building.png", "Building", 0, 0, 95, 88, 5, 50);
    //Building house("Building/house.png", "House", 0, 0, 140, 115, 5, 10);
    //Building fountain("Building/fountain.png", "Fountain", 0, 0, 60, 80, 5);
    //Building tower("Building/tower.png", "Tower", 0, 0, 75, 105, 5);
    //Building ambar("Building/ambar.png", "Ambar", 0, 0, 165, 134, 5, 10);

    Images background("Images/BGG1.png", -1500, -850);
    Images castle("Images/CastleNew.png", 683, 384, 250, 268);
    Images selection("Images/selection.png", 675, 384, 365, 317);//683->675

    Images selectionNot("Images/selectionNotLittle.png", 0, 0, 58, 60);
    Images selectionNotAddition("Images/selectionNotLittle.png", 0, 0, 58, 60);

    Images selectionNot1("Images/selectionNot.png", 603, 266, 70, 72);
    Images selectionNot2("Images/selectionNot.png", 747, 266, 70, 72);
    Images selectionNot3("Images/selectionNot.png", 819, 384, 70, 72);
    Images selectionNot4("Images/selectionNot.png", 747, 504, 70, 72);
    Images selectionNot5("Images/selectionNot.png", 603, 504, 70, 72);
    Images selectionNot6("Images/selectionNot.png", 533, 384, 70, 72);

    Images selection2("Images/selection2Update1.png", 0, 0, 64, 164);//80->64
    Images selection3House("Images/selection3House.png", 0, 0, 160, 164);
    Images selection3Ambar("Images/selection3Ambar.png", 0, 0, 160, 164);

    int indexCave = -1;
    int indexBuilding = -1;
    int indexHouse = -1;
    int indexFountain = -1;
    int indexTower = -1;
    int indexAmbar = -1;

    Font font;
    font.loadFromFile("CyrilicOld.ttf");
    Text text("", font, 20);

    bool pressed_selection_building = false;
    bool pressed_selection = false;
    int isSelect = 0;

    char money[10] = "0";
    int coins = 100000;

    Clock clock;
    Clock clockTimer;
    Clock clockTimerStart;

    float timer = 0;
    float timerStart = 0;
    View view(FloatRect(0, 0, 1366, 768));

    //// heros ////
    list<Player*> heros;
    list<Player*> :: iterator it;

    //// rectangle BEG ////
    RectangleShape rectangle(Vector2f(0, 0));
    rectangle.setSize(Vector2f(0, 0));
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(Color(250, 150, 100));

    bool pressed_rectangle = false;
    //// rectangle END ////

    int pressed_LKM_X;
    int pressed_LKM_Y;

    int released_LKM_X;
    int released_LKM_Y;

    BuildingEnemy EnemyCastle("Building/Enemy's_castle.png", "EnemyCastle", -1300, -500, 256, 206, 5, 0);
    EnemyCastle.create(135, -1300, -500);

    BuildingEnemy boiler("Building/boiler.png", "Boiler", -1100, -600, 128, 80, 5, 0);
    boiler.create(40, -1100, -600);
    boiler.create(40, -1400, -250);

    BuildingEnemy EnemyTower("Building/Enemy's_tower.png", "EnemyTower", -1000, -200, 82, 102, 5, 0);
    EnemyTower.create(55, -1000, -200);

    //// Enemy ////
    list<Enemy*> enemy;
    list<Enemy*> :: iterator itEnemy;
    //enemy.push_back(new Enemy("Images/hero_40x40.png", -1325, -200, 40, 40));
    int Step = 0;

    const char * dbFile = "Data.db";
    Database db(dbFile);

    //char * sqlQuery = "INSERT INTO Map (Name, ID, R, x, y, Radius) VALUES (?, ?, ?, ?, ?, ?);";
    //db.insertData(sqlQuery, "Oleg", 5, 12, 13, 14, 15);
    //char * sqlQuery = "SELECT * FROM Map WHERE Name = ? AND ID = ?;";  //"UPDATE %s SET Name = ?, Surname = ? WHERE ID = ?;"
    //db.getData(sqlQuery, "Castle", 1);

    Vector2i pixelPosWindow;
    Vector2f posWindow;

    Images imagePlayer("Images/hero_40x40.png", 0, 0, 40, 40);

    ////shape////
    /*CircleShape shape(110);
    shape.setFillColor(Color::Transparent);

    shape.setOrigin(110, 110);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(Color(250, 150, 100));
    shape.setPosition(130, 634);*/

    while (!Keyboard::isKeyPressed(Keyboard::Escape))
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        timer += clockTimer.getElapsedTime().asSeconds();

        if(timer > 200) //2000
        {
            if(coins < 1000000000) coins += 10 + cave.getCoins() + building.getCoins() + house.getCoins() + ambar.getCoins();
            sprintf(money, "%i", coins);
            timer = 0;

            for (itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++)
            {
                (*itEnemy)->checkLife(0); // без входных параметров
                if((*itEnemy)->getLife() == 0) enemy.remove(*itEnemy);
            }

            for (it = heros.begin(); it != heros.end(); it++)
            {
                (*it)->checkLife(0); // без входных параметров
                if((*it)->getLife() == 0) heros.remove(*it);
            }

            // Битва между героями
            for (it = heros.begin(); it != heros.end(); it++)
            {
                for (itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++)
                {
                    if((*itEnemy)->checkLife((*it)->getX(), (*it)->getY()) == true)
                    {
                        (*it)->changeLife();
                        if((*it)->getLife() == 0) heros.remove(*it);
                        if((*itEnemy)->getLife() == 0) enemy.remove(*itEnemy);
                    }
                }
            }

            clockTimer.restart();
        }

        if(Step != 200)
        {
            if(Step < 100) Step++;
            else Step = 0;
        }

        if(Step == 1)
        {
            if(enemy.size() < 40)
            {
                enemy.push_back(new Enemy(imagePlayer.sprite, -1320, -220, 40, 40));

                int i = 0;
                int k = 0;

                for(itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++, i++)
                {
                    if(i < 10)
                    {
                        (*itEnemy)->endPosEnemy(-900 + k++ * 40, -600, i);
                        if(k == 10) k = 0;
                    }
                    else if(i >= 10 && i < 20)
                    {
                        (*itEnemy)->endPosEnemy(-900 + k++ * 40, -560, i);
                        if(k == 10) k = 0;
                    }
                    else if(i >= 20 && i < 30)
                    {
                        (*itEnemy)->endPosEnemy(-900 + k++ * 40, -520, i);
                        if(k == 10) k = 0;
                    }
                    else if(i >= 30 && i < 40)
                    {
                        (*itEnemy)->endPosEnemy(-900 + k++ * 40, -480, i);
                        if(k == 10) Step = 200;
                    }
                }
            }
        }

        if(Step == 200)
        {
            if(enemy.size() == 40)
            {
                int i = 0;
                timerStart += clockTimerStart.getElapsedTime().asSeconds();

                if(timerStart > 1000)
                {
                    for(itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++, i++)
                    {
                        (*itEnemy)->endPosEnemy(300, 300, i);
                        clockTimerStart.restart();
                        timerStart = 0;
                    }
                }
            }
        }


        /*
        if(Step == 500)
        {
            int i = 0;
            for (itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++, i++)
            {
                (*itEnemy)->endPosEnemy(-1100, -250, i);
            }
        }
        if(Step == 1000)
        {
            int i = 0;
            for (itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++, i++)
            {
                (*itEnemy)->endPosEnemy(-1200, -300, i);
            }
        }
        if(Step == 1500)
        {
            int i = 0;
            for (itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++, i++)
            {
                (*itEnemy)->endPosEnemy(-1000, -600, i);
            }
            Step = 0;
            enemy.push_back(new Enemy("Images/hero_40x40.png", -1325, -200, 40, 40));
        }
*/

        // Координаты относительно пространства
        Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f pos = window.mapPixelToCoords(pixelPos);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    // Останавливаю прорисовку при движении обьекта ( Сброс обьекта который нажат )
                    isSelect = 0;

                    cave.deleteBuilding();
                    building.deleteBuilding();
                    house.deleteBuilding();
                    fountain.deleteBuilding();
                    tower.deleteBuilding();
                    ambar.deleteBuilding();


                    for (it = heros.begin(); it != heros.end(); it++)
                    {
                        (*it)->stopHero();
                    }

                    for (it = heros.begin(); it != heros.end(); it++)
                    {
                        (*it)->selectHero(pos.x, pos.y);
                    }

                    pressed_rectangle = true;
                    pressed_LKM_X = pos.x;
                    pressed_LKM_Y = pos.y;

                    /*pressed_selection_building = true;

                    // Сброс обьекта который нажат
                    isSelect = 0;

                    cave.deleteBuilding();
                    building.deleteBuilding();
                    house.deleteBuilding();
                    fountain.deleteBuilding();
                    tower.deleteBuilding();
                    ambar.deleteBuilding();

                    // Выбор обьекта который нажат
                    if (pressed_selection == true)
                    {
                        if ( (((pos.x - 603)*(pos.x - 603)) + ((pos.y - 266)*(pos.y - 266))) <= 1225 )
                        {
                            if(coins >= 50)
                            {
                                cave.createAndMove(window, pos.x, pos.y);
                                isSelect = 1;
                            }
                        }
                        else if ( (((pos.x - 747)*(pos.x - 747)) + ((pos.y - 266)*(pos.y - 266))) <= 1225 )
                        {
                            if(coins >= 250)
                            {
                                building.createAndMove(window, pos.x, pos.y);
                                isSelect = 2;
                            }
                        }
                        else if ( (((pos.x - 819)*(pos.x - 819)) + ((pos.y - 384)*(pos.y - 384))) <= 1225 )
                        {
                            if(coins >= 250)
                            {
                                house.createAndMove(window, pos.x, pos.y);
                                isSelect = 3;
                            }
                        }
                        else if ( (((pos.x - 747)*(pos.x - 747)) + ((pos.y - 504)*(pos.y - 504))) <= 1225 )
                        {
                            if(coins >= 1000)
                            {
                                fountain.createAndMove(window, pos.x, pos.y);
                                isSelect = 4;
                            }
                        }
                        else if ( (((pos.x - 603)*(pos.x - 603)) + ((pos.y - 504)*(pos.y - 504))) <= 1225 )
                        {
                            if(coins >= 1000)
                            {
                                tower.createAndMove(window, pos.x, pos.y);
                                isSelect = 5;
                            }
                        }
                        else if ( (((pos.x - 531)*(pos.x - 531)) + ((pos.y - 384)*(pos.y - 384))) <= 1225 )
                        {
                            if(coins >= 450)
                            {
                                ambar.createAndMove(window, pos.x, pos.y);
                                isSelect = 6;
                            }
                        }

                        pressed_selection = false;
                        pressed_selection_building = false;
                    }
                    else if ( (((pos.x - 683)*(pos.x - 683)) + ((pos.y - 410)*(pos.y - 410))) <= 11025 )
                    {
                        pressed_selection = true;
                    }

                    if(pressed_selection_building  == true)
                    {
                        if (indexCave != -1)
                        {
                            if ( (((pos.x - cave.getX(indexCave))*(pos.x  - cave.getX(indexCave))) + ((pos.y - (cave.getY(indexCave) - 50))*(pos.y - (cave.getY(indexCave) - 50)))) <= 950 )
                            {
                                if (coins >= 1000)
                                {
                                    coins -= 1000;
                                    cave.setCoins(indexCave, 10);
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - cave.getX(indexCave))*(pos.x  - cave.getX(indexCave))) + ((pos.y - (cave.getY(indexCave) + 50))*(pos.y - (cave.getY(indexCave) + 50)))) <= 950 )
                            {
                                coins += 25;
                                sprintf(money, "%i", coins);
                                cave.deleteBuildingIndex(indexCave);
                            }

                            // Сброс обьекта "выбор" который нажат
                            indexCave = -1;
                            //indexBuilding = -1;
                            //indexHouse = -1;
                            //indexFountain = -1;
                            //indexTower = -1;
                            //indexAmbar = -1;
                        }
                        else if (indexBuilding != -1)
                        {
                            if ( (((pos.x - building.getX(indexBuilding))*(pos.x  - building.getX(indexBuilding))) + ((pos.y - (building.getY(indexBuilding) - 50))*(pos.y - (building.getY(indexBuilding) - 50)))) <= 950 )
                            {
                                if (coins >= 2000)
                                {
                                    coins -= 2000;
                                    building.setCoins(indexBuilding, 15);
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - building.getX(indexBuilding))*(pos.x  - building.getX(indexBuilding))) + ((pos.y - (building.getY(indexBuilding) + 50))*(pos.y - (building.getY(indexBuilding) + 50)))) <= 950 )
                            {
                                coins += 125;
                                sprintf(money, "%i", coins);
                                building.deleteBuildingIndex(indexBuilding);
                            }

                            // Сброс обьекта "выбор" который нажат
                            //indexCave = -1;
                            indexBuilding = -1;
                            //indexHouse = -1;
                            //indexFountain = -1;
                            //indexTower = -1;
                            //indexAmbar = -1;
                        }
                        else if (indexHouse != -1)
                        {
                            if ( (((pos.x - (house.getX(indexHouse) - 48))*(pos.x  - (house.getX(indexHouse) - 48))) + ((pos.y - (house.getY(indexHouse) - 50))*(pos.y - (house.getY(indexHouse) - 50)))) <= 950 )
                            {//мб сместить на пиксель вверх
                                if (coins >= 1500)
                                {
                                    coins -= 1500;
                                    // to do
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - (house.getX(indexHouse) + 48))*(pos.x  - (house.getX(indexHouse) + 48))) + ((pos.y - (house.getY(indexHouse) - 50))*(pos.y - (house.getY(indexHouse) - 50)))) <= 950 )
                            {//мб сместить на пиксель вверх
                                if (coins >= 1500)
                                {
                                    coins -= 1500;
                                    house.setCoins(indexHouse, 10);
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - house.getX(indexHouse))*(pos.x  - house.getX(indexHouse))) + ((pos.y - (house.getY(indexHouse) + 50))*(pos.y - (house.getY(indexHouse) + 50)))) <= 950 )
                            {
                                coins += 125;
                                sprintf(money, "%i", coins);
                                house.deleteBuildingIndex(indexHouse);
                            }

                            // Сброс обьекта "выбор" который нажат
                            //indexCave = -1;
                            //indexBuilding = -1;
                            indexHouse = -1;
                            //indexFountain = -1;
                            //indexTower = -1;
                            //indexAmbar = -1;
                        }
                        else if (indexFountain != -1)
                        {
                            if ( (((pos.x - fountain.getX(indexFountain))*(pos.x  - fountain.getX(indexFountain))) + ((pos.y - (fountain.getY(indexFountain) - 50))*(pos.y - (fountain.getY(indexFountain) - 50)))) <= 950 )
                            {
                                if (coins >= 2000)
                                {
                                    coins -= 2000;
                                    // to do
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - fountain.getX(indexFountain))*(pos.x  - fountain.getX(indexFountain))) + ((pos.y - (fountain.getY(indexFountain) + 50))*(pos.y - (fountain.getY(indexFountain) + 50)))) <= 950 )
                            {
                                coins += 500;
                                sprintf(money, "%i", coins);
                                fountain.deleteBuildingIndex(indexFountain);
                            }

                            // Сброс обьекта "выбор" который нажат
                            //indexCave = -1;
                            //indexBuilding = -1;
                           // indexHouse = -1;
                            indexFountain = -1;
                            //indexTower = -1;
                            //indexAmbar = -1;
                        }
                        else if (indexTower != -1)
                        {
                            if ( (((pos.x - tower.getX(indexTower))*(pos.x  - tower.getX(indexTower))) + ((pos.y - (tower.getY(indexTower) - 50))*(pos.y - (tower.getY(indexTower) - 50)))) <= 950 )
                            {
                                if (coins >= 2000)
                                {
                                    coins -= 2000;
                                    // to do
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - tower.getX(indexTower))*(pos.x  - tower.getX(indexTower))) + ((pos.y - (tower.getY(indexTower) + 50))*(pos.y - (tower.getY(indexTower) + 50)))) <= 950 )
                            {
                                coins += 500;
                                sprintf(money, "%i", coins);
                                tower.deleteBuildingIndex(indexTower);
                            }

                            // Сброс обьекта "выбор" который нажат
                            //indexCave = -1;
                            //indexBuilding = -1;
                            //indexHouse = -1;
                            //indexFountain = -1;
                            indexTower = -1;
                            //indexAmbar = -1;
                        }
                        else if (indexAmbar != -1)
                        {
                            if ( (((pos.x - (ambar.getX(indexAmbar) - 48))*(pos.x  - (ambar.getX(indexAmbar) - 48))) + ((pos.y - (ambar.getY(indexAmbar) - 50))*(pos.y - (ambar.getY(indexAmbar) - 50)))) <= 950 )
                            {//мб сместить на пиксель вверх
                                if (coins >= 2500)
                                {
                                    coins -= 2500;
                                    // to do
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - (ambar.getX(indexAmbar) + 48))*(pos.x  - (ambar.getX(indexAmbar) + 48))) + ((pos.y - (ambar.getY(indexAmbar) - 50))*(pos.y - (ambar.getY(indexAmbar) - 50)))) <= 950 )
                            {//мб сместить на пиксель вверх
                                if (coins >= 1000)
                                {
                                    coins -= 1000;
                                    // to do
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - ambar.getX(indexAmbar))*(pos.x  - ambar.getX(indexAmbar))) + ((pos.y - (ambar.getY(indexAmbar) + 50))*(pos.y - (ambar.getY(indexAmbar) + 50)))) <= 950 )
                            {
                                coins += 225;
                                sprintf(money, "%i", coins);
                                ambar.deleteBuildingIndex(indexAmbar);
                            }

                            // Сброс обьекта "выбор" который нажат
                            //indexCave = -1;
                            //indexBuilding = -1;
                            //indexHouse = -1;
                            //indexFountain = -1;
                            //indexTower = -1;
                            indexAmbar = -1;
                        }
                        else
                        {
                            // Выбор обьекта "выбор" который нажат
                            indexCave = cave.checkPosition(pos.x, pos.y);
                            indexBuilding = building.checkPosition(pos.x, pos.y);
                            indexHouse = house.checkPosition(pos.x, pos.y);
                            indexTower = tower.checkPosition(pos.x, pos.y);
                            indexFountain = fountain.checkPosition(pos.x, pos.y);
                            indexAmbar = ambar.checkPosition(pos.x, pos.y);
                        }
                    }*/
                }
                else if (event.key.code == Mouse::Right)
                {
                    int i = 0;
                    for (it = heros.begin(); it != heros.end(); it++, i++)
                    {
                        (*it)->endPosHero(pos.x, pos.y, i);
                    }


                    // Вставка обьекта (если можно вставить в даную область карты)
                    if (isSelect == 1)
                    {
                        if (cave.build(41, pos.x, pos.y))
                        {
                            isSelect = 0;
                            coins -= 50;
                            sprintf(money, "%i", coins);
                        }
                    }
                    else if (isSelect == 2)
                    {
                        if (building.build(50, pos.x, pos.y))
                        {
                            isSelect = 0;
                            coins -= 250;
                            sprintf(money, "%i", coins);
                        }
                    }
                    else if (isSelect == 3)
                    {
                        if (house.build(69, pos.x, pos.y))
                        {
                            isSelect = 0;
                            coins -= 250;
                            sprintf(money, "%i", coins);
                        }
                    }
                    else if (isSelect == 4)
                    {
                        if (fountain.build(42, pos.x, pos.y))
                        {
                            isSelect = 0;
                            coins -= 1000;
                            sprintf(money, "%i", coins);
                        }
                    }
                    else if (isSelect == 5)
                    {
                        if (tower.build(53, pos.x, pos.y))
                        {
                            isSelect = 0;
                            coins -= 1000;
                            sprintf(money, "%i", coins);
                        }
                    }
                    else if (isSelect == 6)
                    {
                        if (ambar.build(84, pos.x, pos.y)) // R = 84  увеличил что б рядом размещать войска
                        {
                            isSelect = 0;
                            coins -= 450;
                            sprintf(money, "%i", coins);
                        }
                    }
                }
            }
            else if (event.type == Event::MouseButtonReleased)
            {
                if (event.key.code == Mouse::Left)
                {
                    released_LKM_X = pos.x;
                    released_LKM_Y = pos.y;

                    // Перемещение камеры вида по мини-карте (можно перенести "pos.y < (posWindow.y + 717)" в начальное условие вместе с кругом)
                    //if(pow(pressed_LKM_X - released_LKM_X, 2) + pow(pressed_LKM_Y - released_LKM_Y, 2) < 100) // или эта проверка
                    if(pressed_LKM_X == released_LKM_X && pressed_LKM_Y == released_LKM_Y) // или эта проверка
                    {
                        if(pow(pos.x - (posWindow.x + 130), 2) + pow(pos.y - (posWindow.y + 634), 2) <= 12100)
                        {
                            if(pos.x < (posWindow.x + 95) && pos.y < (posWindow.y + 600)) // tp LU
                            {
                                view.reset(FloatRect(-1500, -850, 1366, 768));
                            }
                            else if(pos.x > (posWindow.x + 165) && pos.y < (posWindow.y + 600)) // tp RU
                            {
                                view.reset(FloatRect(1500, -850, 1366, 768));
                            }
                            else if(pos.x > (posWindow.x + 165) && pos.y > (posWindow.y + 660) && pos.y < (posWindow.y + 717)) // tp RD
                            {
                                view.reset(FloatRect(1500, 850, 1366, 768));
                            }
                            else if(pos.x < (posWindow.x + 95) && pos.y > (posWindow.y + 660) && pos.y < (posWindow.y + 717)) // tp LD
                            {
                                view.reset(FloatRect(-1500, 850, 1366, 768));
                            }
                            else if(pos.x < (posWindow.x + 95) && pos.y < (posWindow.y + 717)) // tp L
                            {
                                view.reset(FloatRect(-1500, 0, 1366, 768));
                            }
                            else if(pos.x > (posWindow.x + 165) && pos.y < (posWindow.y + 717)) // tp R
                            {
                                view.reset(FloatRect(1500, 0, 1366, 768));
                            }
                            else if(pos.y < (posWindow.y + 600)) // tp U
                            {
                                view.reset(FloatRect(0, -850, 1366, 768));
                            }
                            else if(pos.y > (posWindow.y + 660) && pos.y < (posWindow.y + 717)) // tp D
                            {
                                view.reset(FloatRect(0, 850, 1366, 768));
                            }
                            else // tp Centre
                            {
                                if(pos.y < (posWindow.y + 717))
                                {
                                    view.reset(FloatRect(0, 0, 1366, 768));
                                }
                            }
                        }
                    }


                    for (it = heros.begin(); it != heros.end(); it++)
                    {
                        (*it)->selectHero(pressed_LKM_X, pressed_LKM_Y, released_LKM_X, released_LKM_Y);
                    }

                    pressed_rectangle = false;
                    rectangle.setSize(Vector2f(0, 0));
                    window.display();

                    pressed_selection_building = true;

                    // Выбор обьекта который нажат
                    if (pressed_selection == true)
                    {
                        if ( (((pos.x - 603)*(pos.x - 603)) + ((pos.y - 266)*(pos.y - 266))) <= 1225 )
                        {
                            if(coins >= 50)
                            {
                                cave.createAndMove(window, pos.x, pos.y);
                                isSelect = 1;
                            }
                        }
                        else if ( (((pos.x - 747)*(pos.x - 747)) + ((pos.y - 266)*(pos.y - 266))) <= 1225 )
                        {
                            if(coins >= 250)
                            {
                                building.createAndMove(window, pos.x, pos.y);
                                isSelect = 2;
                            }
                        }
                        else if ( (((pos.x - 819)*(pos.x - 819)) + ((pos.y - 384)*(pos.y - 384))) <= 1225 )
                        {
                            if(coins >= 250)
                            {
                                house.createAndMove(window, pos.x, pos.y);
                                isSelect = 3;
                            }
                        }
                        else if ( (((pos.x - 747)*(pos.x - 747)) + ((pos.y - 504)*(pos.y - 504))) <= 1225 )
                        {
                            if(coins >= 1000)
                            {
                                fountain.createAndMove(window, pos.x, pos.y);
                                isSelect = 4;
                            }
                        }
                        else if ( (((pos.x - 603)*(pos.x - 603)) + ((pos.y - 504)*(pos.y - 504))) <= 1225 )
                        {
                            if(coins >= 1000)
                            {
                                tower.createAndMove(window, pos.x, pos.y);
                                isSelect = 5;
                            }
                        }
                        else if ( (((pos.x - 531)*(pos.x - 531)) + ((pos.y - 384)*(pos.y - 384))) <= 1225 )
                        {
                            if(coins >= 450)
                            {
                                ambar.createAndMove(window, pos.x, pos.y);
                                isSelect = 6;
                            }
                        }

                        pressed_selection = false;
                        pressed_selection_building = false;
                    }
                    else if ( (((pos.x - 683)*(pos.x - 683)) + ((pos.y - 410)*(pos.y - 410))) <= 11025 )
                    {
                        pressed_selection = true;
                    }

                    if(pressed_selection_building  == true)
                    {
                        if (indexCave != -1)
                        {
                            if ( (((pos.x - cave.getX(indexCave))*(pos.x  - cave.getX(indexCave))) + ((pos.y - (cave.getY(indexCave) - 50))*(pos.y - (cave.getY(indexCave) - 50)))) <= 950 )
                            {
                                if (coins >= 1000)
                                {
                                    coins -= 1000;
                                    cave.setCoins(indexCave, 10);
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - cave.getX(indexCave))*(pos.x  - cave.getX(indexCave))) + ((pos.y - (cave.getY(indexCave) + 50))*(pos.y - (cave.getY(indexCave) + 50)))) <= 950 )
                            {
                                coins += 25;
                                sprintf(money, "%i", coins);
                                cave.deleteBuildingIndex(indexCave);
                            }

                            // Сброс обьекта "выбор" который нажат
                            indexCave = -1;
                        }
                        else if (indexBuilding != -1)
                        {
                            if ( (((pos.x - building.getX(indexBuilding))*(pos.x  - building.getX(indexBuilding))) + ((pos.y - (building.getY(indexBuilding) - 50))*(pos.y - (building.getY(indexBuilding) - 50)))) <= 950 )
                            {
                                if (coins >= 2000)
                                {
                                    coins -= 2000;
                                    building.setCoins(indexBuilding, 15);
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - building.getX(indexBuilding))*(pos.x  - building.getX(indexBuilding))) + ((pos.y - (building.getY(indexBuilding) + 50))*(pos.y - (building.getY(indexBuilding) + 50)))) <= 950 )
                            {
                                coins += 125;
                                sprintf(money, "%i", coins);
                                building.deleteBuildingIndex(indexBuilding);
                            }

                            // Сброс обьекта "выбор" который нажат
                            indexBuilding = -1;
                        }
                        else if (indexHouse != -1)
                        {
                            if ( (((pos.x - (house.getX(indexHouse) - 48))*(pos.x  - (house.getX(indexHouse) - 48))) + ((pos.y - (house.getY(indexHouse) - 50))*(pos.y - (house.getY(indexHouse) - 50)))) <= 950 )
                            {//мб сместить на пиксель вверх
                                if (coins >= 1500)
                                {
                                    coins -= 1500;
                                    // to do
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - (house.getX(indexHouse) + 48))*(pos.x  - (house.getX(indexHouse) + 48))) + ((pos.y - (house.getY(indexHouse) - 50))*(pos.y - (house.getY(indexHouse) - 50)))) <= 950 )
                            {//мб сместить на пиксель вверх
                                if (coins >= 1500)
                                {
                                    coins -= 1500;
                                    house.setCoins(indexHouse, 10);
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - house.getX(indexHouse))*(pos.x  - house.getX(indexHouse))) + ((pos.y - (house.getY(indexHouse) + 50))*(pos.y - (house.getY(indexHouse) + 50)))) <= 950 )
                            {
                                coins += 125;
                                sprintf(money, "%i", coins);
                                house.deleteBuildingIndex(indexHouse);
                            }

                            // Сброс обьекта "выбор" который нажат
                            indexHouse = -1;
                        }
                        else if (indexFountain != -1)
                        {
                            if ( (((pos.x - fountain.getX(indexFountain))*(pos.x  - fountain.getX(indexFountain))) + ((pos.y - (fountain.getY(indexFountain) - 50))*(pos.y - (fountain.getY(indexFountain) - 50)))) <= 950 )
                            {
                                if (coins >= 2000)
                                {
                                    coins -= 2000;
                                    // to do
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - fountain.getX(indexFountain))*(pos.x  - fountain.getX(indexFountain))) + ((pos.y - (fountain.getY(indexFountain) + 50))*(pos.y - (fountain.getY(indexFountain) + 50)))) <= 950 )
                            {
                                coins += 500;
                                sprintf(money, "%i", coins);
                                fountain.deleteBuildingIndex(indexFountain);
                            }

                            // Сброс обьекта "выбор" который нажат
                            indexFountain = -1;
                        }
                        else if (indexTower != -1)
                        {
                            if ( (((pos.x - tower.getX(indexTower))*(pos.x  - tower.getX(indexTower))) + ((pos.y - (tower.getY(indexTower) - 50))*(pos.y - (tower.getY(indexTower) - 50)))) <= 950 )
                            {
                                if (coins >= 2000) //if (coins >= 2000 && tower.getRadiusTower(indexTower) < 250)
                                {
                                    coins -= 2000;
                                    // to do //tower.setRadiusTower(indexTower, 10);
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - tower.getX(indexTower))*(pos.x  - tower.getX(indexTower))) + ((pos.y - (tower.getY(indexTower) + 50))*(pos.y - (tower.getY(indexTower) + 50)))) <= 950 )
                            {
                                coins += 500;
                                sprintf(money, "%i", coins);
                                tower.deleteBuildingIndex(indexTower);
                            }

                            // Сброс обьекта "выбор" который нажат
                            indexTower = -1;
                        }
                        else if (indexAmbar != -1)
                        {
                            if ( (((pos.x - (ambar.getX(indexAmbar) - 48))*(pos.x  - (ambar.getX(indexAmbar) - 48))) + ((pos.y - (ambar.getY(indexAmbar) - 50))*(pos.y - (ambar.getY(indexAmbar) - 50)))) <= 950 )
                            {//мб сместить на пиксель вверх
                                if (coins >= 2500)
                                {
                                    coins -= 2500;
                                    // to do
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - (ambar.getX(indexAmbar) + 48))*(pos.x  - (ambar.getX(indexAmbar) + 48))) + ((pos.y - (ambar.getY(indexAmbar) - 50))*(pos.y - (ambar.getY(indexAmbar) - 50)))) <= 950 )
                            {//мб сместить на пиксель вверх
                                if (coins >= 1000)
                                {
                                    coins -= 1000;
                                    heros.push_back(new Player(imagePlayer.sprite, "Heros", heros.size(), ambar.getX(indexAmbar) + 150, ambar.getY(indexAmbar), 40, 40)); // место где будут размещаться новые войска при создании
                                    heros.push_back(new Player(imagePlayer.sprite, "Heros", heros.size(), ambar.getX(indexAmbar) + 150, ambar.getY(indexAmbar) + 40, 40, 40));
                                    // можно добавить еще пару юнитов
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - ambar.getX(indexAmbar))*(pos.x  - ambar.getX(indexAmbar))) + ((pos.y - (ambar.getY(indexAmbar) + 50))*(pos.y - (ambar.getY(indexAmbar) + 50)))) <= 950 )
                            {
                                coins += 225;
                                sprintf(money, "%i", coins);
                                ambar.deleteBuildingIndex(indexAmbar);
                            }

                            // Сброс обьекта "выбор" который нажат
                            indexAmbar = -1;
                        }
                        else
                        {
                            // Выбор обьекта "выбор" который нажат
                            indexCave = cave.checkPosition(pos.x, pos.y);
                            indexBuilding = building.checkPosition(pos.x, pos.y);
                            indexHouse = house.checkPosition(pos.x, pos.y);
                            indexTower = tower.checkPosition(pos.x, pos.y);
                            indexFountain = fountain.checkPosition(pos.x, pos.y);
                            indexAmbar = ambar.checkPosition(pos.x, pos.y);
                        }
                    }

                }
            }
        }

        if (pos.x > -1500 && pos.x < 2866 && pos.y > -850 && pos.y < 1618)
        {
            if (pixelPos.x >= 1365)
            {
                view.move(0.3*time, 0);
            }
            if (pixelPos.y >= 767)
            {
                view.move(0, 0.3*time);
            }
            if (pixelPos.x <= 0)
            {
                view.move(-0.3*time, 0);
            }
            if (pixelPos.y <= 0)
            {
                view.move(0, -0.3*time);
            }
        }

        window.clear();
        window.setView(view);
        window.draw(background.sprite);

        // Разметка границ карты
        Vertex lineBorder[] =
        {
            Vertex(Vector2f(-1475, -750), Color::Red),
            Vertex(Vector2f(-1475, 1593), Color::Red),

            Vertex(Vector2f(2841, -750), Color::Red),
            Vertex(Vector2f(2841, 1593), Color::Red),

            Vertex(Vector2f(-1475, -750), Color::Red),
            Vertex(Vector2f(2841, -750), Color::Red),

            Vertex(Vector2f(-1475, 1593), Color::Red),
            Vertex(Vector2f(2841, 1593), Color::Red)
        };
        window.draw(lineBorder, 8, Lines);

        window.draw(castle.sprite);

        // Прорисовка обьектов
        cave.moveAndDraw(window, 41, pos.x, pos.y);
        building.moveAndDraw(window, 50, pos.x, pos.y);
        house.moveAndDraw(window, 69, pos.x, pos.y);
        fountain.moveAndDraw(window, 42, pos.x, pos.y);
        tower.moveAndDraw(window, 53, pos.x, pos.y);
        ambar.moveAndDraw(window, 220, pos.x, pos.y); // R = 84  увеличил что б рядом размещать войска

        // Вражеские строения
        EnemyCastle.draw(window);
        boiler.draw(window);
        EnemyTower.draw(window);

        for (it = heros.begin(); it != heros.end(); it++)
        {
			(*it)->updateHero(time);
		}

        if (pressed_rectangle == true)
        {
            rectangle.setPosition(pressed_LKM_X, pressed_LKM_Y);
            rectangle.setSize(Vector2f(pos.x - pressed_LKM_X, pos.y - pressed_LKM_Y));
        }

        for (it = heros.begin(); it != heros.end(); it++)
        {
			(*it)->drawHero(window);
		}

        ////// Enemy
        for (itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++)
        {
			(*itEnemy)->updateEnemy(time);
		}
        for (itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++)
        {
			(*itEnemy)->drawEnemy(window);
		}
        ////// Enemy

        window.draw(rectangle);

        // Прорисовка обьекта "выбор" при нажатии на обьект
        if((pressed_selection_building  == true) && (pow(pressed_LKM_X - released_LKM_X, 2) + pow(pressed_LKM_Y - released_LKM_Y, 2) < 100))
        {   // делано для того что бы при выдилением квадратом не выбирался обьект // возможно эту проверку: pressed_LKM_X == released_LKM_X && pressed_LKM_Y == released_LKM_Y
            if (indexCave != -1)
            {
                selection2.sprite.setPosition(cave.getX(indexCave), cave.getY(indexCave));
                window.draw(selection2.sprite);

                if (coins < 1000)
                {
                    selectionNot.x = cave.getX(indexCave);
                    selectionNot.y = cave.getY(indexCave) - 50;
                    selectionNot.sprite.setPosition(selectionNot.x, selectionNot.y);
                    window.draw(selectionNot.sprite);
                }
            }
            if (indexBuilding != -1)
            {
                selection2.sprite.setPosition(building.getX(indexBuilding), building.getY(indexBuilding));
                window.draw(selection2.sprite);

                if (coins < 2000)
                {
                    selectionNot.x = building.getX(indexBuilding);
                    selectionNot.y = building.getY(indexBuilding) - 50;
                    selectionNot.sprite.setPosition(selectionNot.x, selectionNot.y);
                    window.draw(selectionNot.sprite);
                }
            }
            if (indexHouse != -1)
            {
                selection3House.sprite.setPosition(house.getX(indexHouse), house.getY(indexHouse));
                window.draw(selection3House.sprite);

                if (coins < 1500)
                {
                    selectionNot.x = house.getX(indexHouse) - 48;
                    selectionNot.y = house.getY(indexHouse) - 50;
                    selectionNot.sprite.setPosition(selectionNot.x, selectionNot.y);
                    window.draw(selectionNot.sprite);

                    selectionNotAddition.x = house.getX(indexHouse) + 48;
                    selectionNotAddition.y = house.getY(indexHouse) - 50;
                    selectionNotAddition.sprite.setPosition(selectionNotAddition.x, selectionNotAddition.y);
                    window.draw(selectionNotAddition.sprite);
                }
            }
            if (indexFountain != -1)
            {
                selection2.sprite.setPosition(fountain.getX(indexFountain), fountain.getY(indexFountain));
                window.draw(selection2.sprite);

                if (coins < 2000)
                {
                    selectionNot.x = fountain.getX(indexFountain);
                    selectionNot.y = fountain.getY(indexFountain) - 50;
                    selectionNot.sprite.setPosition(selectionNot.x, selectionNot.y);
                    window.draw(selectionNot.sprite);
                }
            }
            if (indexTower != -1)
            {
                selection2.sprite.setPosition(tower.getX(indexTower), tower.getY(indexTower));
                window.draw(selection2.sprite);

                if (coins < 2000) //if (coins < 2000 || tower.getRadiusTower(indexTower) == 250)
                {
                    selectionNot.x = tower.getX(indexTower);
                    selectionNot.y = tower.getY(indexTower) - 50;
                    selectionNot.sprite.setPosition(selectionNot.x, selectionNot.y);
                    window.draw(selectionNot.sprite);
                }
            }
            if (indexAmbar != -1)
            {
                selection3Ambar.sprite.setPosition(ambar.getX(indexAmbar), ambar.getY(indexAmbar));
                window.draw(selection3Ambar.sprite);

                if (coins < 2500)
                {
                    selectionNot.x = ambar.getX(indexAmbar) - 48;
                    selectionNot.y = ambar.getY(indexAmbar) - 50;
                    selectionNot.sprite.setPosition(selectionNot.x, selectionNot.y);
                    window.draw(selectionNot.sprite);
                }

                if (coins < 1000)
                {
                    selectionNotAddition.x = ambar.getX(indexAmbar) + 48;
                    selectionNotAddition.y = ambar.getY(indexAmbar) - 50;
                    selectionNotAddition.sprite.setPosition(selectionNotAddition.x, selectionNotAddition.y);
                    window.draw(selectionNotAddition.sprite);
                }
            }
        }

        // Прорисовка обьекта "выбор" при нажатии на обьект "Замок"
        if((pressed_selection == true) && (pow(pressed_LKM_X - released_LKM_X, 2) + pow(pressed_LKM_Y - released_LKM_Y, 2) < 100)) // pressed_LKM_X == released_LKM_X && pressed_LKM_Y == released_LKM_Y
        {   // делано для того что бы при выдилением квадратом не выбирался Замок // возможно эту проверку: pressed_LKM_X == released_LKM_X && pressed_LKM_Y == released_LKM_Y
            window.draw(selection.sprite);

            if(cave.getIndex() == 4)
            {
                selectionNot1.sprite.setColor(Color::Black);
                window.draw(selectionNot1.sprite);
            }
            else if(coins < 50)
            {
                selectionNot1.sprite.setColor(Color::White);
                window.draw(selectionNot1.sprite);
            }

            if(building.getIndex() == 4)
            {
                selectionNot2.sprite.setColor(Color::Black);
                window.draw(selectionNot2.sprite);
            }
            else if(coins < 250)
            {
                selectionNot2.sprite.setColor(Color::White);
                window.draw(selectionNot2.sprite);
            }

            if(house.getIndex() == 4)
            {
                selectionNot3.sprite.setColor(Color::Black);
                window.draw(selectionNot3.sprite);
            }
            else if(coins < 250)
            {
                selectionNot3.sprite.setColor(Color::White);
                window.draw(selectionNot3.sprite);
            }

            if(fountain.getIndex() == 4)
            {
                selectionNot4.sprite.setColor(Color::Black);
                window.draw(selectionNot4.sprite);
            }
            else if(coins < 1000)
            {
                selectionNot4.sprite.setColor(Color::White);
                window.draw(selectionNot4.sprite);
            }

            if(tower.getIndex() == 4)
            {
                selectionNot5.sprite.setColor(Color::Black);
                window.draw(selectionNot5.sprite);
            }
            else if(coins < 1000)
            {
                selectionNot5.sprite.setColor(Color::White);
                window.draw(selectionNot5.sprite);
            }

            if(ambar.getIndex() == 4)
            {
                selectionNot6.sprite.setColor(Color::Black);
                window.draw(selectionNot6.sprite);
            }
            else if(coins < 450)
            {
                selectionNot6.sprite.setColor(Color::White);
                window.draw(selectionNot6.sprite);
            }
        }


        // Координаты относительно экрана
        pixelPosWindow = window.getPosition();
        posWindow = window.mapPixelToCoords(pixelPosWindow);

        miniMap.sprite.setPosition(posWindow.x, posWindow.y + 510);
        window.draw(miniMap.sprite);

        text.setColor(Color::White);
        text.setString(money);
        text.setPosition(posWindow.x + 53, posWindow.y + 721);
        window.draw(text);

        // Разметки на мини-карте
        Vertex lineMiniMap[] =
        {
            Vertex(Vector2f(posWindow.x + 95, posWindow.y + 531)),
            Vertex(Vector2f(posWindow.x + 95, posWindow.y + 716)),

            Vertex(Vector2f(posWindow.x + 165, posWindow.y + 530)),
            Vertex(Vector2f(posWindow.x + 165, posWindow.y + 716)),

            Vertex(Vector2f(posWindow.x + 26, posWindow.y + 600)),
            Vertex(Vector2f(posWindow.x + 235, posWindow.y + 600)),

            Vertex(Vector2f(posWindow.x + 22, posWindow.y + 660)),
            Vertex(Vector2f(posWindow.x + 238, posWindow.y + 660))
        };
        window.draw(lineMiniMap, 8, Lines);

        window.display();
    }

    char * sqlQueryMap = "DELETE FROM Map WHERE Name <> ?;";
    db.clearData(sqlQueryMap); // очищаем все обьекты с базы данных, кроме главного Замка
    char * sqlQueryPlayer = "DELETE FROM Player;";
    db.clearData(sqlQueryPlayer); // очищаем всех персонажей с базы данных
}

int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "Menu", Style::Fullscreen);
    window.setFramerateLimit(50);

    menu(window);

    window.close();
    return 0;
}

/*
void renderingThread(sf::RenderWindow* window)
{
     ////shape////
    CircleShape shape(50);
    shape.setFillColor(Color::Transparent);

    shape.setOrigin(50, 50);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(Color(250, 150, 100));
    shape.setPosition(150, 150);
    // цикл визуализации
    int i = 0;
    while (window->isOpen())
    {
    // рисуем...
    window->clear();
    //Sleep(1000);
    shape.setPosition(150, 150);
    window->draw(shape);
    // конец текущего кадра
    window->display();
    }
}

int main()
{
     // создаём окно (помните: безопаснее всего создавать его в главном потоке из за ограничений ОС)
     sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL");

     // деактивируем контекст OpenGL
     window.setActive(false);

     // запуск визуализации в потоке
     sf::Thread thread(&renderingThread, &window);
     thread.launch();
        int i = 0;
     // цикл обработки событий, логики и прочего..
     while (window.isOpen())
     {
       Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        cout<<i++<<endl;
     }

    return 0;
}*/
