#include <SFML/Graphics.hpp>
#include<Windows.h>

void menu(sf::RenderWindow & window)
{
    sf::Texture Background;
    Background.loadFromFile("Background.png");

    sf::Sprite s_hero;
    s_hero.setTexture(Background);

    bool isMenu = 1;
    int menuNum = 0;

    while (isMenu)
    {
        menuNum = 0;
        //window.clear(sf::Color(129, 181, 221));

        if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(window)))
        {
            menuNum = 1;
        }
        //if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) {  menuNum = 2; }
        //if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) {  menuNum = 3; }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню

        }

            while (window.isOpen())
    {
        // проверить все события окна, которые были вызваны с последней итерации цикла
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "запрос закрытия" событие: мы закрываем окно
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(s_hero);
        window.display();
    }

        window.display();
    }
}


int main()
{
    /*int scrX = GetSystemMetrics(SM_CXSCREEN);
    int scrY = GetSystemMetrics(SM_CYSCREEN);
     window(sf::VideoMode (scrX, scrY), "Menu");*/

    //sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Menu",  sf::Style::Fullscreen);
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Menu");

    menu(window);


// пусть программа работает до тех пор, пока открыто окно
    while (window.isOpen())
    {
        // проверить все события окна, которые были вызваны с последней итерации цикла
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "запрос закрытия" событие: мы закрываем окно
            if (event.type == sf::Event::Closed)
                window.close();
        }
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

