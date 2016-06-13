#ifndef BUILDINGENEMY_HPP
#define BUILDINGENEMY_HPP

#include "ImagesBuild.hpp"

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

#endif
