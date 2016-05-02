#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <cmath>

#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

double length(int x1, int y1, int x2, int y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void saveMap(int R, int x, int y)
{
    ofstream fout("map.txt", std::ios_base::app);
    fout << "R = " << R << "; x = " << x << "; y = " << y << "\n";
    fout.close();
}

void fileMapCleaning()
{
	fstream file;
	file.open("map.txt", ios::out);
	file << "";
	file.close();
}

#include "map.h"

#define MAX_SPEED 0.05

using namespace std;
using namespace sf;


class Images
{
public:             // private
    int x;
    int y;

    int w;
    int h;
    //int originX;
    //int originY;    // public
    //String File;
    Image image;
    Texture texture;
    Sprite sprite;

    Images(String file, int positionX = 0, int positionY = 0, int width = 0, int height = 0)
    {
        //File = file;
        image.loadFromFile(file);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setPosition(positionX, positionY);
        x = positionX;
        y = positionY;
        w = width;
        h = height;
        sprite.setOrigin(Vector2f(w/2, h/2));
    }
};

void menu(RenderWindow & window);
void game(RenderWindow & window);
void settings(RenderWindow & window);

void menu(RenderWindow & window)
{
    Images Background("Background.png");
    Images NewGame("NewGame.png");
    Images LoadGame("LoadGame.png");
    Images SettingsGame("SettingsGame.png");
    Images QuitGame("QuitGame.png");

    bool isMenu = true;
    int menuNum = 0;

    while (isMenu)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        NewGame.sprite.setColor(Color::White);
        LoadGame.sprite.setColor(Color::White);
        SettingsGame.sprite.setColor(Color::White);
        QuitGame.sprite.setColor(Color::White);

        menuNum = 0;
        //window.clear(Color(129, 181, 221)); // Зачем ?

        if (IntRect(222, 252, 245, 78).contains(Mouse::getPosition(window)))
        {
            NewGame.sprite.setColor(Color(230, 100, 200));
            menuNum = 1;
        }
        else if (IntRect(222, 340, 245, 78).contains(Mouse::getPosition(window)))
        {
            LoadGame.sprite.setColor(Color(230, 100, 200));
            menuNum = 2;
        }
        else if (IntRect(222, 428, 245, 78).contains(Mouse::getPosition(window)))
        {
            SettingsGame.sprite.setColor(Color(230, 100, 200));
            menuNum = 3;
        }
        else if (IntRect(222, 516, 245, 78).contains(Mouse::getPosition(window)))
        {
            QuitGame.sprite.setColor(Color(230, 100, 200));
            menuNum = 4;
        }


        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1)
            {
                game(window);
            }
            else if (menuNum == 2)
            {
                window.display();
                while (!Keyboard::isKeyPressed(Keyboard::Escape));
            }
            else if (menuNum == 3)
            {
                settings(window);
            }
            else if (menuNum == 4)
            {
                isMenu = false;
            }
        }

        window.draw(Background.sprite);
        window.draw(NewGame.sprite);
        window.draw(LoadGame.sprite);
        window.draw(SettingsGame.sprite);
        window.draw(QuitGame.sprite);

        window.display();
    }
}

void settings(RenderWindow & window)
{
    Images Settings("Settings.png");
    Images SettingsBackground("SettingsBackground.png");

    while (!Keyboard::isKeyPressed(Keyboard::Escape))
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.draw(SettingsBackground.sprite);
        window.draw(Settings.sprite);
        window.display();
    }
}

class ImagesBuild
{
public:             // private
    int x;
    int y;

    int w;
    int h;
    //int originX;
    //int originY;    // public
    //String File;
    Image image;
    Texture texture;
    Sprite sprite;

    bool isMove = false;
    bool isCreate = false;

    ImagesBuild(String file, int positionX = 0, int positionY = 0, int width = 0, int height = 0)
    {
        //File = file;
        image.loadFromFile(file);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setPosition(positionX, positionY);
        x = positionX;
        y = positionY;
        w = width;
        h = height;
        sprite.setOrigin(Vector2f(w/2, h/2));
    }
};

class Building
{
public:
    ImagesBuild ** building;
    int maxCount;
    int index = -1;

    Building(String file, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int maxCount = 0)
    {
        this->maxCount = maxCount;
        building = new ImagesBuild* [maxCount];

        for(int i = 0; i < maxCount; i++)
        {
            building[i] = new ImagesBuild(file, positionX, positionY, width, height);
        }
    }

    ~Building()
    {
        for (int i = 0; i < maxCount; i++)
        {
            delete building[i];
        }
        delete [] building;
    }


    void createAndMove(RenderWindow & window, int posX, int posY)
    {
        if (index < maxCount - 1)
        {
            index++;
            building[index]->isMove = true;
            building[index]->isCreate = true;
            building[index]->sprite.setPosition(posX, posY);
            window.draw(building[index]->sprite);
        }
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

    void build(int Radius, int posX, int posY)
    {
        if(index > -1)
        {
            building[index]->isMove = false;
            saveMap(Radius, posX, posY);
        }
    }

    void moveAndDraw(RenderWindow & window, int posX, int posY)
    {
        for(int i = 0; i < maxCount; i++)
        {
            if (building[i]->isCreate)
            {
                if (building[i]->isMove)
                {
                    building[i]->sprite.setPosition(posX, posY);
                }
                window.draw(building[i]->sprite);
            }
        }
    }
};

void game(RenderWindow & window)
{
    //Images map("map.png");
    //Images oz("Map/OB5.png", 100, 100);
    Images miniMap("Images/miniMap2.png", 0, 510);

    Building cave("Building/cave.png", 0, 0, 90, 60, 5);
    Building building("Building/building.png", 0, 0, 95, 88, 5);
    Building house("Building/house.png", 0, 0, 140, 115, 5);
    Building fountain("Building/fountain.png", 0, 0, 60, 80, 5);
    Building tower("Building/tower.png", 0, 0, 75, 105, 5);
    Building ambar("Building/ambar.png", 0, 0, 165, 134, 5);

    Images background("Images/BGG1.png", -1500, -850);
    Images castle("Images/CASTLE.png", 683, 384, 300, 268);
    Images selection("Images/selectionDone.png", 675, 384, 365, 317);//683

    //saveMap(Radius, x, y);Castle

    /*
    char buffer[50];
    int R, x, y;

    int posX = 0;
    int posY = 0;
    int Radius = 2;

    ifstream fin("map.txt");

    while (fin.good())
    {
        fin.getline(buffer, 100);

        char * pointR = strstr(buffer, "R = ");
        pointR += 4;
        R = atoi(pointR);

        char * pointX = strstr(buffer, "x = ");
        pointX += 4;
        x = atoi(pointX);

        char * pointY = strstr(buffer, "y = ");
        pointY += 4;
        y = atoi(pointY);

        if (R + Radius < length(posX, posY, x, y))
            puts("OK");
        else
            puts("NOT OK");
    }

    fin.close();*/

    Font font;
    font.loadFromFile("CyrilicOld.ttf");
    Text text("", font, 20);

    ////shape////
    /*CircleShape shape(105);
    shape.setFillColor(Color::Transparent);

    shape.setOrigin(105, 105);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(Color(250, 150, 100));*/

    bool pressed_selection = false;
    int isSelect = 0;

    Clock clock;
    View view(FloatRect(0, 0, 1366, 768));

    while (!Keyboard::isKeyPressed(Keyboard::Escape))
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f pos = window.mapPixelToCoords(pixelPos);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    isSelect = 0;

                    cave.deleteBuilding();
                    building.deleteBuilding();
                    house.deleteBuilding();
                    fountain.deleteBuilding();
                    tower.deleteBuilding();
                    ambar.deleteBuilding();

                    if (pressed_selection == true)
                    {
                        if ( (((pos.x - 603)*(pos.x - 603)) + ((pos.y - 266)*(pos.y - 266))) <= 1225 )
                        {
                            cave.createAndMove(window, pos.x, pos.y);
                            isSelect = 1;
                        }
                        else if ( (((pos.x - 747)*(pos.x - 747)) + ((pos.y - 266)*(pos.y - 266))) <= 1225 )
                        {
                            building.createAndMove(window, pos.x, pos.y);
                            isSelect = 2;
                        }
                        else if ( (((pos.x - 819)*(pos.x - 819)) + ((pos.y - 384)*(pos.y - 384))) <= 1225 )
                        {
                            house.createAndMove(window, pos.x, pos.y);
                            isSelect = 3;
                        }
                        else if ( (((pos.x - 747)*(pos.x - 747)) + ((pos.y - 504)*(pos.y - 504))) <= 1225 )
                        {
                            fountain.createAndMove(window, pos.x, pos.y);
                            isSelect = 4;
                        }
                        else if ( (((pos.x - 603)*(pos.x - 603)) + ((pos.y - 504)*(pos.y - 504))) <= 1225 )
                        {
                            tower.createAndMove(window, pos.x, pos.y);
                            isSelect = 5;
                        }
                        else if ( (((pos.x - 531)*(pos.x - 531)) + ((pos.y - 384)*(pos.y - 384))) <= 1225 )
                        {
                            ambar.createAndMove(window, pos.x, pos.y);
                            isSelect = 6;
                        }

                        pressed_selection = false;
                    }
                    else if ( (((pos.x - 683)*(pos.x - 683)) + ((pos.y - 410)*(pos.y - 410))) <= 11025 )
                    {
                        pressed_selection = true;
                    }
                }
                if (event.key.code == Mouse::Right)
                {
                    if (isSelect == 1) cave.build(41, pos.x, pos.y);
                    if (isSelect == 2) building.build(50, pos.x, pos.y);
                    if (isSelect == 3) house.build(69, pos.x, pos.y);
                    if (isSelect == 4) fountain.build(42, pos.x, pos.y);
                    if (isSelect == 5) tower.build(53, pos.x, pos.y);
                    if (isSelect == 6) ambar.build(84, pos.x, pos.y);

                    isSelect = 0;
                }
            }
        }

        if (pos.x > -1500 && pos.x < 2866 && pos.y > -850 && pos.y < 1618)
        {
            if (pixelPos.x >= 1365)
            {
                view.move(0.3*time, 0);
                //miniMap.sprite.setPosition(miniMap.x += 0.3*time, miniMap.y);
            }
            if (pixelPos.y >= 767)
            {
                view.move(0, 0.3*time);
                //miniMap.sprite.setPosition(miniMap.x, miniMap.y += 0.3*time);
            }
            if (pixelPos.x <= 0)
            {
                view.move(-0.3*time, 0);
                //miniMap.sprite.setPosition(miniMap.x -= 0.3*time, miniMap.y);
            }
            if (pixelPos.y <= 0)
            {
                view.move(0, -0.3*time);
                //miniMap.sprite.setPosition(miniMap.x, miniMap.y -= 0.3*time);
            }
            //window.draw(miniMap.sprite);
        }

        window.clear();
        window.setView(view);
        window.draw(background.sprite);
        //window.draw(oz.sprite);
        window.draw(castle.sprite);

        cave.moveAndDraw(window, pos.x, pos.y);
        building.moveAndDraw(window, pos.x, pos.y);
        house.moveAndDraw(window, pos.x, pos.y);
        fountain.moveAndDraw(window, pos.x, pos.y);
        tower.moveAndDraw(window, pos.x, pos.y);
        ambar.moveAndDraw(window, pos.x, pos.y);


        if (pressed_selection == true)
        {
            window.draw(selection.sprite);
        }

        Vector2i pixelPosWindow = window.getPosition();
        Vector2f posWindow = window.mapPixelToCoords(pixelPosWindow);

        miniMap.sprite.setPosition(posWindow.x, posWindow.y + 510);
        window.draw(miniMap.sprite);

        text.setColor(Color::White);
        text.setString("0");
        text.setPosition(posWindow.x + 53, posWindow.y + 721);
        window.draw(text);

        window.display();
    }

    fileMapCleaning();
}

int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "Menu", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(50);

    game(window);

    window.close();
    return 0;
}









///////КЛАСС ИГРОКА///////
/*class Player
{
public:
    Image image;
    Texture texture;
    Sprite sprite;

    int x, y, w, h;

    int begX, begY;
    int endX, endY;
    int dx, dy;
    float angle;

    bool isMove, isSelect;
    float CurrentFrame;

    //float speed;
    //int dir;

    Player(String file, int positionX, int positionY, int width, int height)
    {
        x = positionX;
        y = positionY;
        w = width;
        h = height;
        image.loadFromFile(file);
        image.createMaskFromColor(Color::White);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setPosition(positionX, positionY);
        sprite.setTextureRect(IntRect(0, 200, w, h));
        sprite.setOrigin(w/2, h/2);

        CurrentFrame = 0;
        isMove = false;
        isSelect = false;

        angle = 45;
    }


    void update(float time,  int numImage, int posX, int posY)
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
        if (isSelect)
        {
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
                isSelect = false;
            }
        }
        else
        {
            stop();
        }
    }



    void mouseLeft() //stop motion
    {
        sprite.setColor(Color::White);
        isSelect = false;
        isMove = false;
    }

    void mouseRight(int posX, int posY)
    {
        if (isMove == true)
        {
            begX = x;
            begY = y;

            //endX = posX;
            //endY = posY;

            dx = endX - begX;
            dy = endY - begY;

            angle = (180 / M_PI) * atan2(float(dy), float(dx));

            sprite.setColor(Color::White);
            isMove = false;
            isSelect = true;
        }
    }

    void MRL()
    {
        isMove = true;
        sprite.setColor(Color::Red);
    }

    bool checkSelect (Player * hero, int posX, int posY, int pressed_LKM_X, int pressed_LKM_Y, int released_LKM_X, int released_LKM_Y)
    {
        if ( (((posX - x)*(posX - x)) + ((posY - y)*(posY - y))) <= 10000 )
        {
            for (int i = 0; i < 7; i++)
                hero[i].MRL();

            return true;
        }
        else if (((pressed_LKM_X <= x) && (x <= released_LKM_X) && (pressed_LKM_Y <= y) && (y <= released_LKM_Y))
                 || ((released_LKM_X <= x) && (x <= pressed_LKM_X) && (released_LKM_Y <= y) && (y <= pressed_LKM_Y))
                 || ((pressed_LKM_X <= x) && (pressed_LKM_Y >= y) && (released_LKM_X >= x) && (released_LKM_Y <= y))
                 || ((pressed_LKM_X >= x) && (pressed_LKM_Y <= y) && (released_LKM_X <= x) && (released_LKM_Y >= y))
                )
        {
            for (int i = 0; i < 7; i++)
                hero[i].MRL();

            return true;
        }

        return false;
    }

    void positionEnd(Player * hero, int posX, int posY)
    {
        hero[0].endX = posX - 30;
        hero[0].endY = posY - 50;

        hero[1].endX = posX + 20;
        hero[1].endY = posY - 50;

        hero[2].endX = posX - 50;
        hero[2].endY = posY;

        hero[3].endX = posX;
        hero[3].endY = posY;

        hero[4].endX = posX + 50;
        hero[4].endY = posY;

        hero[5].endX = posX - 30;
        hero[5].endY = posY + 50;

        hero[6].endX = posX + 20;
        hero[6].endY = posY + 50;
    }

    void mouseReleasedLeft(int posX, int posY, int pressed_LKM_X, int pressed_LKM_Y, int released_LKM_X, int released_LKM_Y)
    {
        if (sprite.getGlobalBounds().contains(posX, posY))
        {
            isMove = true;
            sprite.setColor(Color::Red);
        }
        else if (((pressed_LKM_X <= x) && (x <= released_LKM_X) && (pressed_LKM_Y <= y) && (y <= released_LKM_Y))
                 || ((released_LKM_X <= x) && (x <= pressed_LKM_X) && (released_LKM_Y <= y) && (y <= pressed_LKM_Y))
                 || ((pressed_LKM_X <= x) && (pressed_LKM_Y >= y) && (released_LKM_X >= x) && (released_LKM_Y <= y))
                 || ((pressed_LKM_X >= x) && (pressed_LKM_Y <= y) && (released_LKM_X <= x) && (released_LKM_Y >= y))
                )
        {
            isMove = true;
            sprite.setColor(Color::Red);
        }
    }
};

// обновить класс игрока:
// поправить спрайт
// исправить разность между скоростями по диагонали и по катетам (не критично!)

// скрол карты по диагонали (не критично!)
// увеличить карту
// при движении героя сделать остановку на правую кнопку мыши

// при остановки не убираеться круг
// уменьшить радиус круга

int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "Menu");//, Style::Fullscreen);
    window.setFramerateLimit(50);
    //menu(window);

    View view(FloatRect(0, 0, 1366, 768));
    //view.zoom(3.4f);

    Images map("map.png");

    int countH = 7;
    int centerH = countH / 2;

    Player * hero = new Player[7]{  {"hero_40x40.png", 270, 250, 40, 40}, {"hero_40x40.png", 320, 250, 40, 40},

                    {"hero_40x40.png", 250, 300, 40, 40}, {"hero_40x40.png", 300, 300, 40, 40}, {"hero_40x40.png", 350, 300, 40, 40},

                                    {"hero_40x40.png", 270, 350, 40, 40}, {"hero_40x40.png", 320, 350, 40, 40}
                                };

    ////rectangle////
    RectangleShape rectangle(Vector2f(0, 0));
    rectangle.setSize(Vector2f(0, 0));
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(Color(250, 150, 100));

    Clock clock;

    bool pressed_rectangle = false;

    int pressed_LKM_X;
    int pressed_LKM_Y;

    int released_LKM_X;
    int released_LKM_Y;

    ////shape////
    CircleShape shape(99);
    shape.setFillColor(Color::Transparent);

    shape.setOrigin(99/2, 99/2);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(Color(250, 150, 100));

    bool pressed_shape = false;


    while (window.isOpen() && !Keyboard::isKeyPressed(Keyboard::Escape))
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f pos = window.mapPixelToCoords(pixelPos);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    for (int i = 0; i < countH; i++) // stop motion
                        hero[i].mouseLeft();

                    pressed_shape = false;

                    pressed_rectangle = true;
                    pressed_LKM_X = pos.x;
                    pressed_LKM_Y = pos.y;
                }

                if (event.key.code == Mouse::Right)
                {
                    hero[0].positionEnd(hero, pos.x, pos.y);

                    for (int i = 0; i < countH; i++)
                        hero[i].mouseRight(pos.x, pos.y);
                }
            }

            if (event.type == Event::MouseButtonReleased)
            {
                if (event.key.code == Mouse::Left)
                {
                    released_LKM_X = pos.x;
                    released_LKM_Y = pos.y;

                    pressed_rectangle = false;
                    rectangle.setSize(Vector2f(0, 0));
                    window.display();

                    if(hero[centerH].checkSelect(hero, pos.x, pos.y, pressed_LKM_X, pressed_LKM_Y, released_LKM_X, released_LKM_Y) == true)
                       pressed_shape = true;
                }
            }
        }

        for (int i = 0; i < countH; i++)
            hero[i].movement(time);


        if (pressed_rectangle == true)
        {
            rectangle.setPosition(pressed_LKM_X, pressed_LKM_Y);
            rectangle.setSize(Vector2f(pos.x - pressed_LKM_X, pos.y - pressed_LKM_Y));
        }

        if (pos.x > -1500 && pos.x < 2866 && pos.y > -850 && pos.y < 1618)
        {
            if (pixelPos.x >= 1365) {
                view.move(0.3*time, 0);
            }
            if (pixelPos.y >= 767) {
                view.move(0, 0.3*time);
            }
            if (pixelPos.x <= 0) {
                view.move(-0.3*time, 0);
            }
            if (pixelPos.y <= 0) {
                view.move(0, -0.3*time);
            }
        }

        window.clear();

        for (int i = 0; i < HEIGHT_MAP; i++)
        {
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == ' ') map.sprite.setTextureRect(IntRect(0, 0, 32, 32));
                if (TileMap[i][j] == 's') map.sprite.setTextureRect(IntRect(32, 0, 32, 32));
                if (TileMap[i][j] == '0') map.sprite.setTextureRect(IntRect(64, 0, 32, 32));

                map.sprite.setPosition(j * 32, i * 32);
                window.draw(map.sprite);
            }
        }

        //window.setView(view);
        //window.draw(lineG, 38, Lines);
        //window.draw(lineV, 70, Lines);
        for (int i = 0; i < countH; i++)
            window.draw(hero[i].sprite);

        if (pressed_shape == true)
        {
            shape.setPosition(hero[centerH].x - 50, hero[centerH].y - 50);
            window.draw(shape);
        }

        window.draw(rectangle);
        window.display();
    }

    delete [] hero;
    window.close();
    return 0;
}*/


/*///////КЛАСС ИГРОКА///////
class Player
{
public:
    Image image;
    Texture texture;
    Sprite sprite;

    int x, y, w, h;

    int begX, begY;
    int endX, endY;
    int dx, dy;
    float angle;

    bool isMove, isSelect;
    float CurrentFrame;

    //float speed;
    //int dir;

    Player(String file, int positionX, int positionY, int width, int height)
    {
        x = positionX;
        y = positionY;
        w = width;
        h = height;
        image.loadFromFile(file);
        image.createMaskFromColor(Color::White);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setPosition(positionX, positionY);
        sprite.setTextureRect(IntRect(0, 0, w, h));
        sprite.setOrigin(w/2, h/2);

        CurrentFrame = 0;
        isMove = false;
        isSelect = false;

        begX = x;
        begY = y;

    }

    void update(float time,  int numImage, int posX, int posY)
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
        if (isSelect)
        {
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
                isSelect = false;
            }
        }
        else
        {
            stop();
        }
    }


    void mouseLeft()
    {
        sprite.setColor(Color::White);
        isSelect = false;
        isMove = false;
    }

    void mouseRight(int posX, int posY)
    {
        if (isMove == true)
        {
            begX = x;
            begY = y;

            endX = posX;
            endY = posY;

            dx = endX - begX;
            dy = endY - begY;

            //angle = (180 / M_PI) * atan2(float(dy), float(dx));

            sprite.setColor(Color::White);
            isMove = false;
            isSelect = true;
        }
    }

    void mouseReleasedLeft(int posX, int posY, int pressed_LKM_X, int pressed_LKM_Y, int released_LKM_X, int released_LKM_Y)
    {
        if (sprite.getGlobalBounds().contains(posX, posY))
        {
            isMove = true;
            sprite.setColor(Color::Red);
        }
        else if (((pressed_LKM_X <= x) && (x <= released_LKM_X) && (pressed_LKM_Y <= y) && (y <= released_LKM_Y))
                 || ((released_LKM_X <= x) && (x <= pressed_LKM_X) && (released_LKM_Y <= y) && (y <= pressed_LKM_Y))
                 || ((pressed_LKM_X <= x) && (pressed_LKM_Y >= y) && (released_LKM_X >= x) && (released_LKM_Y <= y))
                 || ((pressed_LKM_X >= x) && (pressed_LKM_Y <= y) && (released_LKM_X <= x) && (released_LKM_Y >= y))
                )
        {
            isMove = true;
            sprite.setColor(Color::Red);
        }
    }
};


int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "Menu", Style::Fullscreen);
    window.setFramerateLimit(50);
    //menu(window);

    View view(FloatRect(0, 0, 1366, 768));
    //view.zoom(3.4f);

    Images map("map.png");
    Player hero("hero_40x40.png", 323, 324, 40, 40);

    ////rectangle////
    RectangleShape rectangle(Vector2f(0, 0));
    rectangle.setSize(Vector2f(0, 0));
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(Color(250, 150, 100));

    Clock clock;

    bool pressed_rectangle = false;

    int pressed_LKM_X;
    int pressed_LKM_Y;

    int released_LKM_X;
    int released_LKM_Y;

    while (window.isOpen() && !Keyboard::isKeyPressed(Keyboard::Escape))
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f pos = window.mapPixelToCoords(pixelPos);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    hero.mouseLeft();

                    pressed_rectangle = true;
                    pressed_LKM_X = pos.x;
                    pressed_LKM_Y = pos.y;
                }

                if (event.key.code == Mouse::Right)
                {
                    hero.mouseRight(pos.x, pos.y);
                }
            }

            if (event.type == Event::MouseButtonReleased)
            {
                if (event.key.code == Mouse::Left)
                {
                    released_LKM_X = pos.x;
                    released_LKM_Y = pos.y;

                    pressed_rectangle = false;
                    rectangle.setSize(Vector2f(0, 0));
                    window.display();

                    hero.mouseReleasedLeft(pos.x, pos.y, pressed_LKM_X, pressed_LKM_Y, released_LKM_X, released_LKM_Y);
                }
            }
        }

        hero.movement(time);

        if (pressed_rectangle == true)
        {
            rectangle.setPosition(pressed_LKM_X, pressed_LKM_Y);
            rectangle.setSize(Vector2f(pos.x - pressed_LKM_X, pos.y - pressed_LKM_Y));
        }



        if (pos.x > -1500 && pos.x < 2866 && pos.y > -850 && pos.y < 1618)
        {
            if (pixelPos.x >= 1365) {
                view.move(0.3*time, 0);
            }
            if (pixelPos.y >= 767) {
                view.move(0, 0.3*time);
            }
            if (pixelPos.x <= 0) {
                view.move(-0.3*time, 0);
            }
            if (pixelPos.y <= 0) {
                view.move(0, -0.3*time);
            }
        }

        window.clear();

        for (int i = 0; i < HEIGHT_MAP; i++)
        {
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == ' ') map.sprite.setTextureRect(IntRect(0, 0, 32, 32));
                if (TileMap[i][j] == 's') map.sprite.setTextureRect(IntRect(32, 0, 32, 32));
                if (TileMap[i][j] == '0') map.sprite.setTextureRect(IntRect(64, 0, 32, 32));

                map.sprite.setPosition(j * 32, i * 32);
                window.draw(map.sprite);
            }
        }


        window.setView(view);
        //window.draw(lineG, 38, Lines);
        //window.draw(lineV, 70, Lines);
        window.draw(hero.sprite);
        window.draw(rectangle);
        window.display();
    }

    window.close();
    return 0;
}*/


/*void movement(float time)
    {
        sprite.setTextureRect(IntRect(200, 0, w, h));

        switch (dir)
        {
        case 0:
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 10) CurrentFrame -= 10;
            sprite.setTextureRect(IntRect(w * int(CurrentFrame), 120, w, h));

            x += (-1)*time;
            y += (-1)*time;

            break;
        case 1:
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 10) CurrentFrame -= 10;
            sprite.setTextureRect(IntRect(w * int(CurrentFrame), 160, w, h));

            x += 0;
            y += (-1)*time;

            break;
        case 2:
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 10) CurrentFrame -= 10;
            sprite.setTextureRect(IntRect(w * int(CurrentFrame), 240, w, h));

            x += (1)*time;
            y += (-1)*time;

            break;
        case 3:
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 10) CurrentFrame -= 10;
            sprite.setTextureRect(IntRect(w * int(CurrentFrame), 80, w, h));

            x += (-1)*time;
            y += 0;

            break;
        case 4:
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 10) CurrentFrame -= 10;
            sprite.setTextureRect(IntRect(w * int(CurrentFrame), 0, w, h));

            x += 0;
            y += (1)*time;

            break;
        case 5:
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 10) CurrentFrame -= 10;
            sprite.setTextureRect(IntRect(w * int(CurrentFrame), 200, w, h));

            x += (1)*time;
            y += 0;

            break;
        case 6:
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 10) CurrentFrame -= 10;
            sprite.setTextureRect(IntRect(w * int(CurrentFrame), 40, w, h));

            x += (-1)*time;
            y += (1)*time;

            break;
        case 7:
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 10) CurrentFrame -= 10;
            sprite.setTextureRect(IntRect(w * int(CurrentFrame), 160, w, h));

            x += (1)*time;
            y += (1)*time;

            break;

         sprite.setPosition(x,y);
        }

        if (Keyboard::isKeyPressed(Keyboard::Q))
        {
            dir = 0;
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 10) CurrentFrame -= 10;
            sprite.setTextureRect(IntRect(w * int(CurrentFrame), 120, w, h));
        }
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            dir = 1;
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 10) CurrentFrame -= 10;
            sprite.setTextureRect(IntRect(w * int(CurrentFrame), 160, w, h));
        }
        if (Keyboard::isKeyPressed(Keyboard::E))
        {
            dir = 2;
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 10) CurrentFrame -= 10;
            sprite.setTextureRect(IntRect(w * int(CurrentFrame), 280, w, h));
        }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            dir = 3;
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 10) CurrentFrame -= 10;
            sprite.setTextureRect(IntRect(w * int(CurrentFrame), 80, w, h));
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            dir = 4;
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 10) CurrentFrame -= 10;
            sprite.setTextureRect(IntRect(w * int(CurrentFrame), 0, w, h));
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            dir = 5;
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 10) CurrentFrame -= 10;
            sprite.setTextureRect(IntRect(w * int(CurrentFrame), 240, w, h));
        }
        if (Keyboard::isKeyPressed(Keyboard::Z))
        {
            dir = 6;
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 10) CurrentFrame -= 10;
            sprite.setTextureRect(IntRect(w * int(CurrentFrame), 40, w, h));
        }
        if (Keyboard::isKeyPressed(Keyboard::X))
        {
            dir = 7;
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 10) CurrentFrame -= 10;
            sprite.setTextureRect(IntRect(w * int(CurrentFrame), 200, w, h));
        }

    }


    void update(float time)
    {
        switch (dir)
        {
        case 0:
            dx = -speed;
            dy = -speed;
            break;
        case 1:
            dx = 0;
            dy = -speed;
            break;
        case 2:
            dx = speed;
            dy = -speed;
            break;
        case 3:
            dx = -speed;
            dy = 0;
            break;
        case 4:
            dx = 0;
            dy = speed;
            break;
        case 5:
            dx = speed;
            dy = 0;
            break;
        case 6:
            dx = -speed;
            dy = speed;
            break;
        case 7:
            dx = speed;
            dy = speed;
            break;
        }

        x += dx*time;        //наше ускорение на время получаем смещение координат и как следствие движение
        y += dy*time;        //аналогично по игреку

        dir = -1;
        speed = 0;
        sprite.setPosition(x,y);
    }

*/

/*int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "Menu");//, Style::Fullscreen);
    window.setFramerateLimit(50);
    //menu(window);

    View view(FloatRect(200, 200, 300, 200));
    view.zoom(1.0f);

    Player hero("hero_40x40.png", 323, 324, 40, 40);

    ////rectangle////
    RectangleShape rectangle(Vector2f(0, 0));
    rectangle.setSize(Vector2f(0, 0));
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(Color(250, 150, 100));

    bool pressed_rectangle = false;

    int dX, sx;
    int dY, sy;
    int err, e2;

    float x = 0;   // координата х при нажатии на лкм
    float y = 0;   // координата у при нажатии на лкм

    float dx = x;   // координата dx при отпускании лкм (вибран ли обьект нажатием на лкм или выдилением области)
    float dy = y;   // координата dx при нажатии лкм (вибран ли обьект нажатием на лкм или выдилением области)

    int tempX = 250;      //временная коорд Х.Снимаем ее после нажатия прав клав мыши
    int tempY = 250;      //коорд Y
    float distance = 0;   //это расстояние от объекта до тыка курсора

    Clock clock;
    float CurrentFrame1 = 0;
    float CurrentFrame2 = 0;
    float CurrentFrame3 = 0;


    Vertex lineG[] =
    {
        Vertex(Vector2f(0, 24)),
        Vertex(Vector2f(1366, 24)),

        Vertex(Vector2f(0, 64)),
        Vertex(Vector2f(1366, 64)),

        Vertex(Vector2f(0, 104)),
        Vertex(Vector2f(1366, 104)),

        Vertex(Vector2f(0, 144)),
        Vertex(Vector2f(1366, 144)),

        Vertex(Vector2f(0, 184)),
        Vertex(Vector2f(1366, 184)),

        Vertex(Vector2f(0, 224)),
        Vertex(Vector2f(1366, 224)),

        Vertex(Vector2f(0, 264)),
        Vertex(Vector2f(1366, 264)),

        Vertex(Vector2f(0, 304)),
        Vertex(Vector2f(1366, 304)),

        Vertex(Vector2f(0, 344)),
        Vertex(Vector2f(1366, 344)),

        Vertex(Vector2f(0, 384)),
        Vertex(Vector2f(1366, 384)),

        Vertex(Vector2f(0, 424)),
        Vertex(Vector2f(1366, 424)),

        Vertex(Vector2f(0, 464)),
        Vertex(Vector2f(1366, 464)),

        Vertex(Vector2f(0, 504)),
        Vertex(Vector2f(1366, 504)),

        Vertex(Vector2f(0, 544)),
        Vertex(Vector2f(1366, 544)),

        Vertex(Vector2f(0, 584)),
        Vertex(Vector2f(1366, 584)),

        Vertex(Vector2f(0, 624)),
        Vertex(Vector2f(1366, 624)),

        Vertex(Vector2f(0, 664)),
        Vertex(Vector2f(1366, 664)),

        Vertex(Vector2f(0, 704)),
        Vertex(Vector2f(1366, 704)),

        Vertex(Vector2f(0, 744)),
        Vertex(Vector2f(1366, 744))
    };

    Vertex lineV[] =
    {
        Vertex(Vector2f(23, 0)),
        Vertex(Vector2f(23, 768)),

        Vertex(Vector2f(63, 0)),
        Vertex(Vector2f(63, 768)),

        Vertex(Vector2f(103, 0)),
        Vertex(Vector2f(103, 768)),

        Vertex(Vector2f(143, 0)),
        Vertex(Vector2f(143, 768)),

        Vertex(Vector2f(183, 0)),
        Vertex(Vector2f(183, 768)),

        Vertex(Vector2f(223, 0)),
        Vertex(Vector2f(223, 768)),

        Vertex(Vector2f(263, 0)),
        Vertex(Vector2f(263, 768)),

        Vertex(Vector2f(303, 0)),
        Vertex(Vector2f(303, 768)),

        Vertex(Vector2f(343, 0)),
        Vertex(Vector2f(343, 768)),

        Vertex(Vector2f(383, 0)),
        Vertex(Vector2f(383, 768)),

        Vertex(Vector2f(423, 0)),
        Vertex(Vector2f(423, 768)),

        Vertex(Vector2f(463, 0)),
        Vertex(Vector2f(463, 768)),

        Vertex(Vector2f(503, 0)),
        Vertex(Vector2f(503, 768)),

        Vertex(Vector2f(543, 0)),
        Vertex(Vector2f(543, 768)),

        Vertex(Vector2f(583, 0)),
        Vertex(Vector2f(583, 768)),

        Vertex(Vector2f(623, 0)),
        Vertex(Vector2f(623, 768)),

        Vertex(Vector2f(663, 0)),
        Vertex(Vector2f(663, 768)),

        Vertex(Vector2f(703, 0)),
        Vertex(Vector2f(703, 768)),

        Vertex(Vector2f(743, 0)),
        Vertex(Vector2f(743, 768)),

        Vertex(Vector2f(783, 0)),
        Vertex(Vector2f(783, 768)),

        Vertex(Vector2f(823, 0)),
        Vertex(Vector2f(823, 768)),

        Vertex(Vector2f(863, 0)),
        Vertex(Vector2f(863, 768)),

        Vertex(Vector2f(903, 0)),
        Vertex(Vector2f(903, 768)),

        Vertex(Vector2f(943, 0)),
        Vertex(Vector2f(943, 768)),

        Vertex(Vector2f(983, 0)),
        Vertex(Vector2f(983, 768)),

        Vertex(Vector2f(1023, 0)),
        Vertex(Vector2f(1023, 768)),

        Vertex(Vector2f(1063, 0)),
        Vertex(Vector2f(1063, 768)),

        Vertex(Vector2f(1103, 0)),
        Vertex(Vector2f(1103, 768)),

        Vertex(Vector2f(1143, 0)),
        Vertex(Vector2f(1143, 768)),

        Vertex(Vector2f(1183, 0)),
        Vertex(Vector2f(1183, 768)),

        Vertex(Vector2f(1223, 0)),
        Vertex(Vector2f(1223, 768)),

        Vertex(Vector2f(1263, 0)),
        Vertex(Vector2f(1263, 768)),

        Vertex(Vector2f(1303, 0)),
        Vertex(Vector2f(1303, 768)),

        Vertex(Vector2f(1343, 0)),
        Vertex(Vector2f(1343, 768))
    };


    while (window.isOpen() && !Keyboard::isKeyPressed(Keyboard::Escape))
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f pos = window.mapPixelToCoords(pixelPos);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    if (pos.x >= 0 && pos.y >= 0 && pos.x <= 1366 && pos.y <= 768)
                    {
                        hero.sprite.setColor(Color::White);
                        pressed_rectangle = true;
                        hero.isSelect = false;
                        hero.isMove = false;
                        x = pos.x;
                        y = pos.y;
                    }
                }

                if (event.key.code == Mouse::Right)
                {
                    if (hero.isMove == true)
                    {
                        tempX = pos.x;
                        tempY = pos.y;

                        dX = abs(tempX - hero.x), sx = hero.x < tempX ? 1 : -1;
                        dY = abs(tempY - hero.y), sy = hero.y < tempY ? 1 : -1;
                        err = (dx > dy ? dx : -dy) / 2;

                        hero.sprite.setColor(Color::White);
                        hero.isMove = false;
                        hero.isSelect = true;
                    }
                }
            }

            if (event.type == Event::MouseButtonReleased)
            {
                if (event.key.code == Mouse::Left)
                {
                    dx = pos.x;
                    dy = pos.y;

                    pressed_rectangle = false;
                    rectangle.setSize(Vector2f(0, 0));
                    window.display();

                    if (hero.sprite.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        hero.isMove = true;
                        hero.sprite.setColor(Color::Red);
                    }
                    else if (((x <= hero.x) && (hero.x <= dx) && (y <= hero.y) && (hero.y <= dy))
                             || ((dx <= hero.x) && (hero.x <= x) && (dy <= hero.y) && (hero.y <= y))
                             || ((x <= hero.x) && (y >= hero.y) && (dx >= hero.x) && (dy <= hero.y))
                             || ((x >= hero.x) && (y <= hero.y) && (dx <= hero.x) && (dy >= hero.y))
                            )
                    {
                        hero.isMove = true;
                        hero.sprite.setColor(Color::Red);
                    }
                }
            }
        }

        if (hero.isSelect)
        {
            //float a_1 = hero.x;
            //float b_1 = hero.y;

            //int limU_1 = ((floor(hero.x / 40)) * 40) + 24;
            //int limL_1 = ((floor(hero.x / 40)) * 40) + 23;

            if (hero.x != tempX && hero.y != tempY)
            {
                e2 = err;
                if (e2 > -dX) { err -= dY; hero.x += sx; }
                if (e2 < dY) { err += dX; hero.y += sy; }

                //float a_2 = hero.x;
                //float b_2 = hero.y;

                //int limU_2 = ((floor(hero.x / 40)) * 40) + 24;
                //int limL_2 = ((floor(hero.x / 40)) * 40) + 23;

                hero.sprite.setPosition(hero.x, hero.x);

                /*if (limU_1 == limU_2 && a_2 > a_1)
                hero.dir = 5;

                }
                /*else if (limU_1 == limU_2 && a_2 < a_1)
                {
                    hero.dir = 3;
                }
                else if (limL_1 == limL_2 && b_2 > b_1)
                {
                    hero.dir = 4;
                }
                else if (limL_1 == limL_2 && b_2 < b_1)
                {
                    hero.dir = 1;
                }
                else if (limL_1 < limL_2 && limU_1 > limU_2)
                {
                    hero.dir = 2;
                }
                else if (limL_1 > limL_2 && limU_1 > limU_2)
                {
                    hero.dir = 0;
                }
                else if (limL_1 > limL_2 && limU_1 < limU_2)
                {
                    hero.dir = 6;
                }
                else if (limL_1 < limL_2 && limU_1 < limU_2)
                {
                    hero.dir = 7;
                }*//*

            }
        }



        //hero.movement(time);
        //hero.update(time);

        if (pressed_rectangle == true)
        {
            rectangle.setPosition(x, y);
            rectangle.setSize(Vector2f(pos.x-x, pos.y-y));
        }

        window.clear();
        //window.setView(view);
        window.draw(lineG, 38, Lines);
        window.draw(lineV, 70, Lines);
        window.draw(hero.sprite);
        window.draw(rectangle);
        window.display();
    }

    window.close();
    return 0;
}*/

// движение по указателю
/*int main()
{   int check=0;
    RenderWindow window(VideoMode::getDesktopMode(), "Menu");//, Style::Fullscreen);
    window.setFramerateLimit(50);
    //menu(window);

    View view(FloatRect(200, 200, 300, 200));
    view.zoom(1.0f);

    Player hero("hero_40x40.png", 323, 324, 40, 40);

    ////rectangle////
    RectangleShape rectangle(Vector2f(0, 0));
    rectangle.setSize(Vector2f(0, 0));
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(Color(250, 150, 100));

    bool pressed_rectangle = false;

    int dX, sx;
    int dY, sy;
    int err, e2;

    float x = 0;   // координата х при нажатии на лкм
    float y = 0;   // координата у при нажатии на лкм

    float dx = x;   // координата dx при отпускании лкм (вибран ли обьект нажатием на лкм или выдилением области)
    float dy = y;   // координата dx при нажатии лкм (вибран ли обьект нажатием на лкм или выдилением области)

    int tempX = 250;      //временная коорд Х.Снимаем ее после нажатия прав клав мыши
    int tempY = 250;      //коорд Y
    float distance = 0;   //это расстояние от объекта до тыка курсора

    Clock clock;

    int a_1 = 323;
    int b_1 = 324;
    int a_2 = 323;
    int b_2 = 324;

    Vertex lineG[] =
    {
        Vertex(Vector2f(0, 24)),
        Vertex(Vector2f(1366, 24)),

        Vertex(Vector2f(0, 64)),
        Vertex(Vector2f(1366, 64)),

        Vertex(Vector2f(0, 104)),
        Vertex(Vector2f(1366, 104)),

        Vertex(Vector2f(0, 144)),
        Vertex(Vector2f(1366, 144)),

        Vertex(Vector2f(0, 184)),
        Vertex(Vector2f(1366, 184)),

        Vertex(Vector2f(0, 224)),
        Vertex(Vector2f(1366, 224)),

        Vertex(Vector2f(0, 264)),
        Vertex(Vector2f(1366, 264)),

        Vertex(Vector2f(0, 304)),
        Vertex(Vector2f(1366, 304)),

        Vertex(Vector2f(0, 344)),
        Vertex(Vector2f(1366, 344)),

        Vertex(Vector2f(0, 384)),
        Vertex(Vector2f(1366, 384)),

        Vertex(Vector2f(0, 424)),
        Vertex(Vector2f(1366, 424)),

        Vertex(Vector2f(0, 464)),
        Vertex(Vector2f(1366, 464)),

        Vertex(Vector2f(0, 504)),
        Vertex(Vector2f(1366, 504)),

        Vertex(Vector2f(0, 544)),
        Vertex(Vector2f(1366, 544)),

        Vertex(Vector2f(0, 584)),
        Vertex(Vector2f(1366, 584)),

        Vertex(Vector2f(0, 624)),
        Vertex(Vector2f(1366, 624)),

        Vertex(Vector2f(0, 664)),
        Vertex(Vector2f(1366, 664)),

        Vertex(Vector2f(0, 704)),
        Vertex(Vector2f(1366, 704)),

        Vertex(Vector2f(0, 744)),
        Vertex(Vector2f(1366, 744))
    };

    Vertex lineV[] =
    {
        Vertex(Vector2f(23, 0)),
        Vertex(Vector2f(23, 768)),

        Vertex(Vector2f(63, 0)),
        Vertex(Vector2f(63, 768)),

        Vertex(Vector2f(103, 0)),
        Vertex(Vector2f(103, 768)),

        Vertex(Vector2f(143, 0)),
        Vertex(Vector2f(143, 768)),

        Vertex(Vector2f(183, 0)),
        Vertex(Vector2f(183, 768)),

        Vertex(Vector2f(223, 0)),
        Vertex(Vector2f(223, 768)),

        Vertex(Vector2f(263, 0)),
        Vertex(Vector2f(263, 768)),

        Vertex(Vector2f(303, 0)),
        Vertex(Vector2f(303, 768)),

        Vertex(Vector2f(343, 0)),
        Vertex(Vector2f(343, 768)),

        Vertex(Vector2f(383, 0)),
        Vertex(Vector2f(383, 768)),

        Vertex(Vector2f(423, 0)),
        Vertex(Vector2f(423, 768)),

        Vertex(Vector2f(463, 0)),
        Vertex(Vector2f(463, 768)),

        Vertex(Vector2f(503, 0)),
        Vertex(Vector2f(503, 768)),

        Vertex(Vector2f(543, 0)),
        Vertex(Vector2f(543, 768)),

        Vertex(Vector2f(583, 0)),
        Vertex(Vector2f(583, 768)),

        Vertex(Vector2f(623, 0)),
        Vertex(Vector2f(623, 768)),

        Vertex(Vector2f(663, 0)),
        Vertex(Vector2f(663, 768)),

        Vertex(Vector2f(703, 0)),
        Vertex(Vector2f(703, 768)),

        Vertex(Vector2f(743, 0)),
        Vertex(Vector2f(743, 768)),

        Vertex(Vector2f(783, 0)),
        Vertex(Vector2f(783, 768)),

        Vertex(Vector2f(823, 0)),
        Vertex(Vector2f(823, 768)),

        Vertex(Vector2f(863, 0)),
        Vertex(Vector2f(863, 768)),

        Vertex(Vector2f(903, 0)),
        Vertex(Vector2f(903, 768)),

        Vertex(Vector2f(943, 0)),
        Vertex(Vector2f(943, 768)),

        Vertex(Vector2f(983, 0)),
        Vertex(Vector2f(983, 768)),

        Vertex(Vector2f(1023, 0)),
        Vertex(Vector2f(1023, 768)),

        Vertex(Vector2f(1063, 0)),
        Vertex(Vector2f(1063, 768)),

        Vertex(Vector2f(1103, 0)),
        Vertex(Vector2f(1103, 768)),

        Vertex(Vector2f(1143, 0)),
        Vertex(Vector2f(1143, 768)),

        Vertex(Vector2f(1183, 0)),
        Vertex(Vector2f(1183, 768)),

        Vertex(Vector2f(1223, 0)),
        Vertex(Vector2f(1223, 768)),

        Vertex(Vector2f(1263, 0)),
        Vertex(Vector2f(1263, 768)),

        Vertex(Vector2f(1303, 0)),
        Vertex(Vector2f(1303, 768)),

        Vertex(Vector2f(1343, 0)),
        Vertex(Vector2f(1343, 768))
    };


    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        //time = time/800;
        time = 40;

        Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f pos = window.mapPixelToCoords(pixelPos);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    if (pos.x >= 0 && pos.y >= 0 && pos.x <= 1366 && pos.y <= 768)
                    {
                        hero.sprite.setColor(Color::White);
                        pressed_rectangle = true;
                        hero.isSelect = false;
                        hero.isMove = false;
                        x = pos.x;
                        y = pos.y;
                    }
                }

                if (event.key.code == Mouse::Right)
                {
                    if (hero.isMove == true)
                    {
                        tempX = pos.x;
                        tempY = pos.y;

                        dX = abs(tempX - hero.x), sx = hero.x < tempX ? 1 : -1;
                        dY = abs(tempY - hero.y), sy = hero.y < tempY ? 1 : -1;
                        err = (dX > dY ? dX : -dY) / 2;

                        hero.sprite.setColor(Color::White);
                        hero.isMove = false;
                        hero.isSelect = true;
                    }
                }
            }

            if (event.type == Event::MouseButtonReleased)
            {
                if (event.key.code == Mouse::Left)
                {
                    dx = pos.x;
                    dy = pos.y;

                    pressed_rectangle = false;
                    rectangle.setSize(Vector2f(0, 0));
                    window.display();

                    if (hero.sprite.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        hero.isMove = true;
                        hero.sprite.setColor(Color::Red);
                    }
                    else if (((x <= hero.x) && (hero.x <= dx) && (y <= hero.y) && (hero.y <= dy))
                             || ((dx <= hero.x) && (hero.x <= x) && (dy <= hero.y) && (hero.y <= y))
                             || ((x <= hero.x) && (y >= hero.y) && (dx >= hero.x) && (dy <= hero.y))
                             || ((x >= hero.x) && (y <= hero.y) && (dx <= hero.x) && (dy >= hero.y))
                            )
                    {
                        hero.isMove = true;
                        hero.sprite.setColor(Color::Red);
                    }
                }
            }
        }

        if (hero.isSelect)
        {
            a_1 = a_2;
            b_1 = b_2;

            int limU_1 = ((floor(b_1 / 40)) * 40) + 24;
            int limL_1 = ((floor(a_1 / 40)) * 40) + 23;

            if(check==0)
            {
                cout<<" "<<tempX<<" "<<tempY<<" ";
                check=1;
            }

            if ( (a_2 != tempX  && b_2 != tempY) || (a_2 != tempX  && b_2 == tempY) || (a_2 == tempX  && b_2 != tempY) )
            {
                e2 = err;
                if (e2 > -dX) { err -= dY; a_2 += sx; }
                if (e2 < dY) { err += dX; b_2 += sy; }
                cout<<"||"<<a_2<<" "<<b_2<<"||";
                int limU_2 = ((floor(b_2 / 40)) * 40) + 24;
                int limL_2 = ((floor(a_2 / 40)) * 40) + 23;

                if (limU_1 == limU_2 && limL_2 > limL_1)
                {
                   // for(int i = 0; i < 40; i+=40)
                    {
                        //window.clear();
                        hero.sprite.setPosition(hero.x += time, hero.y);
                        window.draw(hero.sprite);
                        //window.display();
                    }
                }
                else if (limU_1 == limU_2 && limL_2 < limL_1)
                {
                   // for(int i = 0; i < 40; i+=40)
                    {
                        hero.sprite.setPosition(hero.x -= time, hero.y);
                        window.draw(hero.sprite);
                    }
                }
                else if (limL_1 == limL_2 && limU_2 > limU_1)
                {
                   // for(int i = 0; i < 40; i+=40)
                    {
                        hero.sprite.setPosition(hero.x, hero.y += time);
                        window.draw(hero.sprite);
                    }
                }
                else if (limL_1 == limL_2 && limU_2 < limU_1)
                {
                  //  for(int i = 0; i < 40; i+=40)
                    {
                        hero.sprite.setPosition(hero.x, hero.y -= time);
                        window.draw(hero.sprite);
                    }
                }
                else if (limL_1 < limL_2 && limU_1 > limU_2)
                {
                    puts("OK");
                   // for(int i = 0; i < 40; i+=40)
                    {
                        hero.sprite.setPosition(hero.x += time, hero.y -= time);
                        window.draw(hero.sprite);
                    }
                }
                else if (limL_1 > limL_2 && limU_1 > limU_2)
                {
                  //  for(int i = 0; i < 40; i+=40)
                    {
                        hero.sprite.setPosition(hero.x -= time, hero.y -= time);
                        window.draw(hero.sprite);
                    }
                }
                else if (limL_1 > limL_2 && limU_1 < limU_2)
                {
                  //  for(int i = 0; i < 40; i+=40)
                    {
                        hero.sprite.setPosition(hero.x -= time, hero.y += time);
                        window.draw(hero.sprite);
                    }
                }
                else if (limL_1 < limL_2 && limU_1 < limU_2)
                {
                   // for(int i = 0; i < 40; i+=40)
                    {
                        hero.sprite.setPosition(hero.x += time, hero.y += time);
                        window.draw(hero.sprite);
                    }
                }

            }
            else
            {
                hero.isSelect = false;
            }
        }

        if (pressed_rectangle == true)
        {
            rectangle.setPosition(x, y);
            rectangle.setSize(Vector2f(pos.x-x, pos.y-y));
        }

        window.clear();
        //window.setView(view);
        window.draw(lineG, 38, Lines);
        window.draw(lineV, 70, Lines);
        window.draw(hero.sprite);
        window.draw(rectangle);
        window.display();
    }

    window.close();
    return 0;
}*/

/*class Player
{
public:
    float x, y, w, h, dx, dy, speed;    //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
    int dir;                            //направление (direction) движения игрока
    bool isMove, isSelect;
    float CurrentFrame;
    Image image;
    Texture texture;
    Sprite sprite;

    Player(String file, float positionX, float positionY, float width, float height)
    {
        x = positionX;
        y = positionY;
        w = width;
        h = height;
        image.loadFromFile(file);
        image.createMaskFromColor(Color::White);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setPosition(positionX, positionY);
        sprite.setTextureRect(IntRect(0, 0, w, h));
        //sprite.setOrigin(x/2, y/2);
        dir = 0;
        speed = 0;
        dx = 0;
        dy = 0;
        CurrentFrame = 0;
        isMove = false;
        isSelect = false;
    }

    void movement(float time)
    {
        sprite.setTextureRect(IntRect(32, 0, 31, 29));
hero.sprite.setRotation(angle);
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            dir = 0; //3
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 6) CurrentFrame -= 6;
            sprite.setTextureRect(IntRect(0, 32 * int(CurrentFrame), 31, 32));
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            dir = 1;  //2
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 6) CurrentFrame -= 6;
            sprite.setTextureRect(IntRect(32, 29 * int(CurrentFrame), 31, 29));
        }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            dir = 2; //1
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 6) CurrentFrame -= 6;
            sprite.setTextureRect(IntRect(93, 32 * int(CurrentFrame), 28, 32));
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            dir = 3; //0
            speed = MAX_SPEED;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 6) CurrentFrame -= 6;
            sprite.setTextureRect(IntRect(64, 32 * int(CurrentFrame), 28, 32));
        }
        if (Keyboard::isKeyPressed(Keyboard::Q))
        {
            dir = 4;
            speed = MAX_SPEED - 0.01;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 6) CurrentFrame -= 6;
            sprite.setTextureRect(IntRect(191, 36 * int(CurrentFrame), 37, 36));
        }
        if (Keyboard::isKeyPressed(Keyboard::E))
        {
            dir = 5;
            speed = MAX_SPEED - 0.01;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 6) CurrentFrame -= 6;
            sprite.setTextureRect(IntRect(122, 36 * int(CurrentFrame), 36, 36));
        }
        if (Keyboard::isKeyPressed(Keyboard::Z))
        {
            dir = 6;
            speed = MAX_SPEED - 0.01;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 6) CurrentFrame -= 6;
            sprite.setTextureRect(IntRect(228, 32 * int(CurrentFrame), 33, 32));
        }
        if (Keyboard::isKeyPressed(Keyboard::X))
        {
            dir = 7;
            speed = MAX_SPEED - 0.01;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 6) CurrentFrame -= 6;
            sprite.setTextureRect(IntRect(159, 32 * int(CurrentFrame), 32, 32));
        }
    }

    void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML, вследствие чего работает бесконечно, давая персонажу движение.
    {
        switch (dir)        //реализуем поведение в зависимости от направления (каждая цифра соответствует направлению)
        {
        case 0:
            dx = 0;
            dy = -speed;
            break;           //по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
        case 1:
            dx = 0;
            dy = speed;
            break;          //по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
        case 2:
            dx = -speed;
            dy = 0;
            break;          //по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
        case 3:
            dx = speed;
            dy = 0;
            break;          //по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
        case 4:
            dx = -speed;
            dy = -speed;
            break;
        case 5:
            dx = speed;
            dy = -speed;
            break;
        case 6:
            dx = -speed;
            dy = speed;
            break;
        case 7:
            dx = speed;
            dy = speed;
            break;
        }

        x += dx*time;        //наше ускорение на время получаем смещение координат и как следствие движение
        y += dy*time;        //аналогично по игреку

        speed = 0;                  //зануляем скорость, чтобы персонаж остановился.
        sprite.setPosition(x,y);    //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
    }
};


int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "Menu");//, Style::Fullscreen);
    window.setFramerateLimit(50);
    //menu(window);

    Player hero("hero.png", 250, 250, 31, 32);

    ////rectangle////
    RectangleShape rectangle(sf::Vector2f(0, 0));
    rectangle.setSize(sf::Vector2f(0, 0));
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(sf::Color(250, 150, 100));

    bool pressed_rectangle = false;

    float x = 0;   // координата х при нажатии на лкм
    float y = 0;   // координата у при нажатии на лкм

    float dx = x;   // координата dx при отпускании лкм (вибран ли обьект нажатием на лкм или выдилением области)
    float dy = y;   // координата dx при нажатии лкм (вибран ли обьект нажатием на лкм или выдилением области)

    int tempX = 250;      //временная коорд Х.Снимаем ее после нажатия прав клав мыши
    int tempY = 250;      //коорд Y
    float distance = 0;   //это расстояние от объекта до тыка курсора

    Clock clock;
    float CurrentFrame = 0;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f pos = window.mapPixelToCoords(pixelPos);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    if (pos.x >= 0 && pos.y >= 0 && pos.x <= 1366 && pos.y <= 768)
                    {
                        hero.sprite.setColor(Color::White);
                        pressed_rectangle = true;
                        hero.isSelect = false;
                        hero.isMove = false;
                        x = pos.x;
                        y = pos.y;
                    }
                }

                if (event.key.code == Mouse::Right)
                {
                    if (hero.isMove == true)
                    {
                        tempX = pos.x;
                        tempY = pos.y;

                        hero.sprite.setColor(Color::White);
                        hero.isMove = false;
                        hero.isSelect = true;
                    }
                }
            }

            if (event.type == Event::MouseButtonReleased)
            {
                if (event.key.code == Mouse::Left)
                {
                    dx = pos.x;
                    dy = pos.y;

                    pressed_rectangle = false;
                    rectangle.setSize(Vector2f(0, 0));
                    window.display();

                    if (hero.sprite.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        hero.isMove = true;
                        hero.sprite.setColor(Color::Red);
                    }
                    else if (((x <= hero.x + 15) && (hero.x + 15 <= dx) && (y <= hero.y + 16) && (hero.y + 16 <= dy))
                             || ((dx <= hero.x + 15) && (hero.x + 15 <= x) && (dy <= hero.y + 16) && (hero.y + 16 <= y))
                             || ((x <= hero.x + 15) && (y >= hero.y + 16) && (dx >= hero.x + 15) && (dy <= hero.y + 16))
                             || ((x >= hero.x + 15) && (y <= hero.y + 16) && (dx <= hero.x + 15) && (dy >= hero.y + 16))
                            )
                    {
                        hero.isMove = true;
                        hero.sprite.setColor(Color::Red);
                    }
                }
            }
        }


        if (hero.isSelect)
        {
            int dx = abs(tempX - hero.x), sx = hero.x < tempX ? 1 : -1;
            int dy = abs(tempY - hero.y), sy = hero.y < tempY ? 1 : -1;
            int err = (dx > dy ? dx : -dy) / 2, e2;

            if (hero.x != tempX && hero.y != tempY)
            {
                e2 = err;
                if (e2 > -dx) { err -= dy; hero.x += sx; }
                if (e2 < dy) { err += dx; hero.y += sy; }
                hero.sprite.setPosition(hero.x, hero.y);
            }
        }

        if (pressed_rectangle == true)
        {
            rectangle.setPosition(x, y);
            rectangle.setSize(Vector2f(pos.x-x, pos.y-y));
        }

        window.clear();
        window.draw(hero.sprite);
        window.draw(rectangle);
        window.display();
    }

    window.close();
    return 0;
}
*/
