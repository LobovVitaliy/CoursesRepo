#include "Player.hpp"

Player:: Player(Sprite & spr, Sprite & scaleUpdate, Sprite & scaleArmor, Database & db, const char * name, int ID, int positionX, int positionY, int width, int height, int Radius) :
Unit(spr, scaleUpdate, db, positionX, positionY, width, height, Radius)
{
    strcpy(this->Name, name);
    this->scaleArmor = scaleArmor;
    this->armor = 0;
}

void Player:: changeLife()
{
    if(armor == 0)
    {
        life--;
    }
    else
    {
        armor--;
    }

    if(life == 0) isLive = false;
}

void Player:: checkLife(int RadiusTower)
{
    char sqlQuery[] = "SELECT * FROM Map;";
    for(int j = 0; j < db.count("SELECT COUNT(*) FROM Map;"); j++)
    {
        db.getDataByIndex(sqlQuery, j);
        if(strcmp(db.Name, "EnemyTower") == 0)
        {
            if(pow(x - db.x, 2) + pow(y - db.y, 2) <= pow(db.Radius, 2))
            {
                changeLife();
                //break; // без break, так как при установки нескольких башень урон сумируется
            }
        }
        else if(strcmp(db.Name, "Fountain") == 0)
        {
            if(pow(x - db.x, 2) + pow(y - db.y, 2) <= pow(db.Radius, 2))
            {
                if(life < 3) life++;
                break;
            }
        }
    }
}

void Player:: setArmor(int armor)
{
    this->armor += armor;
    if(this->armor > 3) this->armor = 3;
}

int Player:: getArmor()
{
    return armor;
}

void Player:: stopHero()
{
    isSelect = false;
    sprite.setColor(Color::White);
}

void Player:: selectHero(int posX, int posY)
{
    if(isLive == true)
    {
        if(pow((posX - x), 2) + pow((posY - y), 2) <= pow(R, 2))
        {
            isSelect = true;
            sprite.setColor(Color::Red);
        }
    }
}

void Player::selectHero(int pressed_LKM_X, int pressed_LKM_Y, int released_LKM_X, int released_LKM_Y)
{
    if(isLive == true)
    {
        if(((pressed_LKM_X <= x) && (x <= released_LKM_X) && (pressed_LKM_Y <= y) && (y <= released_LKM_Y))
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

void Player::endPosHero(int posX, int posY, int index)
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

void Player:: updateHero(float time)
{
    if(isLive == true) movement(time);
}

void Player:: drawHero(RenderWindow & window)
{
    if(isLive == true)
    {
        if(armor != 0)
        {
            scaleArmor.setPosition(x + 17, y - 32);
            scaleArmor.setTextureRect(IntRect(18 * (3 - armor), 0, 18, 7));
            window.draw(scaleArmor);
        }

        scaleUpdate.setPosition(x + 17, y - 25);
        scaleUpdate.setTextureRect(IntRect(18 * (3 - life), 0, 18, 7));
        window.draw(scaleUpdate);

        window.draw(sprite);
    }
}

