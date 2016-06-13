#include "Menu.hpp"

Options:: Options()
{
    checkOffHelp = 1;
    checkOffMusic = 0;
    numMusic = 0;
    fileNameMusic = "";
}

void build(RenderWindow & window)
{
    Database * db = new Database("Data.db");

    char sqlQuery[] = "SELECT * FROM Map;";
    for(int j = 0; j < db->count("SELECT COUNT(*) FROM Map;"); j++)
    {
        db->getDataByIndex(sqlQuery, j);

        int Radius = db->R;
        if(strcmp(db->Name, "Ambar") == 0) Radius = db->Radius;

        // Круг вокруг строения
        CircleShape shape(Radius);
        shape.setFillColor(Color::Transparent);

        shape.setOrigin(Radius, Radius);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(Color(194, 228, 228, 80));
        shape.setPosition(db->x, db->y);
        window.draw(shape);
    }
}

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

void game(RenderWindow & window, Options & options)
{
    fileHeroCleaning("hero.txt");
    fileHeroCleaning("enemy.txt");

    Images miniMap("Images/miniMap6.png", 0, 510); // or 5

    // Загружаю картинки только один раз, в дальнейшем использую только их спрайты
    Images imageCave("Building/cave.png", 0, 0, 90, 60);
    Images imageBuilding("Building/building.png", 0, 0, 95, 88);
    Images imageHouse("Building/house.png", 0, 0, 140, 115);
    Images imageFountain("Building/fountain.png", 0, 0, 60, 80);
    Images imageTower("Building/tower.png", 0, 0, 75, 105);
    Images imageAmbar("Building/ambar.png", 0, 0, 165, 134);

    Images BigScaleUpdate("Images/scaleBuilding.png", 0, 0, 112, 140);

    BuildingPlayer cave(imageCave.sprite, BigScaleUpdate.sprite, "Cave", 0, 0, 90, 60, 5, 25);
    BuildingPlayer building(imageBuilding.sprite, BigScaleUpdate.sprite, "Building", 0, 0, 95, 88, 5, 50);
    BuildingPlayer house(imageHouse.sprite, BigScaleUpdate.sprite, "House", 0, 0, 140, 115, 5);
    BuildingPlayer fountain(imageFountain.sprite, BigScaleUpdate.sprite, "Fountain", 0, 0, 60, 80, 5);
    BuildingPlayer tower(imageTower.sprite, BigScaleUpdate.sprite, "Tower", 0, 0, 75, 105, 5);
    BuildingPlayer ambar(imageAmbar.sprite, BigScaleUpdate.sprite, "Ambar", 0, 0, 165, 134, 5);

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

    Text textWin("", font, 100);

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

    while (!Keyboard::isKeyPressed(Keyboard::Escape))
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

                (*it)->checkLife(0); // без входных параметров
                if((*it)->getLife() == 0) heros.remove(*it);
            }

            // Битва между героями
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

        // Координаты относительно пространства
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
                    isBuild = false; // режим постройки отключен
                    isHelpText = true; // разрешить выводить текст при наведении на обьекты

                    // Останавливаю прорисовку при движении обьекта ( Сброс обьекта который нажат )
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

                    // Вставка обьекта (если можно вставить в даную область карты)
                    if (isSelect == 1)
                    {
                        if (cave.build(41, pos.x, pos.y))
                        {
                            isSelect = 0;
                            coins -= 50;
                            sprintf(money, "%i", coins);
                            isBuild = false; // режим постройки отключен
                        }
                    }
                    else if (isSelect == 2)
                    {
                        if (building.build(50, pos.x, pos.y))
                        {
                            isSelect = 0;
                            coins -= 250;
                            sprintf(money, "%i", coins);
                            isBuild = false; // режим постройки отключен
                        }
                    }
                    else if (isSelect == 3)
                    {
                        if (house.build(69, pos.x, pos.y))
                        {
                            isSelect = 0;
                            coins -= 250;
                            sprintf(money, "%i", coins);
                            isBuild = false; // режим постройки отключен
                        }
                    }
                    else if (isSelect == 4)
                    {
                        if (fountain.build(42, pos.x, pos.y))
                        {
                            isSelect = 0;
                            coins -= 1000;
                            sprintf(money, "%i", coins);
                            isBuild = false; // режим постройки отключен
                        }
                    }
                    else if (isSelect == 5)
                    {
                        if (tower.build(53, pos.x, pos.y))
                        {
                            isSelect = 0;
                            coins -= 1000;
                            sprintf(money, "%i", coins);
                            isBuild = false; // режим постройки отключен
                        }
                    }
                    else if (isSelect == 6)
                    {
                        if (ambar.build(84, pos.x, pos.y)) // R = 84  увеличил что б рядом размещать войска
                        {
                            isSelect = 0;
                            coins -= 450;
                            sprintf(money, "%i", coins);
                            isBuild = false; // режим постройки отключен
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

                    // Перемещение камеры вида по мини-карте (можно перенести "pos.y < (posWindow.y + 717)" в начальное условие вместе с кругом)
                    //if(pow(pressed_LKM_X - released_LKM_X, 2) + pow(pressed_LKM_Y - released_LKM_Y, 2) < 100) // или эта проверка
                    if(pressed_LKM_X == released_LKM_X && pressed_LKM_Y == released_LKM_Y) // или эта проверка
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

                    // Выбор обьекта который нажат
                    if (pressed_selection == true)
                    {
                        if ( (((pos.x - 603)*(pos.x - 603)) + ((pos.y - 266)*(pos.y - 266))) <= 1225 )
                        {
                            if(coins >= 50)
                            {
                                cave.createAndMove(window, pos.x, pos.y);
                                isSelect = 1;
                                isBuild = true; // режим постройки включен
                            }
                        }
                        else if ( (((pos.x - 747)*(pos.x - 747)) + ((pos.y - 266)*(pos.y - 266))) <= 1225 )
                        {
                            if(coins >= 250)
                            {
                                building.createAndMove(window, pos.x, pos.y);
                                isSelect = 2;
                                isBuild = true; // режим постройки включен
                            }
                        }
                        else if ( (((pos.x - 819)*(pos.x - 819)) + ((pos.y - 384)*(pos.y - 384))) <= 1225 )
                        {
                            if(coins >= 250)
                            {
                                house.createAndMove(window, pos.x, pos.y);
                                isSelect = 3;
                                isBuild = true; // режим постройки включен
                            }
                        }
                        else if ( (((pos.x - 747)*(pos.x - 747)) + ((pos.y - 504)*(pos.y - 504))) <= 1225 )
                        {
                            if(coins >= 1000)
                            {
                                fountain.createAndMove(window, pos.x, pos.y);
                                isSelect = 4;
                                isBuild = true; // режим постройки включен
                            }
                        }
                        else if ( (((pos.x - 603)*(pos.x - 603)) + ((pos.y - 504)*(pos.y - 504))) <= 1225 )
                        {
                            if(coins >= 1000)
                            {
                                tower.createAndMove(window, pos.x, pos.y);
                                isSelect = 5;
                                isBuild = true; // режим постройки включен
                            }
                        }
                        else if ( (((pos.x - 531)*(pos.x - 531)) + ((pos.y - 384)*(pos.y - 384))) <= 1225 )
                        {
                            if(coins >= 450)
                            {
                                ambar.createAndMove(window, pos.x, pos.y);
                                isSelect = 6;
                                isBuild = true; // режим постройки включен
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

                            // Сброс обьекта "выбор" который нажат
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

                            // Сброс обьекта "выбор" который нажат
                            indexBuilding = -1;
                        }
                        else if (indexHouse != -1)
                        {
                            int deltaArmor = house.getDeltaArmor(indexHouse);

                            if ( (((pos.x - (house.getX(indexHouse) - 48))*(pos.x  - (house.getX(indexHouse) - 48))) + ((pos.y - (house.getY(indexHouse) - 50))*(pos.y - (house.getY(indexHouse) - 50)))) <= 950 )
                            {//мб сместить на пиксель вверх
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
                            {//мб сместить на пиксель вверх
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

                            // Сброс обьекта "выбор" который нажат
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

                            // Сброс обьекта "выбор" который нажат
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

                            // Сброс обьекта "выбор" который нажат
                            indexTower = -1;
                        }
                        else if (indexAmbar != -1)
                        {
                            if ( (((pos.x - (ambar.getX(indexAmbar) - 48))*(pos.x  - (ambar.getX(indexAmbar) - 48))) + ((pos.y - (ambar.getY(indexAmbar) - 50))*(pos.y - (ambar.getY(indexAmbar) - 50)))) <= 950 )
                            {//мб сместить на пиксель вверх
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
                            {//мб сместить на пиксель вверх
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

                            // Сброс обьекта "выбор" который нажат
                            indexAmbar = -1;
                        }
                        else
                        {
                            // Выбор обьекта "выбор" который нажат
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

        // Разметка границ карты
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

        // Прорисовка обьектов
        cave.moveAndDraw(window, 41, pos.x, pos.y);
        building.moveAndDraw(window, 50, pos.x, pos.y);
        house.moveAndDraw(window, 69, pos.x, pos.y);
        fountain.moveAndDraw(window, 42, pos.x, pos.y);
        tower.moveAndDraw(window, 53, pos.x, pos.y);
        ambar.moveAndDraw(window, 220, pos.x, pos.y); // R = 84  увеличил что б рядом размещать войска

        cave.drawScale(window);
        building.drawScale(window);
        house.drawScale(window);
        fountain.drawScale(window);
        tower.drawScale(window);
        ambar.drawScale(window);

        // Вражеские строения
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

        // Прорисовка обьекта "выбор" при нажатии на обьект
        if((pressed_selection_building  == true) && (pow(pressed_LKM_X - released_LKM_X, 2) + pow(pressed_LKM_Y - released_LKM_Y, 2) < 100))
        {   // делано для того что бы при выдилением квадратом не выбирался обьект // возможно эту проверку: pressed_LKM_X == released_LKM_X && pressed_LKM_Y == released_LKM_Y
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

                // Отрисовка радиуса лечения
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

                // Отрисовка радиуса обстрела
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

        // Прорисовка обьекта "выбор" при нажатии на обьект "Замок"
        if((pressed_selection == true) && (pow(pressed_LKM_X - released_LKM_X, 2) + pow(pressed_LKM_Y - released_LKM_Y, 2) < 100)) // pressed_LKM_X == released_LKM_X && pressed_LKM_Y == released_LKM_Y
        {   // делано для того что бы при выдилением квадратом не выбирался Замок // возможно эту проверку: pressed_LKM_X == released_LKM_X && pressed_LKM_Y == released_LKM_Y
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


        // Координаты относительно экрана
        pixelPosWindow = window.getPosition();
        posWindow = window.mapPixelToCoords(pixelPosWindow);

        miniMap.sprite.setPosition(posWindow.x, posWindow.y + 510);
        window.draw(miniMap.sprite);

        text.setColor(Color::White);
        text.setString(money);
        text.setPosition(posWindow.x + 53, posWindow.y + 721);
        window.draw(text);

        if(isGame == false)
        {
            textWin.setCharacterSize(100);
            textWin.setColor(Color::Red);
            textWin.setString("Вы победили!");
            textWin.setPosition(posWindow.x + 400, posWindow.y + 250);
            window.draw(textWin);
            if(event.type == Event::MouseButtonPressed) break;
        }

        // Вывод подсказок
        if(options.checkOffHelp == 1)
        {
            help = "";

            if (indexCave != -1)
            {
                if ( (((pos.x - cave.getX(indexCave))*(pos.x  - cave.getX(indexCave))) + ((pos.y - (cave.getY(indexCave) - 50))*(pos.y - (cave.getY(indexCave) - 50)))) <= 950 )
                {
                    help = "Улучшить характеристики (-1000$)";
                }
                else if ( (((pos.x - cave.getX(indexCave))*(pos.x  - cave.getX(indexCave))) + ((pos.y - (cave.getY(indexCave) + 50))*(pos.y - (cave.getY(indexCave) + 50)))) <= 950 )
                {
                    help = "Удалить";
                }
            }
            else if (indexBuilding != -1)
            {
                if ( (((pos.x - building.getX(indexBuilding))*(pos.x  - building.getX(indexBuilding))) + ((pos.y - (building.getY(indexBuilding) - 50))*(pos.y - (building.getY(indexBuilding) - 50)))) <= 950 )
                {
                    help = "Улучшить характеристики (-2000$)";
                }
                else if ( (((pos.x - building.getX(indexBuilding))*(pos.x  - building.getX(indexBuilding))) + ((pos.y - (building.getY(indexBuilding) + 50))*(pos.y - (building.getY(indexBuilding) + 50)))) <= 950 )
                {
                    help = "Удалить";
                }
            }
            else if (indexHouse != -1)
            {
                if ( (((pos.x - (house.getX(indexHouse) - 48))*(pos.x  - (house.getX(indexHouse) - 48))) + ((pos.y - (house.getY(indexHouse) - 50))*(pos.y - (house.getY(indexHouse) - 50)))) <= 950 )
                {
                    help = "Улучшить способности персонажа (-1500$)";
                }
                else if ( (((pos.x - (house.getX(indexHouse) + 48))*(pos.x  - (house.getX(indexHouse) + 48))) + ((pos.y - (house.getY(indexHouse) - 50))*(pos.y - (house.getY(indexHouse) - 50)))) <= 950 )
                {
                    help = "Улучшить характеристики (-2500$)";
                }
                else if ( (((pos.x - house.getX(indexHouse))*(pos.x  - house.getX(indexHouse))) + ((pos.y - (house.getY(indexHouse) + 50))*(pos.y - (house.getY(indexHouse) + 50)))) <= 950 )
                {
                    help = "Удалить";
                }
            }
            else if (indexFountain != -1)
            {
                if ( (((pos.x - fountain.getX(indexFountain))*(pos.x  - fountain.getX(indexFountain))) + ((pos.y - (fountain.getY(indexFountain) - 50))*(pos.y - (fountain.getY(indexFountain) - 50)))) <= 950 )
                {
                    help = "Улучшить характеристики (-2000$)";
                }
                else if ( (((pos.x - fountain.getX(indexFountain))*(pos.x  - fountain.getX(indexFountain))) + ((pos.y - (fountain.getY(indexFountain) + 50))*(pos.y - (fountain.getY(indexFountain) + 50)))) <= 950 )
                {
                    help = "Удалить";
                }
            }
            else if (indexTower != -1)
            {
                if ( (((pos.x - tower.getX(indexTower))*(pos.x  - tower.getX(indexTower))) + ((pos.y - (tower.getY(indexTower) - 50))*(pos.y - (tower.getY(indexTower) - 50)))) <= 950 )
                {
                    help = "Улучшить характеристики (-2000$)";
                }
                else if ( (((pos.x - tower.getX(indexTower))*(pos.x  - tower.getX(indexTower))) + ((pos.y - (tower.getY(indexTower) + 50))*(pos.y - (tower.getY(indexTower) + 50)))) <= 950 )
                {
                    help = "Удалить";
                }
            }
            else if (indexAmbar != -1)
            {
                if ( (((pos.x - (ambar.getX(indexAmbar) - 48))*(pos.x  - (ambar.getX(indexAmbar) - 48))) + ((pos.y - (ambar.getY(indexAmbar) - 50))*(pos.y - (ambar.getY(indexAmbar) - 50)))) <= 950 )
                {
                    help = "Призвать героя (-2500$)";
                }
                else if ( (((pos.x - (ambar.getX(indexAmbar) + 48))*(pos.x  - (ambar.getX(indexAmbar) + 48))) + ((pos.y - (ambar.getY(indexAmbar) - 50))*(pos.y - (ambar.getY(indexAmbar) - 50)))) <= 950 )
                {
                    help = "Призвать армию (-1000$)";
                }
                else if ( (((pos.x - ambar.getX(indexAmbar))*(pos.x  - ambar.getX(indexAmbar))) + ((pos.y - (ambar.getY(indexAmbar) + 50))*(pos.y - (ambar.getY(indexAmbar) + 50)))) <= 950 )
                {
                    help = "Удалить";
                }
            }

            if (isBuild == true)
            {
                help = "Для размещения нажмите правую кнопку мыши";
            }
            else if (pressed_selection == true)
            {
                if ( (((pos.x - 603)*(pos.x - 603)) + ((pos.y - 266)*(pos.y - 266))) <= 1225 ) help = "Добывает ресурсы в размере 25 одиниц (-50$). Для выбора нажмите левую кнопку мыши";
                else if ( (((pos.x - 747)*(pos.x - 747)) + ((pos.y - 266)*(pos.y - 266))) <= 1225 ) help = "Добывает ресурсы в размере 50 одиниц (-250$). Для выбора нажмите левую кнопку мыши";
                else if ( (((pos.x - 819)*(pos.x - 819)) + ((pos.y - 384)*(pos.y - 384))) <= 1225 ) help = "Улучшает способности персонажа (-250$). Для выбора нажмите левую кнопку мыши";
                else if ( (((pos.x - 747)*(pos.x - 747)) + ((pos.y - 504)*(pos.y - 504))) <= 1225 ) help = "Повышает здоровье персонажа на определённом расстоянии (-1000$). Для выбора нажмите левую кнопку мыши";
                else if ( (((pos.x - 603)*(pos.x - 603)) + ((pos.y - 504)*(pos.y - 504))) <= 1225 ) help = "Наносит урон врагу на определённом расстоянии (-1000$). Для выбора нажмите левую кнопку мыши";
                else if ( (((pos.x - 531)*(pos.x - 531)) + ((pos.y - 384)*(pos.y - 384))) <= 1225 ) help = "Создает персонажей (-450$). Для выбора нажмите левую кнопку мыши";
            }
            else if (pressed_selection == false)
            {
                if ( (((pos.x - 683)*(pos.x - 683)) + ((pos.y - 410)*(pos.y - 410))) <= 11025 )
                {
                    help = "Для выбора нажмите левую кнопку мыши";
                }
                else if (isHelpText == true)
                {
                    if (cave.checkPosition(pos.x, pos.y) != -1) help = "Для выбора нажмите левую кнопку мыши";
                    else if (building.checkPosition(pos.x, pos.y) != -1) help = "Для выбора нажмите левую кнопку мыши";
                    else if (house.checkPosition(pos.x, pos.y) != -1) help = "Для выбора нажмите левую кнопку мыши";
                    else if (tower.checkPosition(pos.x, pos.y) != -1) help = "Для выбора нажмите левую кнопку мыши";
                    else if (fountain.checkPosition(pos.x, pos.y) != -1) help = "Для выбора нажмите левую кнопку мыши";
                    else if (ambar.checkPosition(pos.x, pos.y) != -1) help = "Для выбора нажмите левую кнопку мыши";
                }
            }

            helpText.setColor(Color::White);
            helpText.setString(help);
            helpText.setPosition(posWindow.x + 1300 - help.size() * 9, posWindow.y + 10); // зависит от длины текста

            rect.setPosition(posWindow.x + 1280 - help.size() * 9, posWindow.y);
            rect.setSize(Vector2f(1000, 55));

            if (help.size() != 0) window.draw(rect);
            window.draw(helpText);
        }

        // Разметки на мини-карте
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

    heros.clear();
    enemy.clear();

    char sqlQueryMap[] = "DELETE FROM Map WHERE Name <> ?;";
    db.clearData(sqlQueryMap); // очищаем все обьекты с базы данных, кроме главного Замка
    char sqlQueryPlayer[] = "DELETE FROM Player;";
    db.clearData(sqlQueryPlayer); // очищаем всех персонажей с базы данных
}
