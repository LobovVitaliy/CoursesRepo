#include <SFML/Graphics.hpp>
#include<Windows.h>

using namespace sf;

void menu(RenderWindow & window)
{
    Texture Background_T, NewGame_T, LoadGame_T, Settings_T, QuitGame_T;
    Background_T.loadFromFile("Background.png");
    NewGame_T.loadFromFile("NewGame.png");
    LoadGame_T.loadFromFile("LoadGame.png");
    Settings_T.loadFromFile("Settings.png");
    QuitGame_T.loadFromFile("QuitGame.png");

    Sprite Background_S, NewGame_S, LoadGame_S, Settings_S, QuitGame_S;
    Background_S.setTexture(Background_T);
    NewGame_S.setTexture(NewGame_T);
    LoadGame_S.setTexture(LoadGame_T);
    Settings_S.setTexture(Settings_T);
    QuitGame_S.setTexture(QuitGame_T);


    bool isMenu = true;
    int menuNum = 0;

    while (window.isOpen())
    {
        // проверить все событи€ окна, которые были вызваны с последней итерации цикла
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "запрос закрыти€" событие: мы закрываем окно
            if (event.type == sf::Event::Closed)
                window.close();
        }

        NewGame_S.setColor(Color::White);
        LoadGame_S.setColor(Color::White);
        Settings_S.setColor(Color::White);
        QuitGame_S.setColor(Color::White);

        menuNum = 0;
        window.clear(Color(129, 181, 221)); // «ачем ?

        if (IntRect(222, 252, 245, 78).contains(Mouse::getPosition(window)))
        {
            NewGame_S.setColor(Color(230, 100, 200));
            menuNum = 1;
        }
        if (IntRect(222, 340, 245, 78).contains(Mouse::getPosition(window)))
        {
            LoadGame_S.setColor(Color(230, 100, 200));
            menuNum = 2;
        }
        if (IntRect(222, 428, 245, 78).contains(Mouse::getPosition(window)))
        {
            Settings_S.setColor(Color(230, 100, 200));
            menuNum = 3;
        }
        if (IntRect(222, 516, 245, 78).contains(Mouse::getPosition(window)))
        {
            QuitGame_S.setColor(Color(230, 100, 200));
            menuNum = 4;
        }



        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1)
            {
                isMenu = false;//если нажали первую кнопку, то выходим из меню
            }
            if (menuNum == 2)
            {
                //window.draw(about);
                window.display();
                while (!Keyboard::isKeyPressed(Keyboard::Escape));
            }
            if (menuNum == 3)
            {

            }
            if (menuNum == 4)
            {
                window.close();
                isMenu = false;
            }

        }

        window.draw(Background_S);
        window.draw(NewGame_S);
        window.draw(LoadGame_S);
        window.draw(Settings_S);
        window.draw(QuitGame_S);

        window.display();
    }


    /*while (isMenu)
    {
        NewGame_S.setColor(Color::White);
        LoadGame_S.setColor(Color::White);
        Settings_S.setColor(Color::White);
        QuitGame_S.setColor(Color::White);

        menuNum = 0;
        window.clear(Color(129, 181, 221)); // «ачем

        if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window)))
        {
            NewGame_S.setColor(Color::Blue);
            menuNum = 1;
        }
        if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window)))
        {
            LoadGame_S.setColor(Color::Blue);
            menuNum = 2;
        }
        if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window)))
        {
            Settings_S.setColor(Color::Blue);
            menuNum = 3;
        }
        if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window)))
        {
            QuitGame_S.setColor(Color::Blue);
            menuNum = 4;
        }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1)
            {
                isMenu = false;//если нажали первую кнопку, то выходим из меню
            }
            if (menuNum == 2)
            {
                //window.draw(about);
                window.display();
                while (!Keyboard::isKeyPressed(Keyboard::Escape));
            }
            if (menuNum == 3)
            {

            }
            if (menuNum == 4)
            {
                window.close();
                isMenu = false;
            }

        }

        window.draw(Background_S);
        window.draw(NewGame_S);
        window.draw(LoadGame_S);
        window.draw(Settings_S);
        window.draw(QuitGame_S);

        window.display();
    }*/
}


int main()
{
    /*int scrX = GetSystemMetrics(SM_CXSCREEN);
    int scrY = GetSystemMetrics(SM_CYSCREEN);
     window(sf::VideoMode (scrX, scrY), "Menu");*/

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Menu",  sf::Style::Fullscreen);
    //RenderWindow window(VideoMode::getDesktopMode(), "Menu");
    //RenderWindow window(VideoMode(1200, 700), "Menu");

    menu(window);


    // пусть программа работает до тех пор, пока открыто окно
    sf::RectangleShape rectangle(sf::Vector2f(120, 50));
    // change the size to 100x100
    rectangle.setSize(sf::Vector2f(100, 100));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(rectangle);
        window.display();
    }

    return 0;
}
/*
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Kfni.ho.ua load image");

    sf::Texture t_hero;
    t_hero.loadFromFile("Background.png");

    sf::Sprite s_hero;
    s_hero.setTexture(t_hero);
    s_hero.setPosition(400,300);
    s_hero.setOrigin(56,56);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(s_hero);
        window.display();
    }

    return 0;
}*/

