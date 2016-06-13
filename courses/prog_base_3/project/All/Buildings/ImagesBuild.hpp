#ifndef IMAGESBUILD_HPP
#define IMAGESBUILD_HPP

#include "../Images/Images.hpp"
#include "../Database/Database.hpp"

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

    ImagesBuild(Sprite & spr, Sprite & scaleUpdate, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int coins = 0);

    void setPosition(int Radius, int posX, int posY);
};

#endif
