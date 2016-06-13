#include "Enemy.hpp"

Enemy:: Enemy(Sprite & spr, Sprite & scaleUpdate, Database & db, int positionX, int positionY, int width, int height, int Radius) :
Unit(spr, scaleUpdate, db, positionX, positionY, width, height, Radius)
{
    this->sprite.setColor(Color(80, 80, 80));
}

void Enemy:: changeLife()
{
    life--;
    if(life == 0) isLive = false;
}

void Enemy:: checkLife()
{
    char sqlQuery[] = "SELECT * FROM Map;";
    for(int j = 0; j < db.count("SELECT COUNT(*) FROM Map;"); j++)
    {
        db.getDataByIndex(sqlQuery, j);
        if(strcmp(db.Name, "Tower") == 0)
        {
            if(pow(x - db.x, 2) + pow(y - db.y, 2) <= pow(db.Radius, 2))
            {
                changeLife();
                //break; // без break, так как при установки нескольких башень урон сумируется
            }
        }
    }
}

bool Enemy::checkLife(int posX, int posY)
{
    if(pow(posX - x, 2) + pow(posY - y, 2) <= 2500)
    {
        changeLife();
        return true;
    }
    return false;
}

void Enemy:: endPosEnemy(int posX, int posY, int index)
{
    if(isLive == true)
    {
        heroCleaning("enemy.txt", index);
        isMove = true;

        while(checkPos("enemy.txt", posX, posY, index) == false)
        {
            int vX = -1 + rand() % 2;
            posX += vX * (20 + rand() % 10);
            int vY = -1 + rand() % 2;
            posY += vY * (20 + rand() % 10);
        }

        endX = posX;
        endY = posY;

        mouseRight();
        saveHero("enemy.txt", index, R, endX, endY);
    }
}

void Enemy:: updateEnemy(float time)
{
    if(isLive == true) movement(time);
}

void Enemy:: drawEnemy(RenderWindow & window)
{
    if(isLive == true)
    {
        scaleUpdate.setPosition(x + 17, y - 25);
        scaleUpdate.setTextureRect(IntRect(18 * (3 - life), 0, 18, 7));
        window.draw(scaleUpdate);
        window.draw(sprite);
    }
}

