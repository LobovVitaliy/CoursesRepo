#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <list>

//#include "All/Database/Database.hpp"
//#include "All/Images/Images.hpp"

#include "All/Units/Enemy.hpp"
#include "All/Units/Player.hpp"

#define MAX_COUNT_HEROS 50

using namespace std;
using namespace sf;

double length(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

///////////////FILE HERO///////////////
/*void saveHero(const char * file, int Name, int R, int x, int y)
{
    ofstream fout(file, std::ios_base::app);
    fout << "Name = " << Name << "; R = " << R << "; x = " << x << "; y = " << y << "\n";
    fout.close();
}

void fileHeroCleaning(const char * file)
{
    fstream fileClean;
    fileClean.open(file, ios::out);
    fileClean << "";
    fileClean.close();
}

void heroCleaning(const char * file, int index)
{
    int Name;

    const int len = 50, strings = 1000;
    int countStr = 0;
    int delIndex = -1;
    char buffer[len][strings];

    ifstream fs(file, ios::in | ios::binary);
    while (fs.getline(buffer[countStr], 50))
    {
        char * pointName = strstr(buffer[countStr], "Name = ");
        pointName += 7;
        Name = atoi(pointName);

        if(Name == index)
        {
            delIndex = countStr;
        }
        countStr++;
    }
    fs.close();

    fileHeroCleaning(file);

    ofstream fout(file, std::ios_base::app);
    for(int k = 0; k < countStr; k++)
    {
        if(k != delIndex) fout << buffer[k] << "\n";
    }
    fout.close();
}

bool checkPos(const char * file, int posX, int posY, int index)
{
    int Name, R, x, y;

    const int len = 50, strings = 100;
    int countStr = 0;
    char buffer[len][strings];

    ifstream fs(file, ios::in | ios::binary);
    while (fs.getline(buffer[countStr], 50))
    {
        char * pointName = strstr(buffer[countStr], "Name = ");
        pointName += 7;
        Name = atoi(pointName);

        char * pointR = strstr(buffer[countStr], "R = ");
        pointR += 4;
        R = atoi(pointR);

        char * pointX = strstr(buffer[countStr], "x = ");
        pointX += 4;
        x = atoi(pointX);

        char * pointY = strstr(buffer[countStr], "y = ");
        pointY += 4;
        y = atoi(pointY);

        if(Name != index)
        {
            if ( (((posX - x)*(posX - x)) + ((posY - y)*(posY - y))) <= R * R )
            {
                fs.close();
                return false;
            }
        }
        countStr++;
    }
    fs.close();
    return true;
}*/


/*
class Images
{
public:
    int x, y, w, h, R;

    Image image;
    Texture texture;
    Sprite sprite;

    Images(string file, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int Radius = 0)
    {
        this->image.loadFromFile(file);
        this->texture.loadFromImage(image);
        this->sprite.setTexture(texture);
        this->sprite.setPosition(positionX, positionY);
        this->sprite.setOrigin(Vector2f(width/2, height/2));
        this->x = positionX;
        this->y = positionY;
        this->w = width;
        this->h = height;
        this->R = Radius;
    }

    Images(Sprite & spr, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int Radius = 0)
    {
        this->sprite = spr;
        this->sprite.setPosition(positionX, positionY);
        this->sprite.setOrigin(Vector2f(width/2, height/2));
        this->x = positionX;
        this->y = positionY;
        this->w = width;
        this->h = height;
        this->R = Radius;
    }
};*/

///////////////// HERO ////////////////////////
/*
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

    Unit(Sprite & spr, Sprite & scaleUpdate, Database & db, int positionX, int positionY, int width, int height, int Radius = 20) :
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

    void update(float time, int numImage, int posX, int posY)
    {
        CurrentFrame += 0.02*time;
        if (CurrentFrame > 10) CurrentFrame -= 10;
        sprite.setTextureRect(IntRect(w * int(CurrentFrame), numImage, w, h));
        sprite.setPosition(posX, posY);
    }

    void stop()
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

    void movement(float time)
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
                else
                {
                    stopAngle = 360;
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

    void mouseRight()
    {
        begX = x;
        begY = y;

        dx = endX - begX;
        dy = endY - begY;

        angle = (180 / M_PI) * atan2(float(dy), float(dx));
    }

    int getLife()
    {
        return life;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }
};

class Player : public Unit
{
public:
    char Name[20];

    int armor;
    Sprite scaleArmor;

    Player(Sprite & spr, Sprite & scaleUpdate, Sprite & scaleArmor, Database & db, const char * name, int ID, int positionX, int positionY, int width, int height, int Radius = 20) :
    Unit(spr, scaleUpdate, db, positionX, positionY, width, height, Radius)
    {
        strcpy(this->Name, name);
        this->scaleArmor = scaleArmor;
        this->armor = 0;
    }

    void changeLife()
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

    void checkLife(int RadiusTower)
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
                    //break; // ��� break, ��� ��� ��� ��������� ���������� ������ ���� ����������
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

    void setArmor(int armor)
    {
        this->armor += armor;
        if(this->armor > 3) this->armor = 3;
    }

    int getArmor()
    {
        return armor;
    }

    void stopHero()
    {
        isSelect = false;
        sprite.setColor(Color::White);
    }

    void selectHero(int posX, int posY)
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

    void selectHero(int pressed_LKM_X, int pressed_LKM_Y, int released_LKM_X, int released_LKM_Y)
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

    void endPosHero(int posX, int posY, int index)
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

    void updateHero(float time)
    {
        if(isLive == true) movement(time);
    }

    void drawHero(RenderWindow & window)
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
};

class Enemy : public Unit
{
public:

    Enemy(Sprite & spr, Sprite & scaleUpdate, Database & db, int positionX, int positionY, int width, int height, int Radius = 20) :
    Unit(spr, scaleUpdate, db, positionX, positionY, width, height, Radius)
    {
        this->sprite.setColor(Color(80, 80, 80));
    }

    void changeLife()
    {
        life--;
        if(life == 0) isLive = false;
    }

    void checkLife()
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
                    //break; // ��� break, ��� ��� ��� ��������� ���������� ������ ���� ����������
                }
            }
        }
    }

    bool checkLife(int posX, int posY)
    {
        if(pow(posX - x, 2) + pow(posY - y, 2) <= 2500)
        {
            changeLife();
            return true;
        }
        return false;
    }

    void endPosEnemy(int posX, int posY, int index)
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

    void updateEnemy(float time)
    {
        if(isLive == true) movement(time);
    }

    void drawEnemy(RenderWindow & window)
    {
        if(isLive == true)
        {
            scaleUpdate.setPosition(x + 17, y - 25);
            scaleUpdate.setTextureRect(IntRect(18 * (3 - life), 0, 18, 7));
            window.draw(scaleUpdate);
            window.draw(sprite);
        }
    }
};
*/
// ��������� �������� ����� ���������� �� ��������� � �� �������
// ����� ����� �� ���������

// ����� ������ ���� ������ �� ������ ������, � �� �� ���� ����� !!!
// ����� ����� ���������� �� ������ ���� !!!

class Options
{
public:
    int checkOffHelp;
    int checkOffMusic;
    int numMusic;
    string fileNameMusic;

    Options()
    {
        checkOffHelp = 1;
        checkOffMusic = 0;
        numMusic = 0;
        fileNameMusic = "";
    }
};

void menu(RenderWindow & window);
void game(RenderWindow & window, Options & options);
void settings(RenderWindow & window, Options & options);


void menu(RenderWindow & window)
{
    Images Background("Images/Menu/MenuBackground.png");

    Font font;
    font.loadFromFile("Tahoma.ttf");

    Text textNewGame("New game", font, 50);
    Text textSettings("Settings", font, 50);
    Text textQuitGame("Quit game", font, 50);

    textNewGame.setStyle(Text::Bold);
    textSettings.setStyle(Text::Bold);
    textQuitGame.setStyle(Text::Bold);

    Options options;

    bool isMenu = true;
    int menuNum = 0;

    while (isMenu)
    {
        Vector2i pixelPosWindow = window.getPosition();
        Vector2f posWindow = window.mapPixelToCoords(pixelPosWindow);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    if (menuNum == 1) game(window, options);
                    else if (menuNum == 2) settings(window, options);
                    else if (menuNum == 3) isMenu = false;
                }
            }
        }

        menuNum = 0;

        Background.sprite.setPosition(posWindow.x, posWindow.y);
        window.draw(Background.sprite);

        textNewGame.setPosition(posWindow.x + 230, posWindow.y + 250);
        textSettings.setPosition(posWindow.x + 260, posWindow.y + 355);
        textQuitGame.setPosition(posWindow.x + 230, posWindow.y + 455);

        textNewGame.setColor(Color(116, 105, 150));
        textSettings.setColor(Color(116, 105, 150));
        textQuitGame.setColor(Color(116, 105, 150));

        if (IntRect(215, 245, 270, 82).contains(Mouse::getPosition(window)))
        {
            textNewGame.setColor(Color(85, 60, 170));
            menuNum = 1;
        }
        else if (IntRect(215, 345, 270, 92).contains(Mouse::getPosition(window)))
        {
            textSettings.setColor(Color(85, 60, 170));
            menuNum = 2;
        }
        else if (IntRect(215, 450, 270, 85).contains(Mouse::getPosition(window)))
        {
            textQuitGame.setColor(Color(85, 60, 170));
            menuNum = 3;
        }

        window.draw(textNewGame);
        window.draw(textSettings);
        window.draw(textQuitGame);

        window.display();
    }
}

void settings(RenderWindow & window, Options & options)
{
    Images Background("Images/Settings/SettingsBackground.png");

    Images offHelp("Images/Settings/off.png", 797, 188);
    Images offMusic("Images/Settings/off.png", 797, 303);

    Font font;
    font.loadFromFile("Tahoma.ttf");

    Text textM1("Default", font, 25);
    Text textM2("Image Dragons - Radioactiv", font, 25);
    Text textM3("Mattafix - Big City Life", font, 25);
    Text textM4("Nirvana - Smells Like Teen Spirit", font, 25);
    Text textM5("Red Hot Chili Peppers - Cant Stop", font, 25);
    Text textM6("Red Hot Chili Peppers - Snow Hey Oh", font, 25);

    textM1.setStyle(Text::Bold);
    textM2.setStyle(Text::Bold);
    textM3.setStyle(Text::Bold);
    textM4.setStyle(Text::Bold);
    textM5.setStyle(Text::Bold);
    textM6.setStyle(Text::Bold);

    while (!Keyboard::isKeyPressed(Keyboard::Escape))
    {
        Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f pos = window.mapPixelToCoords(pixelPos);

        Vector2i pixelPosWindow = window.getPosition();
        Vector2f posWindow = window.mapPixelToCoords(pixelPosWindow);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    if (offHelp.sprite.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        options.checkOffHelp++;
                        options.checkOffHelp %= 2;
                    }
                    else if (offMusic.sprite.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        options.checkOffMusic++;
                        options.checkOffMusic %= 2;
                    }
                    else if (textM1.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        options.numMusic = 1;
                        options.fileNameMusic = "Music/StepUp.ogg";
                    }
                    else if (textM2.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        options.numMusic = 2;
                        options.fileNameMusic = "Music/ImageDragons-Radioactiv.ogg";
                    }
                    else if (textM3.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        options.numMusic = 3;
                        options.fileNameMusic = "Music/Mattafix-BigCityLife.ogg";
                    }
                    else if (textM4.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        options.numMusic = 4;
                        options.fileNameMusic = "Music/Nirvana-SmellsLikeTeenSpirit.ogg";
                    }
                    else if (textM5.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        options.numMusic = 5;
                        options.fileNameMusic = "Music/RedHotChiliPeppers-CantStop.ogg";
                    }
                    else if (textM6.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        options.numMusic = 6;
                        options.fileNameMusic = "Music/RedHotChiliPeppers-SnowHeyOh.ogg";
                    }
                }
            }
        }

        Background.sprite.setPosition(posWindow.x, posWindow.y);
        window.draw(Background.sprite);

        offHelp.sprite.setPosition(posWindow.x + 797, posWindow.y + 188);
        offMusic.sprite.setPosition(posWindow.x + 797, posWindow.y + 303);

        if (options.checkOffHelp == 0)
        {
            window.draw(offHelp.sprite);
        }
        if (options.checkOffMusic == 0)
        {
             window.draw(offMusic.sprite);
             options.numMusic = 0;
             options.fileNameMusic = "";
        }

        textM1.setPosition(posWindow.x + 635, posWindow.y + 360);
        textM2.setPosition(posWindow.x + 510, posWindow.y + 400);
        textM3.setPosition(posWindow.x + 540, posWindow.y + 435);
        textM4.setPosition(posWindow.x + 480, posWindow.y + 470);
        textM5.setPosition(posWindow.x + 470, posWindow.y + 505);
        textM6.setPosition(posWindow.x + 450, posWindow.y + 540);

        textM1.setColor(Color::White);
        textM2.setColor(Color::White);
        textM3.setColor(Color::White);
        textM4.setColor(Color::White);
        textM5.setColor(Color::White);
        textM6.setColor(Color::White);

        if (options.numMusic == 1) textM1.setColor(Color(230, 100, 200));
        else if (options.numMusic == 2) textM2.setColor(Color(230, 100, 200));
        else if (options.numMusic == 3) textM3.setColor(Color(230, 100, 200));
        else if (options.numMusic == 4) textM4.setColor(Color(230, 100, 200));
        else if (options.numMusic == 5) textM5.setColor(Color(230, 100, 200));
        else if (options.numMusic == 6) textM6.setColor(Color(230, 100, 200));

        window.draw(textM1);
        window.draw(textM2);
        window.draw(textM3);
        window.draw(textM4);
        window.draw(textM5);
        window.draw(textM6);

        window.display();
    }
}



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
    int deltaArmor; // ������ ��� House
    int Radius;

    ImagesBuild(Sprite & spr, Sprite & scaleUpdate, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int coins = 0) :
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

    void setPosition(int Radius, int posX, int posY)
    {
        R = Radius;
        x = posX;
        y = posY;
    }
};

class Building
{
public:
    ImagesBuild ** building;

    char Name[20];
    Database * db;

    int maxCount;
    int index;

    Building(Sprite & spr, Sprite & scaleUpdate, const char * name, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int maxCount = 0, int coins = 0)
    {
        strcpy(this->Name, name);
        this->db = new Database("Data.db");
        this->maxCount = maxCount;
        this->building = new ImagesBuild* [maxCount];
        this->index = -1;

        for(int i = 0; i < maxCount; i++)
        {
            building[i] = new ImagesBuild(spr, scaleUpdate, positionX, positionY, width, height, coins);
        }
    }

    ~Building()
    {
        for (int i = 0; i < maxCount; i++)
        {
            delete building[i];
        }
        delete [] building;
        delete db;
    }


    void changeLife(int i)
    {
        building[i]->life--;
        if(building[i]->life == 0)
        {
            building[i]->isLive = false;
            deleteBuildingIndex(i);
        }
    }

    void checkLife(int posX, int posY)
    {
        for(int i = 0; i < index + 1; i++)
        {
            char sqlQuery[] = "SELECT * FROM Map WHERE Name = ? AND ID = ?;";
            db->getData(sqlQuery, Name, i);

            if(pow(posX - db->x, 2) + pow(posY - db->y, 2) <= pow(db->R + 20 + 30, 2))
            {
                changeLife(i);
                //break; // ?
            }
        }
    }



    int checkPosition(int posX, int posY)
    {
        for(int i = 0; i < index + 1; i++) // ������ ���� �� maxCount, ��� ������� ������� ��������� ����� ��� ���������
        {
            if ( (((posX - building[i]->x)*(posX - building[i]->x)) + ((posY - building[i]->y)*(posY - building[i]->y))) <= (building[i]->R)*(building[i]->R) )
            {
                return i;
            }
        }
        return -1;
    }

    int getX(int i)
    {
        if (building[i]->isLive)
            return building[i]->x;
        else
            return 5000;
    }

    int getY(int i)
    {
        if (building[i]->isLive)
            return building[i]->y;
        else
            return 5000;
    }

    void createAndMove(RenderWindow & window, int posX, int posY)
    {
        if (index < maxCount - 1)
        {
            index++;
            building[index]->isLive = true;
            building[index]->isMove = true;
            building[index]->isCreate = true;
            building[index]->sprite.setPosition(posX, posY);
            window.draw(building[index]->sprite);
        }
    }

    void deleteBuildingIndex(int indexBuilding) // db // change
    {
        char sqlQuery[] = "DELETE FROM Map WHERE Name = ? AND ID = ?;";
        db->deleteData(sqlQuery, Name, indexBuilding); // change

        int x, y, w, h, R, coins, deltaArmor, life;
        bool isMove, isCreate, isLive;

        Image image;
        Texture texture;
        Sprite sprite;

        char sqlQueryUp[] = "UPDATE Map SET ID = ? WHERE Name = ? AND ID = ?;";

        // �������� ������� ���������� � ������� ����
        building[indexBuilding]->deltaArmor = 1;
        building[indexBuilding]->life = 10;
        building[indexBuilding]->coins = building[indexBuilding]->startCoins;

        for(int i = indexBuilding; i < index; i++)
        {
            ////////////////////////////////////////////
            x = building[i + 1]->x;
            y = building[i + 1]->y;
            w = building[i + 1]->w;
            h = building[i + 1]->h;
            R = building[i + 1]->R;
            coins = building[i + 1]->coins;
            deltaArmor = building[i + 1]->deltaArmor;
            life = building[i + 1]->life;

            image = building[i + 1]->image;
            texture = building[i + 1]->texture;
            sprite = building[i + 1]->sprite;

            isCreate = building[i + 1]->isCreate;
            isLive = building[i + 1]->isLive;
            isMove = building[i + 1]->isMove;

            ////////////////////////////////////////////
            building[i]->x = x;
            building[i]->y = y;
            building[i]->w = w;
            building[i]->h = h;
            building[i]->R = R;
            building[i]->coins = coins;
            building[i]->deltaArmor = deltaArmor;
            building[i]->life = life;

            building[i]->image = image;
            building[i]->texture = texture;
            building[i]->sprite = sprite;

            building[i]->isCreate = isCreate;
            building[i]->isLive = isLive;
            building[i]->isMove = isMove;

            db->updateDataID(sqlQueryUp, Name, i + 1, i);
        }

        building[index]->isCreate = false;
        building[index]->isLive = false;
        building[index]->isMove = false;

        index--;
    }

    void deleteBuilding()
    {
        if(index > -1)
        {
            if(building[index]->isMove)
            {
                building[index]->isMove = false;
                building[index]->isCreate = false;
                index--;
            }
        }
    }

    bool build(int Radius, int posX, int posY) // db
    {
        if(index > -1)
        {
            if(building[index]->isLive)
            {
                building[index]->isMove = false;
                building[index]->setPosition(Radius, posX, posY);

                char sqlQuery[] = "INSERT INTO Map (Name, ID, R, x, y, Radius) VALUES (?, ?, ?, ?, ?, ?);";

                if(strcmp(Name, "Ambar") == 0)
                {
                    db->insertData(sqlQuery, Name, index, Radius, posX, posY, 220);
                }
                else if(strcmp(Name, "Fountain") == 0 || strcmp(Name, "Tower") == 0)
                {
                    db->insertData(sqlQuery, Name, index, Radius, posX, posY, 100);
                }
                else
                {
                    db->insertData(sqlQuery, Name, index, Radius, posX, posY, 0);
                }

                return true;
            }
        }
        return false;
    }

    void moveAndDraw(RenderWindow & window, int Radius, int posX, int posY) // db // change
    {
        for(int i = 0; i < maxCount; i++)
        {
            if (building[i]->isCreate)
            {
                if (building[index]->isMove)
                {
                    // ���� ������ ��������
                    CircleShape shape(Radius);
                    shape.setFillColor(Color::Transparent);

                    shape.setOrigin(Radius, Radius);
                    shape.setOutlineThickness(2);
                    shape.setOutlineColor(Color(194, 228, 228));
                    shape.setPosition(posX, posY);

                    window.draw(shape);

                    building[index]->sprite.setPosition(posX, posY);

                    char sqlQuery[] = "SELECT * FROM Map;";
                    for(int j = 0; j < db->count("SELECT COUNT(*) FROM Map;"); j++)
                    {
                        db->getDataByIndex(sqlQuery, j);
                        if(strcmp(db->Name, "Ambar") == 0) db->R = db->Radius; // change

                        // ��������� ���� ����� � ��������� ������� �� �����
                        if (posX < -300 + Radius || posX > 2841 - Radius || posY < -750 + Radius || posY > 1593 - Radius) // posX < -1475
                        {
                            building[index]->sprite.setColor(Color::Red);
                            building[index]->isLive = false;
                            break;
                        }
                        else if (db->R + Radius < length(posX, posY, db->x, db->y))
                        {
                            building[index]->sprite.setColor(Color::White);
                            building[index]->isLive = true;
                        }
                        else
                        {
                            building[index]->sprite.setColor(Color::Red);
                            building[index]->isLive = false;
                            break;
                        }
                    }
                }

                window.draw(building[i]->sprite);
            }
        }
    }

    void drawScale(RenderWindow & window)
    {
        for(int i = 0; i < index + 1; i++)
        {
            if (building[i]->isMove == false)
            {
                int R = 0;
                if(strcmp(Name, "Cave") == 0) R = -10;
                else if(strcmp(Name, "House") == 0) R = 10;
                else if(strcmp(Name, "Ambar") == 0) R = 20;

                building[i]->scaleUpdate.setPosition(building[i]->x, building[i]->y - R);
                building[i]->scaleUpdate.setTextureRect(IntRect(0, 14 * (10 - building[i]->life), 112, 14));
                window.draw(building[i]->scaleUpdate);
            }
        }
    }

    void setCoins(int indexBuilding, int newCoins)
    {
        building[indexBuilding]->coins += newCoins;
    }

    int getCoinsByID(int indexBuilding)
    {
        return building[indexBuilding]->coins;
    }

    int getCoins()
    {
        int coins = 0;
        for(int i = 0; i < index + 1; i++)
        {
            if(building[i]->isMove == false)
            {
                 coins += building[i]->coins;
            }
        }
        return coins;
    }

    int getIndex()
    {
        return index;
    }

    void setDeltaArmor(int i, int deltaArmor)
    {
        building[i]->deltaArmor = deltaArmor;
    }

    int getDeltaArmor(int i)
    {
        if (building[i]->isLive) return building[i]->deltaArmor;
        return 0;
    }


    void setRadius(int i, int Radius)
    {
        char sqlQuery[] = "UPDATE Map SET Radius = ? WHERE Name = ? AND ID = ?;";
        building[i]->Radius = Radius;
        db->updateDataRadius(sqlQuery, Name, i, Radius);
    }

    int getRadius(int i)
    {
        char sqlQuery[] = "SELECT * FROM Map WHERE Name = ? AND ID = ?;";
        db->getData(sqlQuery, Name, i);
        return db->Radius;
    }
};

class BuildingEnemy
{
public:
    ImagesBuild ** building;

    char Name[20];
    Database * db;

    int maxCount;
    int index ;

    BuildingEnemy(Sprite & spr, Sprite & scaleUpdate,  const char * name, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int maxCount = 0, int coins = 0)
    {
        strcpy(this->Name, name);
        this->db = new Database("Data.db");
        this->maxCount = maxCount;
        this->building = new ImagesBuild* [maxCount];
        this->index = -1;

        for(int i = 0; i < maxCount; i++)
        {
            building[i] = new ImagesBuild(spr, scaleUpdate, positionX, positionY, width, height, coins);
        }
    }

    ~BuildingEnemy()
    {
        for (int i = 0; i < maxCount; i++)
        {
            delete building[i];
        }
        delete [] building;
        delete db;
    }


    void changeLife(int i)
    {
        building[i]->life--;
        if(building[i]->life == 0)
        {
            building[i]->isLive = false;
            deleteBuildingIndex(i);
        }
    }

    void checkLife(int posX, int posY)
    {
        for(int i = 0; i < index + 1; i++)
        {
            char sqlQuery[] = "SELECT * FROM Map WHERE Name = ? AND ID = ?;";
            db->getData(sqlQuery, Name, i);

            if(pow(posX - db->x, 2) + pow(posY - db->y, 2) <= pow(db->R + 20 + 30, 2))
            {
                changeLife(i);
                //break; // ?
            }
        }
    }


    int getX(int i)
    {
        return building[i]->x;
    }

    int getY(int i)
    {
        return building[i]->y;
    }

    void create(int Radius, int posX, int posY)
    {
        if (index < maxCount - 1)
        {
            index++;
            building[index]->isLive = true;
            building[index]->isCreate = true;
            building[index]->sprite.setPosition(posX, posY);
            building[index]->setPosition(Radius, posX, posY);

            char sqlQuery[] = "INSERT INTO Map (Name, ID, R, x, y, Radius) VALUES (?, ?, ?, ?, ?, ?);";

            if(strcmp(Name, "EnemyTower") == 0)
            {
                db->insertData(sqlQuery, Name, index, Radius, posX, posY, 200);
            }
            else
            {
                db->insertData(sqlQuery, Name, index, Radius, posX, posY, 0);
            }
        }
    }

    void deleteBuildingIndex(int indexBuilding) // db // change
    {
        char sqlQuery[] = "DELETE FROM Map WHERE Name = ? AND ID = ?;";
        db->deleteData(sqlQuery, Name, indexBuilding); // change

        int x, y, w, h, R, coins, deltaArmor, life;
        bool isMove, isCreate, isLive;

        Image image;
        Texture texture;
        Sprite sprite;

        char sqlQueryUp[] = "UPDATE Map SET ID = ? WHERE Name = ? AND ID = ?;";

        // �������� ������� ���������� � ������� ����
        building[indexBuilding]->life = 10;
        building[indexBuilding]->coins = building[indexBuilding]->startCoins;

        for(int i = indexBuilding; i < index; i++)
        {
            ////////////////////////////////////////////
            x = building[i + 1]->x;
            y = building[i + 1]->y;
            w = building[i + 1]->w;
            h = building[i + 1]->h;
            R = building[i + 1]->R;
            coins = building[i + 1]->coins;
            deltaArmor = building[i + 1]->deltaArmor;
            life = building[i + 1]->life;

            image = building[i + 1]->image;
            texture = building[i + 1]->texture;
            sprite = building[i + 1]->sprite;

            isCreate = building[i + 1]->isCreate;
            isLive = building[i + 1]->isLive;
            isMove = building[i + 1]->isMove;

            ////////////////////////////////////////////
            building[i]->x = x;
            building[i]->y = y;
            building[i]->w = w;
            building[i]->h = h;
            building[i]->R = R;
            building[i]->coins = coins;
            building[i]->deltaArmor = deltaArmor;
            building[i]->life = life;

            building[i]->image = image;
            building[i]->texture = texture;
            building[i]->sprite = sprite;

            building[i]->isCreate = isCreate;
            building[i]->isLive = isLive;
            building[i]->isMove = isMove;

            db->updateDataID(sqlQueryUp, Name, i + 1, i);
        }

        building[index]->isCreate = false;
        building[index]->isLive = false;
        building[index]->isMove = false;

        index--;
    }

    void deleteBuilding()
    {
        if(index > -1)
        {
            if(building[index]->isMove)
            {
                building[index]->isCreate = false;
                index--;
            }
        }
    }

    bool build(int Radius, int posX, int posY) // db
    {
        if(index > -1)
        {
            if(building[index]->isLive)
            {
                building[index]->isMove = false;
                building[index]->setPosition(Radius, posX, posY);

                char sqlQuery[] = "INSERT INTO Map (Name, ID, R, x, y, Radius) VALUES (?, ?, ?, ?, ?, ?);";

                if(strcmp(Name, "Ambar") == 0)
                {
                    db->insertData(sqlQuery, Name, index, Radius, posX, posY, 220);
                }
                else if(strcmp(Name, "Fountain") == 0 || strcmp(Name, "Tower") == 0)
                {
                    db->insertData(sqlQuery, Name, index, Radius, posX, posY, 200);
                }
                else
                {
                    db->insertData(sqlQuery, Name, index, Radius, posX, posY, 0);
                }

                return true;
            }
        }
        return false;
    }

    int getIndex()
    {
        return index;
    }

    void draw(RenderWindow & window)
    {
        for(int i = 0; i < index + 1; i++)
        {
            int R = 0;
            if(strcmp(Name, "EnemyCastle") == 0) R = 60;

            building[i]->scaleUpdate.setPosition(building[i]->x, building[i]->y - R);
            building[i]->scaleUpdate.setTextureRect(IntRect(0, 14 * (10 - building[i]->life), 112, 14));
            window.draw(building[i]->scaleUpdate);

            window.draw(building[i]->sprite);
        }
    }
};




void build(RenderWindow & window)
{
    Database * db = new Database("Data.db");

    char sqlQuery[] = "SELECT * FROM Map;";
    for(int j = 0; j < db->count("SELECT COUNT(*) FROM Map;"); j++)
    {
        db->getDataByIndex(sqlQuery, j);

        int Radius = db->R;
        if(strcmp(db->Name, "Ambar") == 0) Radius = db->Radius;

        // ���� ������ ��������
        CircleShape shape(Radius);
        shape.setFillColor(Color::Transparent);

        shape.setOrigin(Radius, Radius);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(Color(194, 228, 228, 80));
        shape.setPosition(db->x, db->y);
        window.draw(shape);
    }
}

/*void Artificial_Intelligence(int & Step, list<Enemy*> & enemy, Images & imagePlayer, BuildingEnemy & boiler, int & checkNewEnemy, Images & scaleUpdate, Database & db)
{
    list<Enemy*> :: iterator itEnemy;

    if(Step < 200) Step++;
    else Step = 0;

    if(Step == 199)
    for(int index = 0; index < boiler.getIndex() + 1; index++)
    if(boiler.building[index]->isLive)
    {
        if((int)enemy.size() < (boiler.getIndex() + 2) * 5)
        {
            enemy.push_back(new Enemy(imagePlayer.sprite, scaleUpdate.sprite, db, boiler.building[index]->x + 100, boiler.building[index]->y + 40, 40, 40));

            int i = 0;
            int k = 0;

            for(itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++, i++)
            {
                if(i < 5)
                {
                    (*itEnemy)->endPosEnemy(-900 + k++ * 40, -500, i); //-900 -600
                    if(k == 5) k = 0;
                }
                else if(i >= 5 && i < 10)
                {
                    (*itEnemy)->endPosEnemy(-900 + k++ * 40, -460, i);
                    if(k == 5) k = 0;
                }
                else if(i >= 10 && i < 15)
                {
                    (*itEnemy)->endPosEnemy(-900 + k++ * 40, -420, i);
                    if(k == 5) k = 0;
                }
                else if(i >= 15 && i < 20)
                {
                    (*itEnemy)->endPosEnemy(-900 + k++ * 40, -380, i);
                    if(k == 5) k = 0;
                }
            }
        }
        else
        {
            checkNewEnemy++;
        }
    }

    if(checkNewEnemy > -1 && checkNewEnemy < 5)
    {
        for(int index = 0; index < boiler.getIndex() + 1; index++)
        if(boiler.building[index]->isLive)
        {
            enemy.push_back(new Enemy(imagePlayer.sprite, scaleUpdate.sprite, db, boiler.building[index]->x + 100, boiler.building[index]->y + 40, 40, 40));

            int i = 0;
            int k = 0;

            itEnemy = enemy.begin();
            for(int q = 0; q < 15; q++) itEnemy++;

            for(; itEnemy != enemy.end(); itEnemy++, i++)
            {
                if(i < 5)
                {
                    (*itEnemy)->endPosEnemy(-1200 + k++ * 40, 1000, i);
                    if(k == 5) k = 0;
                }
            }

            checkNewEnemy++;
        }
    }

    for(itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++)
    {
        if((*itEnemy)->x < -1100 && (*itEnemy)->y > 950)
        {
            boiler.create(65, -1300, 1100);
            checkNewEnemy = 100500;
            break;
        }
    }
}*/

void Artificial_Intelligence(int & Step, list<Enemy*> & enemy, Images & imagePlayer, BuildingEnemy & boiler, int & checkNewEnemy, Images & scaleUpdate, Database & db)
{
    list<Enemy*> :: iterator itEnemy;

    if(Step < 200) Step++;
    else Step = 0;

    if(enemy.size() == 0) checkNewEnemy = -1;

    if(Step == 199 && checkNewEnemy == -1)
    for(int index = 0; index < boiler.getIndex() + 1; index++)
    if(boiler.building[index]->isLive)
    {
        if((int)enemy.size() < (boiler.getIndex() + 2) * 5)
        {
            enemy.push_back(new Enemy(imagePlayer.sprite, scaleUpdate.sprite, db, boiler.building[index]->x + 100, boiler.building[index]->y + 40, 40, 40));

            int i = 0;
            int k = 0;

            for(itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++, i++)
            {
                if(i < 5)
                {
                    (*itEnemy)->endPosEnemy(-900 + k++ * 40, -500, i);
                    if(k == 5) k = 0;
                }
                else if(i >= 5 && i < 10)
                {
                    (*itEnemy)->endPosEnemy(-900 + k++ * 40, -460, i);
                    if(k == 5) k = 0;
                }
                else if(i >= 10 && i < 15)
                {
                    (*itEnemy)->endPosEnemy(-900 + k++ * 40, -420, i);
                    if(k == 5) k = 0;
                }
                else if(i >= 15 && i < 20)
                {
                    (*itEnemy)->endPosEnemy(-900 + k++ * 40, -380, i);
                    if(k == 5) k = 0;
                }
            }
        }
        else
        {
            checkNewEnemy = 0;
        }
    }

    if(Step == 199 && checkNewEnemy == 0)
    {
        for(int i = 0; i < 5; i++)
        {
            enemy.push_back(new Enemy(imagePlayer.sprite, scaleUpdate.sprite, db, boiler.building[1]->x + 100, boiler.building[1]->y + 40, 40, 40));
        }

        int q = 0;
        itEnemy = enemy.begin();
        for(; q < enemy.size() - 5; q++) itEnemy++;

        int k = 0;
        for(; itEnemy != enemy.end(); itEnemy++, q++)
        {
            (*itEnemy)->endPosEnemy(-1200 + k++ * 40, 1000, q);
        }
        checkNewEnemy = 1;
    }

    if(Step == 199 && checkNewEnemy == 1)
    {
        int q = 0;
        itEnemy = enemy.begin();
        for(; q < enemy.size() - 5; q++) itEnemy++;

        for(; itEnemy != enemy.end(); itEnemy++)
        if((*itEnemy)->x < -1100 && (*itEnemy)->y > 950)
        {
            //boiler.create(65, -1300, 1100);
            checkNewEnemy = 2;
            break;
        }
    }

    if(Step == 199 && checkNewEnemy == 2)
    {
        int i = 0;
        for (itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++, i++)
        {
            char sqlQuery[] = "SELECT * FROM Map;";
            for(int j = 0; j < db.count("SELECT COUNT(*) FROM Map;"); j++)
            {
                db.getDataByIndex(sqlQuery, j);

                int x, y;
                if(strcmp(db.Name, "Cave") == 0) {x = db.x; y = db.y; (*itEnemy)->endPosEnemy(x, y, i);}
                else if(strcmp(db.Name, "Building") == 0) {x = db.x; y = db.y; (*itEnemy)->endPosEnemy(x, y, i);}
                else if(strcmp(db.Name, "House") == 0) {x = db.x; y = db.y; (*itEnemy)->endPosEnemy(x, y, i);}
                else if(strcmp(db.Name, "Fountain") == 0) {x = db.x; y = db.y; (*itEnemy)->endPosEnemy(x, y, i);}
                else if(strcmp(db.Name, "Tower") == 0) {x = db.x; y = db.y; (*itEnemy)->endPosEnemy(x, y, i);}
                else if(strcmp(db.Name, "Ambar") == 0) {x = db.x; y = db.y; (*itEnemy)->endPosEnemy(x, y, i);}
            }
        }
    }
}

void game(RenderWindow & window, Options & options)
{
    fileHeroCleaning("hero.txt");
    fileHeroCleaning("enemy.txt");

    Images miniMap("Images/miniMap6.png", 0, 510); // or 5

    // �������� �������� ������ ���� ���, � ���������� ��������� ������ �� �������
    Images imageCave("Building/cave.png", 0, 0, 90, 60);
    Images imageBuilding("Building/building.png", 0, 0, 95, 88);
    Images imageHouse("Building/house.png", 0, 0, 140, 115);
    Images imageFountain("Building/fountain.png", 0, 0, 60, 80);
    Images imageTower("Building/tower.png", 0, 0, 75, 105);
    Images imageAmbar("Building/ambar.png", 0, 0, 165, 134);

    Images BigScaleUpdate("Images/scaleBuilding.png", 0, 0, 112, 140);

    Building cave(imageCave.sprite, BigScaleUpdate.sprite, "Cave", 0, 0, 90, 60, 5, 25);
    Building building(imageBuilding.sprite, BigScaleUpdate.sprite, "Building", 0, 0, 95, 88, 5, 50);
    Building house(imageHouse.sprite, BigScaleUpdate.sprite, "House", 0, 0, 140, 115, 5);
    Building fountain(imageFountain.sprite, BigScaleUpdate.sprite, "Fountain", 0, 0, 60, 80, 5);
    Building tower(imageTower.sprite, BigScaleUpdate.sprite, "Tower", 0, 0, 75, 105, 5);
    Building ambar(imageAmbar.sprite, BigScaleUpdate.sprite, "Ambar", 0, 0, 165, 134, 5);

    Images background("Images/BGG1.png", -1500, -850);

    Images castle("Images/CastleNew.png", 683, 384, 250, 268);
    Images selection("Images/selection.png", 675, 384, 365, 317);//683->675

    Images selectionNot("Images/selectionNotLittle.png", 0, 0, 58, 60);
    Images selectionNotAddition("Images/selectionNotLittle.png", 0, 0, 58, 60);

    Images selectionNot1("Images/selectionNot.png", 603, 266, 70, 72);
    Images selectionNot2("Images/selectionNot.png", 747, 266, 70, 72);
    Images selectionNot3("Images/selectionNot.png", 819, 384, 70, 72);
    Images selectionNot4("Images/selectionNot.png", 747, 504, 70, 72);
    Images selectionNot5("Images/selectionNot.png", 603, 504, 70, 72);
    Images selectionNot6("Images/selectionNot.png", 533, 384, 70, 72);

    Images selection2("Images/selection2Update1.png", 0, 0, 64, 164); //80->64
    Images selection3House("Images/selection3House.png", 0, 0, 160, 164);
    Images selection3Ambar("Images/selection3Ambar.png", 0, 0, 160, 164);

    int indexCave = -1;
    int indexBuilding = -1;
    int indexHouse = -1;
    int indexFountain = -1;
    int indexTower = -1;
    int indexAmbar = -1;

    Font font;
    font.loadFromFile("CyrilicOld.ttf");
    Text text("", font, 20);

    Text helpText("", font, 20);
    bool isHelpText = true;
    string help = "";

    bool pressed_selection_building = false;
    bool pressed_selection = false;
    int isSelect = 0;
    bool isBuild = false;

    char money[15] = "0";
    int coins = 100000;

    Clock clock;
    Clock clockTimer;
    Clock clockTimerStart;

    float timer = 0;
    View view(FloatRect(0, 0, 1366, 768));

    //// heros ////
    list<Player*> heros;
    list<Player*> :: iterator it;

    //// rectangle BEG ////
    RectangleShape rectangle(Vector2f(0, 0));
    rectangle.setSize(Vector2f(0, 0));
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(Color(250, 150, 100));

    bool pressed_rectangle = false;
    //// rectangle END ////

    int pressed_LKM_X;
    int pressed_LKM_Y;

    int released_LKM_X;
    int released_LKM_Y;

    Images imageEnemyCastle("Building/Enemy's_castle.png", 0, 0, 256, 206);
    Images imageBoiler("Building/boiler.png", 0, 0, 256, 206);
    Images imageEnemyTower("Building/Enemy's_tower.png", 0, 0, 256, 206);

    BuildingEnemy EnemyCastle(imageEnemyCastle.sprite, BigScaleUpdate.sprite, "EnemyCastle", -1300, -500, 256, 206, 5, 0);
    EnemyCastle.create(135, -1300, -500);

    BuildingEnemy boiler(imageBoiler.sprite, BigScaleUpdate.sprite, "Boiler", -1100, -600, 128, 80, 5, 0);
    boiler.create(65, -1100, -600);
    boiler.create(65, -1400, -250);

    //BuildingEnemy EnemyTower(imageEnemyTower.sprite, BigScaleUpdate.sprite, "EnemyTower", -1000, -200, 82, 102, 5, 0);
    //EnemyTower.create(55, -1000, -200);

    int checkNewEnemy = -1;

    //// Enemy ////
    list<Enemy*> enemy;
    list<Enemy*> :: iterator itEnemy;

    int Step = 0;

    const char * dbFile = "Data.db";
    Database db(dbFile);

    Vector2i pixelPosWindow;
    Vector2f posWindow;

    Images imagePlayer("Images/hero_40x40.png", 0, 0, 40, 40);

    RectangleShape rect;
    rect.setFillColor(Color::Black);

    Images scaleUpdate("Images/scaleUpdate.png", 0, 0, 54, 7);
    Images scaleArmor("Images/scaleUpdateGreen.png", 0, 0, 54, 7);

    int volume = 50;
    Music music;
    if(options.checkOffMusic == 1 && options.fileNameMusic != "")
    {
        music.openFromFile(options.fileNameMusic);
        music.setVolume(volume);
        music.setLoop(true);
        music.play();
    }

    bool isGame = true;

    while (!Keyboard::isKeyPressed(Keyboard::Escape) && isGame)
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        timer += clockTimer.getElapsedTime().asSeconds();

        if(timer > 200)
        {
            if(coins < 1000000000) coins += 10 + cave.getCoins() + building.getCoins();
            sprintf(money, "%i", coins);
            timer = 0;

            for (itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++)
            {
                cave.checkLife((*itEnemy)->getX(), (*itEnemy)->getY());
                building.checkLife((*itEnemy)->getX(), (*itEnemy)->getY());
                house.checkLife((*itEnemy)->getX(), (*itEnemy)->getY());
                fountain.checkLife((*itEnemy)->getX(), (*itEnemy)->getY());
                tower.checkLife((*itEnemy)->getX(), (*itEnemy)->getY());
                ambar.checkLife((*itEnemy)->getX(), (*itEnemy)->getY());

                (*itEnemy)->checkLife();
                if((*itEnemy)->getLife() == 0) enemy.remove(*itEnemy);
            }

            for (it = heros.begin(); it != heros.end(); it++)
            {
                EnemyCastle.checkLife((*it)->getX(), (*it)->getY());
                boiler.checkLife((*it)->getX(), (*it)->getY());
                //EnemyTower.checkLife((*it)->getX(), (*it)->getY());

                (*it)->checkLife(0); // ��� ������� ����������
                if((*it)->getLife() == 0) heros.remove(*it);
            }

            // ����� ����� �������
            for (it = heros.begin(); it != heros.end(); it++)
            {
                for (itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++)
                {
                    if((*itEnemy)->checkLife((*it)->getX(), (*it)->getY()) == true)
                    {
                        (*it)->changeLife();
                        if((*it)->getLife() == 0) heros.remove(*it);
                        if((*itEnemy)->getLife() == 0) enemy.remove(*itEnemy);
                    }
                }
            }

            clockTimer.restart();
        }

        Artificial_Intelligence(Step, enemy, imagePlayer, boiler, checkNewEnemy, scaleUpdate, db);

        if(boiler.getIndex() == -1 && EnemyCastle.getIndex() == -1 && enemy.size() == 0) isGame = false;

        /*if(checkNewEnemy == 100500)
        {
            int i = 0;
            for (itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++, i++)
            {
                (*itEnemy)->endPosEnemy(500, 500, i);
            }
        }*/

        /*
        if(Step != 200)
        {
            if(Step < 100) Step++;
            else Step = 0;
        }

        if(Step == 1)
        {
            if(enemy.size() < 40)
            {
                enemy.push_back(new Enemy(imagePlayer.sprite, -1320, -220, 40, 40));

                int i = 0;
                int k = 0;

                for(itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++, i++)
                {
                    if(i < 10)
                    {
                        (*itEnemy)->endPosEnemy(-900 + k++ * 40, -600, i);
                        if(k == 10) k = 0;
                    }
                    else if(i >= 10 && i < 20)
                    {
                        (*itEnemy)->endPosEnemy(-900 + k++ * 40, -560, i);
                        if(k == 10) k = 0;
                    }
                    else if(i >= 20 && i < 30)
                    {
                        (*itEnemy)->endPosEnemy(-900 + k++ * 40, -520, i);
                        if(k == 10) k = 0;
                    }
                    else if(i >= 30 && i < 40)
                    {
                        (*itEnemy)->endPosEnemy(-900 + k++ * 40, -480, i);
                        if(k == 10) Step = 200;
                    }
                }
            }
        }

        if(Step == 200)
        {
            if(enemy.size() == 40)
            {
                int i = 0;
                timerStart += clockTimerStart.getElapsedTime().asSeconds();

                if(timerStart > 1000)
                {
                    for(itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++, i++)
                    {
                        (*itEnemy)->endPosEnemy(300, 300, i);
                        clockTimerStart.restart();
                        timerStart = 0;
                    }
                }
            }
        }
*/

        /*
        if(Step == 500)
        {
            int i = 0;
            for (itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++, i++)
            {
                (*itEnemy)->endPosEnemy(-1100, -250, i);
            }
        }
        if(Step == 1000)
        {
            int i = 0;
            for (itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++, i++)
            {
                (*itEnemy)->endPosEnemy(-1200, -300, i);
            }
        }
        if(Step == 1500)
        {
            int i = 0;
            for (itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++, i++)
            {
                (*itEnemy)->endPosEnemy(-1000, -600, i);
            }
            Step = 0;
            enemy.push_back(new Enemy("Images/hero_40x40.png", -1325, -200, 40, 40));
        }
*/

        // ���������� ������������ ������������
        Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f pos = window.mapPixelToCoords(pixelPos);

        Event event;
        while (window.pollEvent(event))
        {
            if (Keyboard::isKeyPressed(Keyboard::Equal))
            {
                if(volume < 100) music.setVolume(volume += 10);
            }
            else if (Keyboard::isKeyPressed(Keyboard::Dash))
            {
                if(volume > 0) music.setVolume(volume -= 10);
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    isBuild = false; // ����� ��������� ��������
                    isHelpText = true; // ��������� �������� ����� ��� ��������� �� �������

                    // ������������ ���������� ��� �������� ������� ( ����� ������� ������� ����� )
                    isSelect = 0;

                    cave.deleteBuilding();
                    building.deleteBuilding();
                    house.deleteBuilding();
                    fountain.deleteBuilding();
                    tower.deleteBuilding();
                    ambar.deleteBuilding();


                    for (it = heros.begin(); it != heros.end(); it++)
                    {
                        (*it)->stopHero();
                    }

                    for (it = heros.begin(); it != heros.end(); it++)
                    {
                        (*it)->selectHero(pos.x, pos.y);
                    }

                    pressed_rectangle = true;
                    pressed_LKM_X = pos.x;
                    pressed_LKM_Y = pos.y;
                }
                else if (event.key.code == Mouse::Right)
                {
                    int i = 0;
                    for (it = heros.begin(); it != heros.end(); it++, i++)
                    {
                        (*it)->endPosHero(pos.x, pos.y, i);
                    }

                    // ������� ������� (���� ����� �������� � ����� ������� �����)
                    if (isSelect == 1)
                    {
                        if (cave.build(41, pos.x, pos.y))
                        {
                            isSelect = 0;
                            coins -= 50;
                            sprintf(money, "%i", coins);
                            isBuild = false; // ����� ��������� ��������
                        }
                    }
                    else if (isSelect == 2)
                    {
                        if (building.build(50, pos.x, pos.y))
                        {
                            isSelect = 0;
                            coins -= 250;
                            sprintf(money, "%i", coins);
                            isBuild = false; // ����� ��������� ��������
                        }
                    }
                    else if (isSelect == 3)
                    {
                        if (house.build(69, pos.x, pos.y))
                        {
                            isSelect = 0;
                            coins -= 250;
                            sprintf(money, "%i", coins);
                            isBuild = false; // ����� ��������� ��������
                        }
                    }
                    else if (isSelect == 4)
                    {
                        if (fountain.build(42, pos.x, pos.y))
                        {
                            isSelect = 0;
                            coins -= 1000;
                            sprintf(money, "%i", coins);
                            isBuild = false; // ����� ��������� ��������
                        }
                    }
                    else if (isSelect == 5)
                    {
                        if (tower.build(53, pos.x, pos.y))
                        {
                            isSelect = 0;
                            coins -= 1000;
                            sprintf(money, "%i", coins);
                            isBuild = false; // ����� ��������� ��������
                        }
                    }
                    else if (isSelect == 6)
                    {
                        if (ambar.build(84, pos.x, pos.y)) // R = 84  �������� ��� � ����� ��������� ������
                        {
                            isSelect = 0;
                            coins -= 450;
                            sprintf(money, "%i", coins);
                            isBuild = false; // ����� ��������� ��������
                        }
                    }
                }
            }
            else if (event.type == Event::MouseButtonReleased)
            {
                if (event.key.code == Mouse::Left)
                {
                    released_LKM_X = pos.x;
                    released_LKM_Y = pos.y;

                    // ����������� ������ ���� �� ����-����� (����� ��������� "pos.y < (posWindow.y + 717)" � ��������� ������� ������ � ������)
                    //if(pow(pressed_LKM_X - released_LKM_X, 2) + pow(pressed_LKM_Y - released_LKM_Y, 2) < 100) // ��� ��� ��������
                    if(pressed_LKM_X == released_LKM_X && pressed_LKM_Y == released_LKM_Y) // ��� ��� ��������
                    {
                        if(pow(pos.x - (posWindow.x + 130), 2) + pow(pos.y - (posWindow.y + 634), 2) <= 12100)
                        {
                            if(pos.x < (posWindow.x + 95) && pos.y < (posWindow.y + 600)) // tp LU
                            {
                                view.reset(FloatRect(-1500, -850, 1366, 768));
                            }
                            else if(pos.x > (posWindow.x + 165) && pos.y < (posWindow.y + 600)) // tp RU
                            {
                                view.reset(FloatRect(1500, -850, 1366, 768));
                            }
                            else if(pos.x > (posWindow.x + 165) && pos.y > (posWindow.y + 660) && pos.y < (posWindow.y + 717)) // tp RD
                            {
                                view.reset(FloatRect(1500, 850, 1366, 768));
                            }
                            else if(pos.x < (posWindow.x + 95) && pos.y > (posWindow.y + 660) && pos.y < (posWindow.y + 717)) // tp LD
                            {
                                view.reset(FloatRect(-1500, 850, 1366, 768));
                            }
                            else if(pos.x < (posWindow.x + 95) && pos.y < (posWindow.y + 717)) // tp L
                            {
                                view.reset(FloatRect(-1500, 0, 1366, 768));
                            }
                            else if(pos.x > (posWindow.x + 165) && pos.y < (posWindow.y + 717)) // tp R
                            {
                                view.reset(FloatRect(1500, 0, 1366, 768));
                            }
                            else if(pos.y < (posWindow.y + 600)) // tp U
                            {
                                view.reset(FloatRect(0, -850, 1366, 768));
                            }
                            else if(pos.y > (posWindow.y + 660) && pos.y < (posWindow.y + 717)) // tp D
                            {
                                view.reset(FloatRect(0, 850, 1366, 768));
                            }
                            else // tp Centre
                            {
                                if(pos.y < (posWindow.y + 717))
                                {
                                    view.reset(FloatRect(0, 0, 1366, 768));
                                }
                            }
                        }
                    }


                    for (it = heros.begin(); it != heros.end(); it++)
                    {
                        (*it)->selectHero(pressed_LKM_X, pressed_LKM_Y, released_LKM_X, released_LKM_Y);
                    }

                    pressed_rectangle = false;
                    rectangle.setSize(Vector2f(0, 0));
                    window.display();

                    pressed_selection_building = true;

                    // ����� ������� ������� �����
                    if (pressed_selection == true)
                    {
                        if ( (((pos.x - 603)*(pos.x - 603)) + ((pos.y - 266)*(pos.y - 266))) <= 1225 )
                        {
                            if(coins >= 50)
                            {
                                cave.createAndMove(window, pos.x, pos.y);
                                isSelect = 1;
                                isBuild = true; // ����� ��������� �������
                            }
                        }
                        else if ( (((pos.x - 747)*(pos.x - 747)) + ((pos.y - 266)*(pos.y - 266))) <= 1225 )
                        {
                            if(coins >= 250)
                            {
                                building.createAndMove(window, pos.x, pos.y);
                                isSelect = 2;
                                isBuild = true; // ����� ��������� �������
                            }
                        }
                        else if ( (((pos.x - 819)*(pos.x - 819)) + ((pos.y - 384)*(pos.y - 384))) <= 1225 )
                        {
                            if(coins >= 250)
                            {
                                house.createAndMove(window, pos.x, pos.y);
                                isSelect = 3;
                                isBuild = true; // ����� ��������� �������
                            }
                        }
                        else if ( (((pos.x - 747)*(pos.x - 747)) + ((pos.y - 504)*(pos.y - 504))) <= 1225 )
                        {
                            if(coins >= 1000)
                            {
                                fountain.createAndMove(window, pos.x, pos.y);
                                isSelect = 4;
                                isBuild = true; // ����� ��������� �������
                            }
                        }
                        else if ( (((pos.x - 603)*(pos.x - 603)) + ((pos.y - 504)*(pos.y - 504))) <= 1225 )
                        {
                            if(coins >= 1000)
                            {
                                tower.createAndMove(window, pos.x, pos.y);
                                isSelect = 5;
                                isBuild = true; // ����� ��������� �������
                            }
                        }
                        else if ( (((pos.x - 531)*(pos.x - 531)) + ((pos.y - 384)*(pos.y - 384))) <= 1225 )
                        {
                            if(coins >= 450)
                            {
                                ambar.createAndMove(window, pos.x, pos.y);
                                isSelect = 6;
                                isBuild = true; // ����� ��������� �������
                            }
                        }

                        pressed_selection = false;
                        pressed_selection_building = false;
                    }
                    else if ( (((pos.x - 683)*(pos.x - 683)) + ((pos.y - 410)*(pos.y - 410))) <= 11025 )
                    {
                        pressed_selection = true;
                    }

                    if(pressed_selection_building  == true)
                    {
                        if (indexCave != -1)
                        {
                            if ( (((pos.x - cave.getX(indexCave))*(pos.x  - cave.getX(indexCave))) + ((pos.y - (cave.getY(indexCave) - 50))*(pos.y - (cave.getY(indexCave) - 50)))) <= 950 )
                            {
                                if (coins >= 1000 && cave.getCoinsByID(indexCave) < 100)
                                {
                                    coins -= 1000;
                                    cave.setCoins(indexCave, 15);
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - cave.getX(indexCave))*(pos.x  - cave.getX(indexCave))) + ((pos.y - (cave.getY(indexCave) + 50))*(pos.y - (cave.getY(indexCave) + 50)))) <= 950 )
                            {
                                coins += 25;
                                sprintf(money, "%i", coins);
                                cave.deleteBuildingIndex(indexCave);
                            }

                            // ����� ������� "�����" ������� �����
                            indexCave = -1;
                        }
                        else if (indexBuilding != -1)
                        {
                            if ( (((pos.x - building.getX(indexBuilding))*(pos.x  - building.getX(indexBuilding))) + ((pos.y - (building.getY(indexBuilding) - 50))*(pos.y - (building.getY(indexBuilding) - 50)))) <= 950 )
                            {
                                if (coins >= 2000 && building.getCoinsByID(indexBuilding) < 500)
                                {
                                    coins -= 2000;
                                    building.setCoins(indexBuilding, 25);
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - building.getX(indexBuilding))*(pos.x  - building.getX(indexBuilding))) + ((pos.y - (building.getY(indexBuilding) + 50))*(pos.y - (building.getY(indexBuilding) + 50)))) <= 950 )
                            {
                                coins += 125;
                                sprintf(money, "%i", coins);
                                building.deleteBuildingIndex(indexBuilding);
                            }

                            // ����� ������� "�����" ������� �����
                            indexBuilding = -1;
                        }
                        else if (indexHouse != -1)
                        {
                            int deltaArmor = house.getDeltaArmor(indexHouse);

                            if ( (((pos.x - (house.getX(indexHouse) - 48))*(pos.x  - (house.getX(indexHouse) - 48))) + ((pos.y - (house.getY(indexHouse) - 50))*(pos.y - (house.getY(indexHouse) - 50)))) <= 950 )
                            {//�� �������� �� ������� �����
                                if (coins >= 1500)
                                {
                                    coins -= 1500;
                                    sprintf(money, "%i", coins);

                                    for (it = heros.begin(); it != heros.end(); it++)
                                    {
                                        (*it)->setArmor(deltaArmor);
                                    }
                                }
                            }
                            else if ( (((pos.x - (house.getX(indexHouse) + 48))*(pos.x  - (house.getX(indexHouse) + 48))) + ((pos.y - (house.getY(indexHouse) - 50))*(pos.y - (house.getY(indexHouse) - 50)))) <= 950 )
                            {//�� �������� �� ������� �����
                                if (coins >= 2500 && deltaArmor < 3)
                                {
                                    coins -= 2500;
                                    house.setDeltaArmor(indexHouse, deltaArmor + 1);
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - house.getX(indexHouse))*(pos.x  - house.getX(indexHouse))) + ((pos.y - (house.getY(indexHouse) + 50))*(pos.y - (house.getY(indexHouse) + 50)))) <= 950 )
                            {
                                coins += 125;
                                sprintf(money, "%i", coins);
                                house.deleteBuildingIndex(indexHouse);
                            }

                            // ����� ������� "�����" ������� �����
                            indexHouse = -1;
                        }
                        else if (indexFountain != -1)
                        {
                            if ( (((pos.x - fountain.getX(indexFountain))*(pos.x  - fountain.getX(indexFountain))) + ((pos.y - (fountain.getY(indexFountain) - 50))*(pos.y - (fountain.getY(indexFountain) - 50)))) <= 950 )
                            {
                                if (coins >= 2000 && fountain.getRadius(indexFountain) < 200)
                                {
                                    coins -= 2000;
                                    fountain.setRadius(indexFountain, fountain.getRadius(indexFountain) + 10);
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - fountain.getX(indexFountain))*(pos.x  - fountain.getX(indexFountain))) + ((pos.y - (fountain.getY(indexFountain) + 50))*(pos.y - (fountain.getY(indexFountain) + 50)))) <= 950 )
                            {
                                coins += 500;
                                sprintf(money, "%i", coins);
                                fountain.deleteBuildingIndex(indexFountain);
                            }

                            // ����� ������� "�����" ������� �����
                            indexFountain = -1;
                        }
                        else if (indexTower != -1)
                        {
                            if ( (((pos.x - tower.getX(indexTower))*(pos.x  - tower.getX(indexTower))) + ((pos.y - (tower.getY(indexTower) - 50))*(pos.y - (tower.getY(indexTower) - 50)))) <= 950 )
                            {
                                if (coins >= 2000 && tower.getRadius(indexTower) < 200)
                                {
                                    coins -= 2000;
                                    tower.setRadius(indexTower, tower.getRadius(indexTower) + 10);
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - tower.getX(indexTower))*(pos.x  - tower.getX(indexTower))) + ((pos.y - (tower.getY(indexTower) + 50))*(pos.y - (tower.getY(indexTower) + 50)))) <= 950 )
                            {
                                coins += 500;
                                sprintf(money, "%i", coins);
                                tower.deleteBuildingIndex(indexTower);
                            }

                            // ����� ������� "�����" ������� �����
                            indexTower = -1;
                        }
                        else if (indexAmbar != -1)
                        {
                            if ( (((pos.x - (ambar.getX(indexAmbar) - 48))*(pos.x  - (ambar.getX(indexAmbar) - 48))) + ((pos.y - (ambar.getY(indexAmbar) - 50))*(pos.y - (ambar.getY(indexAmbar) - 50)))) <= 950 )
                            {//�� �������� �� ������� �����
                                if (coins >= 2500 && heros.size() < MAX_COUNT_HEROS)
                                {
                                    coins -= 2500;
                                    heros.push_back(new Player(imagePlayer.sprite, scaleUpdate.sprite, scaleArmor.sprite, db, "Heros", heros.size(), ambar.getX(indexAmbar) + 150, ambar.getY(indexAmbar), 40, 40));

                                    it = heros.end();
                                    it--;
                                    (*it)->setArmor(3);

                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - (ambar.getX(indexAmbar) + 48))*(pos.x  - (ambar.getX(indexAmbar) + 48))) + ((pos.y - (ambar.getY(indexAmbar) - 50))*(pos.y - (ambar.getY(indexAmbar) - 50)))) <= 950 )
                            {//�� �������� �� ������� �����
                                if (coins >= 1000 && heros.size() < MAX_COUNT_HEROS - 1)
                                {
                                    coins -= 1000;
                                    heros.push_back(new Player(imagePlayer.sprite, scaleUpdate.sprite, scaleArmor.sprite, db, "Heros", heros.size(), ambar.getX(indexAmbar) + 150, ambar.getY(indexAmbar), 40, 40));
                                    heros.push_back(new Player(imagePlayer.sprite, scaleUpdate.sprite, scaleArmor.sprite, db, "Heros", heros.size(), ambar.getX(indexAmbar) + 150, ambar.getY(indexAmbar) + 40, 40, 40));
                                    sprintf(money, "%i", coins);
                                }
                            }
                            else if ( (((pos.x - ambar.getX(indexAmbar))*(pos.x  - ambar.getX(indexAmbar))) + ((pos.y - (ambar.getY(indexAmbar) + 50))*(pos.y - (ambar.getY(indexAmbar) + 50)))) <= 950 )
                            {
                                coins += 225;
                                sprintf(money, "%i", coins);
                                ambar.deleteBuildingIndex(indexAmbar);
                            }

                            // ����� ������� "�����" ������� �����
                            indexAmbar = -1;
                        }
                        else
                        {
                            // ����� ������� "�����" ������� �����
                            indexCave = cave.checkPosition(pos.x, pos.y);
                            indexBuilding = building.checkPosition(pos.x, pos.y);
                            indexHouse = house.checkPosition(pos.x, pos.y);
                            indexTower = tower.checkPosition(pos.x, pos.y);
                            indexFountain = fountain.checkPosition(pos.x, pos.y);
                            indexAmbar = ambar.checkPosition(pos.x, pos.y);

                            if(indexCave != -1 || indexBuilding != -1 ||
                               indexHouse != -1 || indexTower != -1 ||
                               indexFountain != -1 || indexAmbar != -1
                            )
                            {
                                isHelpText = false;
                            }
                        }
                    }
                }
            }
        }

        if (pos.x > -1500 && pos.x < 2866 && pos.y > -850 && pos.y < 1618)
        {
            if (pixelPos.x >= 1365)
            {
                view.move(0.3*time, 0);
            }
            if (pixelPos.y >= 767)
            {
                view.move(0, 0.3*time);
            }
            if (pixelPos.x <= 0)
            {
                view.move(-0.3*time, 0);
            }
            if (pixelPos.y <= 0)
            {
                view.move(0, -0.3*time);
            }
        }

        window.clear();
        window.setView(view);
        window.draw(background.sprite);

        // �������� ������ �����
        Vertex lineBorder[] =
        {
            Vertex(Vector2f(-1475, -750), Color::Red),
            Vertex(Vector2f(-1475, 1593), Color::Red),

            Vertex(Vector2f(2841, -750), Color::Red),
            Vertex(Vector2f(2841, 1593), Color::Red),

            Vertex(Vector2f(-1475, -750), Color::Red),
            Vertex(Vector2f(2841, -750), Color::Red),

            Vertex(Vector2f(-1475, 1593), Color::Red),
            Vertex(Vector2f(2841, 1593), Color::Red)
        };
        window.draw(lineBorder, 8, Lines);

        window.draw(castle.sprite);

        if(isBuild == true) build(window);

        // ���������� ��������
        cave.moveAndDraw(window, 41, pos.x, pos.y);
        building.moveAndDraw(window, 50, pos.x, pos.y);
        house.moveAndDraw(window, 69, pos.x, pos.y);
        fountain.moveAndDraw(window, 42, pos.x, pos.y);
        tower.moveAndDraw(window, 53, pos.x, pos.y);
        ambar.moveAndDraw(window, 220, pos.x, pos.y); // R = 84  �������� ��� � ����� ��������� ������

        cave.drawScale(window);
        building.drawScale(window);
        house.drawScale(window);
        fountain.drawScale(window);
        tower.drawScale(window);
        ambar.drawScale(window);

        // ��������� ��������
        EnemyCastle.draw(window);
        boiler.draw(window);
        //EnemyTower.draw(window);

        for (it = heros.begin(); it != heros.end(); it++)
        {
			(*it)->updateHero(time);
		}

        if (pressed_rectangle == true)
        {
            rectangle.setPosition(pressed_LKM_X, pressed_LKM_Y);
            rectangle.setSize(Vector2f(pos.x - pressed_LKM_X, pos.y - pressed_LKM_Y));
        }

        for (it = heros.begin(); it != heros.end(); it++)
        {
			(*it)->drawHero(window);
		}

        ////// Enemy
        for (itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++)
        {
			(*itEnemy)->updateEnemy(time);
		}
        for (itEnemy = enemy.begin(); itEnemy != enemy.end(); itEnemy++)
        {
			(*itEnemy)->drawEnemy(window);
		}
        ////// Enemy

        window.draw(rectangle);

        // ���������� ������� "�����" ��� ������� �� ������
        if((pressed_selection_building  == true) && (pow(pressed_LKM_X - released_LKM_X, 2) + pow(pressed_LKM_Y - released_LKM_Y, 2) < 100))
        {   // ������ ��� ���� ��� �� ��� ���������� ��������� �� ��������� ������ // �������� ��� ��������: pressed_LKM_X == released_LKM_X && pressed_LKM_Y == released_LKM_Y
            if (indexCave != -1)
            {
                selection2.sprite.setPosition(cave.getX(indexCave), cave.getY(indexCave));
                window.draw(selection2.sprite);

                if (cave.getCoinsByID(indexCave) >= 100) selectionNot.sprite.setColor(Color::Black);
                if (coins < 1000 || cave.getCoinsByID(indexCave) >= 100)
                {
                    selectionNot.x = cave.getX(indexCave);
                    selectionNot.y = cave.getY(indexCave) - 50;
                    selectionNot.sprite.setPosition(selectionNot.x, selectionNot.y);
                    window.draw(selectionNot.sprite);
                }
            }
            if (indexBuilding != -1)
            {
                selection2.sprite.setPosition(building.getX(indexBuilding), building.getY(indexBuilding));
                window.draw(selection2.sprite);

                if (building.getCoinsByID(indexBuilding) >= 500) selectionNot.sprite.setColor(Color::Black);
                if (coins < 2000 || building.getCoinsByID(indexBuilding) >= 500)
                {
                    selectionNot.x = building.getX(indexBuilding);
                    selectionNot.y = building.getY(indexBuilding) - 50;
                    selectionNot.sprite.setPosition(selectionNot.x, selectionNot.y);
                    window.draw(selectionNot.sprite);
                }
            }
            if (indexHouse != -1)
            {
                selection3House.sprite.setPosition(house.getX(indexHouse), house.getY(indexHouse));
                window.draw(selection3House.sprite);

                if (coins < 1500)
                {
                    selectionNot.x = house.getX(indexHouse) - 48;
                    selectionNot.y = house.getY(indexHouse) - 50;
                    selectionNot.sprite.setPosition(selectionNot.x, selectionNot.y);
                    window.draw(selectionNot.sprite);
                }

                if (house.getDeltaArmor(indexHouse) >= 3) selectionNotAddition.sprite.setColor(Color::Black);
                if (coins < 2500 || house.getDeltaArmor(indexHouse) >= 3)
                {
                    selectionNotAddition.x = house.getX(indexHouse) + 48;
                    selectionNotAddition.y = house.getY(indexHouse) - 50;
                    selectionNotAddition.sprite.setPosition(selectionNotAddition.x, selectionNotAddition.y);
                    window.draw(selectionNotAddition.sprite);
                }
            }
            if (indexFountain != -1)
            {
                selection2.sprite.setPosition(fountain.getX(indexFountain), fountain.getY(indexFountain));
                window.draw(selection2.sprite);

                // ��������� ������� �������
                CircleShape shape(fountain.getRadius(indexFountain));
                shape.setFillColor(Color::Transparent);
                shape.setOutlineThickness(2);
                shape.setOutlineColor(Color(255, 255, 255, 80));

                shape.setOrigin(fountain.getRadius(indexFountain), fountain.getRadius(indexFountain));
                shape.setPosition(fountain.getX(indexFountain), fountain.getY(indexFountain));
                window.draw(shape);

                if (fountain.getRadius(indexFountain) >= 200) selectionNot.sprite.setColor(Color::Black);
                if (coins < 2000 || fountain.getRadius(indexFountain) >= 200)
                {
                    selectionNot.x = fountain.getX(indexFountain);
                    selectionNot.y = fountain.getY(indexFountain) - 50;
                    selectionNot.sprite.setPosition(selectionNot.x, selectionNot.y);
                    window.draw(selectionNot.sprite);
                }
            }
            if (indexTower != -1)
            {
                selection2.sprite.setPosition(tower.getX(indexTower), tower.getY(indexTower));
                window.draw(selection2.sprite);

                // ��������� ������� ��������
                CircleShape shape(tower.getRadius(indexTower));
                shape.setFillColor(Color::Transparent);
                shape.setOutlineThickness(2);
                shape.setOutlineColor(Color(255, 255, 255, 80));

                shape.setOrigin(tower.getRadius(indexTower), tower.getRadius(indexTower));
                shape.setPosition(tower.getX(indexTower), tower.getY(indexTower));
                window.draw(shape);

                if (tower.getRadius(indexTower) >= 200) selectionNot.sprite.setColor(Color::Black);
                if (coins < 2000 || tower.getRadius(indexTower) >= 200)
                {
                    selectionNot.x = tower.getX(indexTower);
                    selectionNot.y = tower.getY(indexTower) - 50;
                    selectionNot.sprite.setPosition(selectionNot.x, selectionNot.y);
                    window.draw(selectionNot.sprite);
                }
            }
            if (indexAmbar != -1)
            {
                selection3Ambar.sprite.setPosition(ambar.getX(indexAmbar), ambar.getY(indexAmbar));
                window.draw(selection3Ambar.sprite);

                if (heros.size() >= MAX_COUNT_HEROS) selectionNot.sprite.setColor(Color::Black);
                if (coins < 2500 || heros.size() >= MAX_COUNT_HEROS)
                {
                    selectionNot.x = ambar.getX(indexAmbar) - 48;
                    selectionNot.y = ambar.getY(indexAmbar) - 50;
                    selectionNot.sprite.setPosition(selectionNot.x, selectionNot.y);
                    window.draw(selectionNot.sprite);
                }

                if (heros.size() >= MAX_COUNT_HEROS - 1) selectionNotAddition.sprite.setColor(Color::Black);
                if (coins < 1000 || heros.size() >= MAX_COUNT_HEROS - 1)
                {
                    selectionNotAddition.x = ambar.getX(indexAmbar) + 48;
                    selectionNotAddition.y = ambar.getY(indexAmbar) - 50;
                    selectionNotAddition.sprite.setPosition(selectionNotAddition.x, selectionNotAddition.y);
                    window.draw(selectionNotAddition.sprite);
                }
            }
        }

        // ���������� ������� "�����" ��� ������� �� ������ "�����"
        if((pressed_selection == true) && (pow(pressed_LKM_X - released_LKM_X, 2) + pow(pressed_LKM_Y - released_LKM_Y, 2) < 100)) // pressed_LKM_X == released_LKM_X && pressed_LKM_Y == released_LKM_Y
        {   // ������ ��� ���� ��� �� ��� ���������� ��������� �� ��������� ����� // �������� ��� ��������: pressed_LKM_X == released_LKM_X && pressed_LKM_Y == released_LKM_Y
            window.draw(selection.sprite);

            if(cave.getIndex() == 4)
            {
                selectionNot1.sprite.setColor(Color::Black);
                window.draw(selectionNot1.sprite);
            }
            else if(coins < 50)
            {
                selectionNot1.sprite.setColor(Color::White);
                window.draw(selectionNot1.sprite);
            }

            if(building.getIndex() == 4)
            {
                selectionNot2.sprite.setColor(Color::Black);
                window.draw(selectionNot2.sprite);
            }
            else if(coins < 250)
            {
                selectionNot2.sprite.setColor(Color::White);
                window.draw(selectionNot2.sprite);
            }

            if(house.getIndex() == 4)
            {
                selectionNot3.sprite.setColor(Color::Black);
                window.draw(selectionNot3.sprite);
            }
            else if(coins < 250)
            {
                selectionNot3.sprite.setColor(Color::White);
                window.draw(selectionNot3.sprite);
            }

            if(fountain.getIndex() == 4)
            {
                selectionNot4.sprite.setColor(Color::Black);
                window.draw(selectionNot4.sprite);
            }
            else if(coins < 1000)
            {
                selectionNot4.sprite.setColor(Color::White);
                window.draw(selectionNot4.sprite);
            }

            if(tower.getIndex() == 4)
            {
                selectionNot5.sprite.setColor(Color::Black);
                window.draw(selectionNot5.sprite);
            }
            else if(coins < 1000)
            {
                selectionNot5.sprite.setColor(Color::White);
                window.draw(selectionNot5.sprite);
            }

            if(ambar.getIndex() == 4)
            {
                selectionNot6.sprite.setColor(Color::Black);
                window.draw(selectionNot6.sprite);
            }
            else if(coins < 450)
            {
                selectionNot6.sprite.setColor(Color::White);
                window.draw(selectionNot6.sprite);
            }
        }


        // ���������� ������������ ������
        pixelPosWindow = window.getPosition();
        posWindow = window.mapPixelToCoords(pixelPosWindow);

        miniMap.sprite.setPosition(posWindow.x, posWindow.y + 510);
        window.draw(miniMap.sprite);

        text.setColor(Color::White);
        text.setString(money);
        text.setPosition(posWindow.x + 53, posWindow.y + 721);
        window.draw(text);

        // ����� ���������
        if(options.checkOffHelp == 1)
        {
            help = "";

            if (indexCave != -1)
            {
                if ( (((pos.x - cave.getX(indexCave))*(pos.x  - cave.getX(indexCave))) + ((pos.y - (cave.getY(indexCave) - 50))*(pos.y - (cave.getY(indexCave) - 50)))) <= 950 )
                {
                    help = "�������� �������������� (-1000$)";
                }
                else if ( (((pos.x - cave.getX(indexCave))*(pos.x  - cave.getX(indexCave))) + ((pos.y - (cave.getY(indexCave) + 50))*(pos.y - (cave.getY(indexCave) + 50)))) <= 950 )
                {
                    help = "�������";
                }
            }
            else if (indexBuilding != -1)
            {
                if ( (((pos.x - building.getX(indexBuilding))*(pos.x  - building.getX(indexBuilding))) + ((pos.y - (building.getY(indexBuilding) - 50))*(pos.y - (building.getY(indexBuilding) - 50)))) <= 950 )
                {
                    help = "�������� �������������� (-2000$)";
                }
                else if ( (((pos.x - building.getX(indexBuilding))*(pos.x  - building.getX(indexBuilding))) + ((pos.y - (building.getY(indexBuilding) + 50))*(pos.y - (building.getY(indexBuilding) + 50)))) <= 950 )
                {
                    help = "�������";
                }
            }
            else if (indexHouse != -1)
            {
                if ( (((pos.x - (house.getX(indexHouse) - 48))*(pos.x  - (house.getX(indexHouse) - 48))) + ((pos.y - (house.getY(indexHouse) - 50))*(pos.y - (house.getY(indexHouse) - 50)))) <= 950 )
                {
                    help = "�������� ����������� ��������� (-1500$)";
                }
                else if ( (((pos.x - (house.getX(indexHouse) + 48))*(pos.x  - (house.getX(indexHouse) + 48))) + ((pos.y - (house.getY(indexHouse) - 50))*(pos.y - (house.getY(indexHouse) - 50)))) <= 950 )
                {
                    help = "�������� �������������� (-2500$)";
                }
                else if ( (((pos.x - house.getX(indexHouse))*(pos.x  - house.getX(indexHouse))) + ((pos.y - (house.getY(indexHouse) + 50))*(pos.y - (house.getY(indexHouse) + 50)))) <= 950 )
                {
                    help = "�������";
                }
            }
            else if (indexFountain != -1)
            {
                if ( (((pos.x - fountain.getX(indexFountain))*(pos.x  - fountain.getX(indexFountain))) + ((pos.y - (fountain.getY(indexFountain) - 50))*(pos.y - (fountain.getY(indexFountain) - 50)))) <= 950 )
                {
                    help = "�������� �������������� (-2000$)";
                }
                else if ( (((pos.x - fountain.getX(indexFountain))*(pos.x  - fountain.getX(indexFountain))) + ((pos.y - (fountain.getY(indexFountain) + 50))*(pos.y - (fountain.getY(indexFountain) + 50)))) <= 950 )
                {
                    help = "�������";
                }
            }
            else if (indexTower != -1)
            {
                if ( (((pos.x - tower.getX(indexTower))*(pos.x  - tower.getX(indexTower))) + ((pos.y - (tower.getY(indexTower) - 50))*(pos.y - (tower.getY(indexTower) - 50)))) <= 950 )
                {
                    help = "�������� �������������� (-2000$)";
                }
                else if ( (((pos.x - tower.getX(indexTower))*(pos.x  - tower.getX(indexTower))) + ((pos.y - (tower.getY(indexTower) + 50))*(pos.y - (tower.getY(indexTower) + 50)))) <= 950 )
                {
                    help = "�������";
                }
            }
            else if (indexAmbar != -1)
            {
                if ( (((pos.x - (ambar.getX(indexAmbar) - 48))*(pos.x  - (ambar.getX(indexAmbar) - 48))) + ((pos.y - (ambar.getY(indexAmbar) - 50))*(pos.y - (ambar.getY(indexAmbar) - 50)))) <= 950 )
                {
                    help = "�������� ����� (-2500$)";
                }
                else if ( (((pos.x - (ambar.getX(indexAmbar) + 48))*(pos.x  - (ambar.getX(indexAmbar) + 48))) + ((pos.y - (ambar.getY(indexAmbar) - 50))*(pos.y - (ambar.getY(indexAmbar) - 50)))) <= 950 )
                {
                    help = "�������� ����� (-1000$)";
                }
                else if ( (((pos.x - ambar.getX(indexAmbar))*(pos.x  - ambar.getX(indexAmbar))) + ((pos.y - (ambar.getY(indexAmbar) + 50))*(pos.y - (ambar.getY(indexAmbar) + 50)))) <= 950 )
                {
                    help = "�������";
                }
            }

            if (isBuild == true)
            {
                help = "��� ���������� ������� ������ ������ ����";
            }
            else if (pressed_selection == true)
            {
                if ( (((pos.x - 603)*(pos.x - 603)) + ((pos.y - 266)*(pos.y - 266))) <= 1225 ) help = "�������� ������� � ������� 25 ������ (-50$). ��� ������ ������� ����� ������ ����";
                else if ( (((pos.x - 747)*(pos.x - 747)) + ((pos.y - 266)*(pos.y - 266))) <= 1225 ) help = "�������� ������� � ������� 50 ������ (-250$). ��� ������ ������� ����� ������ ����";
                else if ( (((pos.x - 819)*(pos.x - 819)) + ((pos.y - 384)*(pos.y - 384))) <= 1225 ) help = "�������� ����������� ��������� (-250$). ��� ������ ������� ����� ������ ����";
                else if ( (((pos.x - 747)*(pos.x - 747)) + ((pos.y - 504)*(pos.y - 504))) <= 1225 ) help = "�������� �������� ��������� �� ����������� ���������� (-1000$). ��� ������ ������� ����� ������ ����";
                else if ( (((pos.x - 603)*(pos.x - 603)) + ((pos.y - 504)*(pos.y - 504))) <= 1225 ) help = "������� ���� ����� �� ����������� ���������� (-1000$). ��� ������ ������� ����� ������ ����";
                else if ( (((pos.x - 531)*(pos.x - 531)) + ((pos.y - 384)*(pos.y - 384))) <= 1225 ) help = "������� ���������� (-450$). ��� ������ ������� ����� ������ ����";
            }
            else if (pressed_selection == false)
            {
                if ( (((pos.x - 683)*(pos.x - 683)) + ((pos.y - 410)*(pos.y - 410))) <= 11025 )
                {
                    help = "��� ������ ������� ����� ������ ����";
                }
                else if (isHelpText == true)
                {
                    if (cave.checkPosition(pos.x, pos.y) != -1) help = "��� ������ ������� ����� ������ ����";
                    else if (building.checkPosition(pos.x, pos.y) != -1) help = "��� ������ ������� ����� ������ ����";
                    else if (house.checkPosition(pos.x, pos.y) != -1) help = "��� ������ ������� ����� ������ ����";
                    else if (tower.checkPosition(pos.x, pos.y) != -1) help = "��� ������ ������� ����� ������ ����";
                    else if (fountain.checkPosition(pos.x, pos.y) != -1) help = "��� ������ ������� ����� ������ ����";
                    else if (ambar.checkPosition(pos.x, pos.y) != -1) help = "��� ������ ������� ����� ������ ����";
                }
            }

            helpText.setColor(Color::White);
            helpText.setString(help);
            helpText.setPosition(posWindow.x + 1300 - help.size() * 9, posWindow.y + 10); // ������� �� ����� ������

            rect.setPosition(posWindow.x + 1280 - help.size() * 9, posWindow.y);
            rect.setSize(Vector2f(1000, 55));

            if (help.size() != 0) window.draw(rect);
            window.draw(helpText);
        }

        // �������� �� ����-�����
        Vertex lineMiniMap[] =
        {
            Vertex(Vector2f(posWindow.x + 95, posWindow.y + 531)),
            Vertex(Vector2f(posWindow.x + 95, posWindow.y + 716)),

            Vertex(Vector2f(posWindow.x + 165, posWindow.y + 530)),
            Vertex(Vector2f(posWindow.x + 165, posWindow.y + 716)),

            Vertex(Vector2f(posWindow.x + 26, posWindow.y + 600)),
            Vertex(Vector2f(posWindow.x + 235, posWindow.y + 600)),

            Vertex(Vector2f(posWindow.x + 22, posWindow.y + 660)),
            Vertex(Vector2f(posWindow.x + 238, posWindow.y + 660))
        };
        window.draw(lineMiniMap, 8, Lines);

        window.display();
    }

    char sqlQueryMap[] = "DELETE FROM Map WHERE Name <> ?;";
    db.clearData(sqlQueryMap); // ������� ��� ������� � ���� ������, ����� �������� �����
    char sqlQueryPlayer[] = "DELETE FROM Player;";
    db.clearData(sqlQueryPlayer); // ������� ���� ���������� � ���� ������
}

int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "Menu", Style::Fullscreen);
    window.setFramerateLimit(50);

    menu(window);

    window.close();
    return 0;
}

/*
void renderingThread(sf::RenderWindow* window)
{
     ////shape////
    CircleShape shape(50);
    shape.setFillColor(Color::Transparent);

    shape.setOrigin(50, 50);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(Color(250, 150, 100));
    shape.setPosition(150, 150);
    // ���� ������������
    int i = 0;
    while (window->isOpen())
    {
    // ������...
    window->clear();
    //Sleep(1000);
    shape.setPosition(150, 150);
    window->draw(shape);
    // ����� �������� �����
    window->display();
    }
}

int main()
{
     // ������ ���� (�������: ���������� ����� ��������� ��� � ������� ������ �� �� ����������� ��)
     sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL");

     // ������������ �������� OpenGL
     window.setActive(false);

     // ������ ������������ � ������
     sf::Thread thread(&renderingThread, &window);
     thread.launch();
        int i = 0;
     // ���� ��������� �������, ������ � �������..
     while (window.isOpen())
     {
       Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        cout<<i++<<endl;
     }

    return 0;
}*/
