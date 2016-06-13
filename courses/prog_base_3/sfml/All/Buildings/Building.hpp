#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "../Images/Images.hpp"
#include "../Database/Database.hpp"
/*
class ImagesBuild : public Images
{
public:
    bool isMove;
    bool isCreate;
    bool isLive;
    int life;

    Sprite scaleUpdate;

    int coins;
    int startCoins;
    int deltaArmor; // только для House
    int Radius;

    ImagesBuild(Sprite & spr, Sprite & scaleUpdate, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int coins = 0) :
    Images(spr, positionX, positionY, width, height, Radius) {}

    void setPosition(int Radius, int posX, int posY);
};

class Building
{
public:
    ImagesBuild ** building;

    char Name[20];
    Database * db;

    int maxCount;
    int index;

    Building(Sprite & spr, Sprite & scaleUpdate, const char * name, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int maxCount = 0, int coins = 0);
    ~Building();

    void changeLife(int i);
    void checkLife(int posX, int posY);
    int checkPosition(int posX, int posY);
    int getX(int i);
    int getY(int i);
    void createAndMove(RenderWindow & window, int posX, int posY);
    void deleteBuildingIndex(int indexBuilding);
    void deleteBuilding();
    bool build(int Radius, int posX, int posY);
    void moveAndDraw(RenderWindow & window, int Radius, int posX, int posY);
    void drawScale(RenderWindow & window);
    void setCoins(int indexBuilding, int newCoins);
    int getCoinsByID(int indexBuilding);
    int getCoins();
    int getIndex();
    void setDeltaArmor(int i, int deltaArmor);
    int getDeltaArmor(int i);
    void setRadius(int i, int Radius);
    int getRadius(int i);
};

class BuildingEnemy
{
public:
    ImagesBuild ** building;

    char Name[20];
    Database * db;

    int maxCount;
    int index ;

    BuildingEnemy(Sprite & spr, Sprite & scaleUpdate,  const char * name, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int maxCount = 0, int coins = 0);
    ~BuildingEnemy();

    void changeLife(int i);
    void checkLife(int posX, int posY);
    int getX(int i);
    int getY(int i);
    void create(int Radius, int posX, int posY);
    void deleteBuildingIndex(int indexBuilding);
    void deleteBuilding();
    bool build(int Radius, int posX, int posY);
    int getIndex();
    void draw(RenderWindow & window);
};
*/

#endif

