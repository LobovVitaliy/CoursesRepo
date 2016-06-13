#include "ImagesBuild.hpp"

ImagesBuild:: ImagesBuild(Sprite & spr, Sprite & scaleUpdate, int positionX, int positionY, int width, int height, int coins) :
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

void ImagesBuild:: setPosition(int Radius, int posX, int posY)
{
    R = Radius;
    x = posX;
    y = posY;
}
