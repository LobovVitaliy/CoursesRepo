#include "BuildingEnemy.hpp"

BuildingEnemy:: BuildingEnemy(Sprite & spr, Sprite & scaleUpdate,  const char * name, int positionX, int positionY, int width, int height, int maxCount, int coins)
{
    strcpy(this->Name, name);
    this->db = new Database("Data.db");
    this->maxCount = maxCount;
    this->building = new ImagesBuild* [maxCount];
    this->index = -1;

    for(int i = 0; i < maxCount; i++)
    {
        building[i] = new ImagesBuild(spr, scaleUpdate, positionX, positionY, width, height, coins);
    }
}

BuildingEnemy:: ~BuildingEnemy()
{
    for (int i = 0; i < maxCount; i++)
    {
        delete building[i];
    }
    delete [] building;
    delete db;
}

void BuildingEnemy:: changeLife(int i)
{
    building[i]->life--;
    if(building[i]->life == 0)
    {
        building[i]->isLive = false;
        deleteBuildingIndex(i);
    }
}

void BuildingEnemy:: checkLife(int posX, int posY)
{
    for(int i = 0; i < index + 1; i++)
    {
        char sqlQuery[] = "SELECT * FROM Map WHERE Name = ? AND ID = ?;";
        db->getData(sqlQuery, Name, i);

        if(pow(posX - db->x, 2) + pow(posY - db->y, 2) <= pow(db->R + 20 + 30, 2))
        {
            changeLife(i);
            //break; // ?
        }
    }
}

int BuildingEnemy:: getX(int i)
{
    return building[i]->x;
}

int BuildingEnemy:: getY(int i)
{
    return building[i]->y;
}

void BuildingEnemy:: create(int Radius, int posX, int posY)
{
    if (index < maxCount - 1)
    {
        index++;
        building[index]->isLive = true;
        building[index]->isCreate = true;
        building[index]->sprite.setPosition(posX, posY);
        building[index]->setPosition(Radius, posX, posY);

        char sqlQuery[] = "INSERT INTO Map (Name, ID, R, x, y, Radius) VALUES (?, ?, ?, ?, ?, ?);";

        if(strcmp(Name, "EnemyTower") == 0)
        {
            db->insertData(sqlQuery, Name, index, Radius, posX, posY, 200);
        }
        else
        {
            db->insertData(sqlQuery, Name, index, Radius, posX, posY, 0);
        }
    }
}

void BuildingEnemy:: deleteBuildingIndex(int indexBuilding) // db // change
{
    char sqlQuery[] = "DELETE FROM Map WHERE Name = ? AND ID = ?;";
    db->deleteData(sqlQuery, Name, indexBuilding); // change

    int x, y, w, h, R, coins, deltaArmor, life;
    bool isMove, isCreate, isLive;

    Image image;
    Texture texture;
    Sprite sprite;

    char sqlQueryUp[] = "UPDATE Map SET ID = ? WHERE Name = ? AND ID = ?;";

    // значения которые изменяются в течение игры
    building[indexBuilding]->life = 10;
    building[indexBuilding]->coins = building[indexBuilding]->startCoins;

    for(int i = indexBuilding; i < index; i++)
    {
        ////////////////////////////////////////////
        x = building[i + 1]->x;
        y = building[i + 1]->y;
        w = building[i + 1]->w;
        h = building[i + 1]->h;
        R = building[i + 1]->R;
        coins = building[i + 1]->coins;
        deltaArmor = building[i + 1]->deltaArmor;
        life = building[i + 1]->life;

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
        building[i]->deltaArmor = deltaArmor;
        building[i]->life = life;

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

void BuildingEnemy:: deleteBuilding()
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

bool BuildingEnemy:: build(int Radius, int posX, int posY) // db
{
    if(index > -1)
    {
        if(building[index]->isLive)
        {
            building[index]->isMove = false;
            building[index]->setPosition(Radius, posX, posY);

            char sqlQuery[] = "INSERT INTO Map (Name, ID, R, x, y, Radius) VALUES (?, ?, ?, ?, ?, ?);";

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

int BuildingEnemy:: getIndex()
{
    return index;
}

void BuildingEnemy:: draw(RenderWindow & window)
{
    for(int i = 0; i < index + 1; i++)
    {
        int R = 0;
        if(strcmp(Name, "EnemyCastle") == 0) R = 60;

        building[i]->scaleUpdate.setPosition(building[i]->x, building[i]->y - R);
        building[i]->scaleUpdate.setTextureRect(IntRect(0, 14 * (10 - building[i]->life), 112, 14));
        window.draw(building[i]->scaleUpdate);

        window.draw(building[i]->sprite);
    }
}
