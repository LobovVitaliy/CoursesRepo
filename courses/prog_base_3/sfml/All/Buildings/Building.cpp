/*#include "Building.hpp"

ImagesBuild:: ImagesBuild(Sprite & spr, Sprite & scaleUpdate, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int coins = 0) :
Images(spr, positionX, positionY, width, height, Radius)
{
    this->scaleUpdate = scaleUpdate;
    this->isMove = false;
    this->isCreate = false;
    this->isLive = false;
    this->coins = coins;
    this->startCoins = coins;
    this->deltaArmor = 1;
    this->life = 10;
}

ImagesBuild:: void setPosition(int Radius, int posX, int posY)
{
    R = Radius;
    x = posX;
    y = posY;
}


Building:: Building(Sprite & spr, Sprite & scaleUpdate, const char * name, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int maxCount = 0, int coins = 0)
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

Building:: ~Building()
{
    for (int i = 0; i < maxCount; i++)
    {
        delete building[i];
    }
    delete [] building;
    delete db;
}


void Building:: changeLife(int i)
{
    building[i]->life--;
    if(building[i]->life == 0)
    {
        building[i]->isLive = false;
        deleteBuildingIndex(i);
    }
}

void Building:: checkLife(int posX, int posY)
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



int Building:: checkPosition(int posX, int posY)
{
    for(int i = 0; i < index + 1; i++) // раньше было до maxCount, при удалени обьекта оставалс€ выбор его улучшений
    {
        if ( (((posX - building[i]->x)*(posX - building[i]->x)) + ((posY - building[i]->y)*(posY - building[i]->y))) <= (building[i]->R)*(building[i]->R) )
        {
            return i;
        }
    }
    return -1;
}

int Building:: getX(int i)
{
    if (building[i]->isLive)
        return building[i]->x;
    else
        return 5000;
}

int Building:: getY(int i)
{
    if (building[i]->isLive)
        return building[i]->y;
    else
        return 5000;
}

void Building:: createAndMove(RenderWindow & window, int posX, int posY)
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

void Building:: deleteBuildingIndex(int indexBuilding) // db // change
{
    char sqlQuery[] = "DELETE FROM Map WHERE Name = ? AND ID = ?;";
    db->deleteData(sqlQuery, Name, indexBuilding); // change

    int x, y, w, h, R, coins, deltaArmor, life;
    bool isMove, isCreate, isLive;

    Image image;
    Texture texture;
    Sprite sprite;

    char sqlQueryUp[] = "UPDATE Map SET ID = ? WHERE Name = ? AND ID = ?;";

    // значени€ которые измен€ютс€ в течение игры
    building[indexBuilding]->deltaArmor = 1;
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

void Building:: deleteBuilding()
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

bool Building:: build(int Radius, int posX, int posY) // db
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
                db->insertData(sqlQuery, Name, index, Radius, posX, posY, 100);
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

void Building:: moveAndDraw(RenderWindow & window, int Radius, int posX, int posY) // db // change
{
    for(int i = 0; i < maxCount; i++)
    {
        if (building[i]->isCreate)
        {
            if (building[index]->isMove)
            {
                //  руг вокруг строени€
                CircleShape shape(Radius);
                shape.setFillColor(Color::Transparent);

                shape.setOrigin(Radius, Radius);
                shape.setOutlineThickness(2);
                shape.setOutlineColor(Color(194, 228, 228));
                shape.setPosition(posX, posY);

                window.draw(shape);

                building[index]->sprite.setPosition(posX, posY);

                char sqlQuery[] = "SELECT * FROM Map;";
                for(int j = 0; j < db->count("SELECT COUNT(*) FROM Map;"); j++)
                {
                    db->getDataByIndex(sqlQuery, j);
                    if(strcmp(db->Name, "Ambar") == 0) db->R = db->Radius; // change

                    // ѕровер€ем краи карты и ближайшие обьекты на карте
                    if (posX < -300 + Radius || posX > 2841 - Radius || posY < -750 + Radius || posY > 1593 - Radius) // posX < -1475
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
            }

            window.draw(building[i]->sprite);
        }
    }
}

void Building:: drawScale(RenderWindow & window)
{
    for(int i = 0; i < index + 1; i++)
    {
        if (building[i]->isMove == false)
        {
            int R = 0;
            if(strcmp(Name, "Cave") == 0) R = -10;
            else if(strcmp(Name, "House") == 0) R = 10;
            else if(strcmp(Name, "Ambar") == 0) R = 20;

            building[i]->scaleUpdate.setPosition(building[i]->x, building[i]->y - R);
            building[i]->scaleUpdate.setTextureRect(IntRect(0, 14 * (10 - building[i]->life), 112, 14));
            window.draw(building[i]->scaleUpdate);
        }
    }
}

void Building:: setCoins(int indexBuilding, int newCoins)
{
    building[indexBuilding]->coins += newCoins;
}

int Building:: getCoinsByID(int indexBuilding)
{
    return building[indexBuilding]->coins;
}

int Building:: getCoins()
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

int Building:: getIndex()
{
    return index;
}

void Building:: setDeltaArmor(int i, int deltaArmor)
{
    building[i]->deltaArmor = deltaArmor;
}

int Building:: getDeltaArmor(int i)
{
    if (building[i]->isLive) return building[i]->deltaArmor;
    return 0;
}


void Building:: setRadius(int i, int Radius)
{
    char sqlQuery[] = "UPDATE Map SET Radius = ? WHERE Name = ? AND ID = ?;";
    building[i]->Radius = Radius;
    db->updateDataRadius(sqlQuery, Name, i, Radius);
}

int Building:: getRadius(int i)
{
    char sqlQuery[] = "SELECT * FROM Map WHERE Name = ? AND ID = ?;";
    db->getData(sqlQuery, Name, i);
    return db->Radius;
}


BuildingEnemy:: BuildingEnemy(Sprite & spr, Sprite & scaleUpdate,  const char * name, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int maxCount = 0, int coins = 0)
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

    // значени€ которые измен€ютс€ в течение игры
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
*/
