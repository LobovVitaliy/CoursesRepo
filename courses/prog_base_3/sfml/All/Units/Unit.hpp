#ifndef UNIT_HPP
#define UNIT_HPP

#include <cmath>

#include "../Images/Images.hpp"
#include "../Database/Database.hpp"

class Unit : public Images
{
public:

    int begX, begY;
    int endX, endY;
    int dx, dy;
    float angle;
    int stopAngle;

    int life;
    bool isMove, isSelect, isLive;
    float CurrentFrame;

    Sprite scaleUpdate;
    Database db;

    Unit(Sprite & spr, Sprite & scaleUpdate, Database & db, int positionX, int positionY, int width, int height, int Radius = 20);

    void update(float time, int numImage, int posX, int posY);
    void stop();
    void movement(float time);
    void mouseRight();
    int getLife();
    int getX();
    int getY();
};

#endif
