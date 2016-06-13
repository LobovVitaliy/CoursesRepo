#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Unit.hpp"

class Enemy : public Unit
{
public:

    Enemy(Sprite & spr, Sprite & scaleUpdate, Database & db, int positionX, int positionY, int width, int height, int Radius = 20);

    void changeLife();
    void checkLife();
    bool checkLife(int posX, int posY);
    void endPosEnemy(int posX, int posY, int index);
    void updateEnemy(float time);
    void drawEnemy(RenderWindow & window);
};

#endif
