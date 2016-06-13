#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Unit.hpp"

class Player : public Unit
{
public:

    char Name[20];
    int armor;
    Sprite scaleArmor;

    Player(Sprite & spr, Sprite & scaleUpdate, Sprite & scaleArmor, Database & db, const char * name, int ID, int positionX, int positionY, int width, int height, int Radius = 20);

    void changeLife();
    void checkLife(int RadiusTower);
    void setArmor(int armor);
    int getArmor();
    void stopHero();
    void selectHero(int posX, int posY);
    void selectHero(int pressed_LKM_X, int pressed_LKM_Y, int released_LKM_X, int released_LKM_Y);
    void endPosHero(int posX, int posY, int index);
    void updateHero(float time);
    void drawHero(RenderWindow & window);
};

#endif
