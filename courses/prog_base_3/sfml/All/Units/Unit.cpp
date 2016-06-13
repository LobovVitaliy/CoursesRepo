#include "Unit.hpp"

Unit:: Unit(Sprite & spr, Sprite & scaleUpdate, Database & db, int positionX, int positionY, int width, int height, int Radius) :
Images(spr, positionX, positionY, width, height, Radius), db(db)
{
    this->db = db;
    this->scaleUpdate = scaleUpdate;

    this->isMove = false;
    this->isSelect = false;
    this->isLive = true;

    this->CurrentFrame = 0;
    this->stopAngle = 360;
    this->angle = 45;
    this->life = 3;
}

void Unit:: update(float time, int numImage, int posX, int posY)
{
    CurrentFrame += 0.02*time;
    if (CurrentFrame > 10) CurrentFrame -= 10;
    sprite.setTextureRect(IntRect(w * int(CurrentFrame), numImage, w, h));
    sprite.setPosition(posX, posY);
}

void Unit:: stop()
{
    if (-90 < angle && angle <= 0)
        sprite.setTextureRect(IntRect(0, 280, w, h));
    else if (-180 < angle && angle <= -90)
        sprite.setTextureRect(IntRect(0, 120, w, h));
    else if (0 < angle && angle <= 90)
        sprite.setTextureRect(IntRect(0, 200, w, h));
    else if (90 < angle && angle <= 180)
        sprite.setTextureRect(IntRect(0, 40, w, h));
}

void Unit:: movement(float time)
{
    if (isMove)
    {
        int status = 1;

        char sqlQuery[] = "SELECT * FROM Map;";
        for(int j = 0; j < db.count("SELECT COUNT(*) FROM Map;"); j++)
        {
            db.getDataByIndex(sqlQuery, j);

            if (x < -1475 + R)
            {
                stopAngle = 180;
                status = 0;
                break;
            }
            else if (x > 2841 - R)
            {
                stopAngle = 0;
                status = 0;
                break;
            }
            else if (y < -750 + R)
            {
                stopAngle = -90;
                status = 0;
                break;
            }
            else if (y > 1593 - R)
            {
                stopAngle = 90;
                status = 0;
                break;
            }

            if ( (((x - db.x)*(x - db.x)) + ((y - db.y)*(y - db.y))) < (db.R + 20)*(db.R + 20) )
            {
                int stopX = db.x - x;
                int stopY = db.y - y;

                stopAngle = (180 / M_PI) * atan2(float(stopY), float(stopX));

                status = 0;
                break;
            }
        }

        if(stopAngle != 360)
        {
            int stopAngleR = stopAngle - 90;
            int stopAngleL = stopAngle + 90;

            if(stopAngleL > 180) stopAngleL -= 360;
            if(stopAngleR < -180) stopAngleR += 360;

            if(-90 <= stopAngle && stopAngle <= 90)
            {
                if(stopAngleR <= angle && angle <= stopAngleL)
                {
                    status = 0;
                }
                else
                {
                    status = 1;
                    stopAngle = 360;
                }
            }
            else
            {
                if(stopAngleL <= angle && angle <= stopAngleR)
                {
                    status = 1;
                    stopAngle = 360;
                }
                else
                {
                    status = 0;
                }
            }
        }

        if(status == 0)
        {
            stop();
            isMove = false;
            return;
        }

        if (x != endX || y != endY)
        {
            if (-45 < angle && angle <= 0)
            {
                if (x <= begX + abs(dy)/2)
                    update(time, 280, x++, y--);
                else if (x <= endX - abs(dy)/2)
                    update(time, 240, x++, y);
                else if (x <= endX)
                    update(time, 280, x++, y--);
            }
            else if (-90 < angle && angle <= -45)
            {
                if (y >= begY - abs(dx)/2)
                    update(time, 280, x++, y--);
                else if (y >= endY + abs(dx)/2)
                    update(time, 160, x, y--);
                else if (y >= endY)
                    update(time, 280, x++, y--);
            }
            else if (-135 < angle && angle <= -90)
            {
                if (y >= begY - abs(dx)/2)
                    update(time, 120, x--, y--);
                else if (y >= endY + abs(dx)/2)
                    update(time, 160, x, y--);
                else if (y >= endY)
                    update(time, 120, x--, y--);
            }
            else if (-180 < angle && angle <= -135)
            {
                if (x >= begX - abs(dy)/2)
                    update(time, 120, x--, y--);
                else if (x >= endX + abs(dy)/2)
                    update(time, 80, x--, y);
                else if (x >= endX)
                    update(time, 120, x--, y--);
            }
            else if (0 < angle && angle <= 45)
            {
                if (x <= begX + abs(dy)/2)
                    update(time, 200, x++, y++);
                else if (x <= endX - abs(dy)/2)
                    update(time, 240, x++, y);
                else if (x <= endX)
                    update(time, 200, x++, y++);
            }
            else if (45 < angle && angle <= 90)
            {
                if (y <= begY + abs(dx)/2)
                    update(time, 200, x++, y++);
                else if (y <= endY - abs(dx)/2)
                    update(time, 0, x, y++);
                else if (y <= endY)
                    update(time, 200, x++, y++);
            }
            else if (90 < angle && angle <= 135)
            {
                if (y <= begY + abs(dx)/2)
                    update(time, 40, x--, y++);
                else if (y <= endY - abs(dx)/2)
                    update(time, 0, x, y++);
                else if (y <= endY)
                    update(time, 40, x--, y++);
            }
            else if (135 < angle && angle <= 180)
            {
                if (x >= begX - abs(dy)/2)
                    update(time, 40, x--, y++);
                else if (x >= endX + abs(dy)/2)
                    update(time, 80, x--, y);
                else if (x >= endX)
                    update(time, 40, x--, y++);
            }
        }
        else
        {
            stop();
            isMove = false;
        }
    }
    else
    {
        stop();
    }
}

void Unit:: mouseRight()
{
    begX = x;
    begY = y;

    dx = endX - begX;
    dy = endY - begY;

    angle = (180 / M_PI) * atan2(float(dy), float(dx));
}

int Unit:: getLife()
{
    return life;
}

int Unit:: getX()
{
    return x;
}

int Unit:: getY()
{
    return y;
}


