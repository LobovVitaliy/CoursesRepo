#include <SFML/Graphics.hpp>
#include <Windows.h>

using namespace sf;

void settings(RenderWindow & window);
void menu(RenderWindow & window);

void menu(RenderWindow & window)
{
    Texture Background_T, NewGame_T, LoadGame_T, SettingsGame_T, QuitGame_T;
    Background_T.loadFromFile("Background.png");
    NewGame_T.loadFromFile("NewGame.png");
    LoadGame_T.loadFromFile("LoadGame.png");
    SettingsGame_T.loadFromFile("SettingsGame.png");
    QuitGame_T.loadFromFile("QuitGame.png");

    Sprite Background_S, NewGame_S, LoadGame_S, SettingsGame_S, QuitGame_S;
    Background_S.setTexture(Background_T);
    NewGame_S.setTexture(NewGame_T);
    LoadGame_S.setTexture(LoadGame_T);
    SettingsGame_S.setTexture(SettingsGame_T);
    QuitGame_S.setTexture(QuitGame_T);


    bool isMenu = true;
    int menuNum = 0;

    while (isMenu)
    {
        // проверить все события окна, которые были вызваны с последней итерации цикла
        Event event;
        while (window.pollEvent(event))
        {
            // "запрос закрытия" событие: мы закрываем окно
            if (event.type == Event::Closed)
                window.close();
        }

        NewGame_S.setColor(Color::White);
        LoadGame_S.setColor(Color::White);
        SettingsGame_S.setColor(Color::White);
        QuitGame_S.setColor(Color::White);

        menuNum = 0;
        window.clear(Color(129, 181, 221)); // Зачем ?

        if (IntRect(222, 252, 245, 78).contains(Mouse::getPosition(window)))
        {
            NewGame_S.setColor(Color(230, 100, 200));
            menuNum = 1;
        }
        else if (IntRect(222, 340, 245, 78).contains(Mouse::getPosition(window)))
        {
            LoadGame_S.setColor(Color(230, 100, 200));
            menuNum = 2;
        }
        else if (IntRect(222, 428, 245, 78).contains(Mouse::getPosition(window)))
        {
            SettingsGame_S.setColor(Color(230, 100, 200));
            menuNum = 3;
        }
        else if (IntRect(222, 516, 245, 78).contains(Mouse::getPosition(window)))
        {
            QuitGame_S.setColor(Color(230, 100, 200));
            menuNum = 4;
        }


        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1)
            {
                isMenu = false; //если нажали первую кнопку, то выходим из меню
            }
            else if (menuNum == 2)
            {
                //window.draw(about);
                window.display();
                while (!Keyboard::isKeyPressed(Keyboard::Escape));
            }
            else if (menuNum == 3)
            {
                settings(window);
            }
            else if (menuNum == 4)
            {
                window.close();
                isMenu = false;
            }
        }

        window.draw(Background_S);
        window.draw(NewGame_S);
        window.draw(LoadGame_S);
        window.draw(SettingsGame_S);
        window.draw(QuitGame_S);

        window.display();
    }
}

void settings(RenderWindow & window)
{
    Texture Settings_T;
    Settings_T.loadFromFile("Settings.png");

    Sprite Settings_S;
    Settings_S.setTexture(Settings_T);

    Texture SettingsBackground_T;
    SettingsBackground_T.loadFromFile("SettingsBackground.png");

    Sprite SettingsBackground_S;
    SettingsBackground_S.setTexture(SettingsBackground_T);


    while (!Keyboard::isKeyPressed(Keyboard::Escape))
    {
        // проверить все события окна, которые были вызваны с последней итерации цикла
        Event event;
        while (window.pollEvent(event))
        {
            // "запрос закрытия" событие: мы закрываем окно
            if (event.type == Event::Closed)
                window.close();
        }

        window.draw(SettingsBackground_S);
        window.draw(Settings_S);
        window.display();
    }
}

int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "Menu", Style::Fullscreen);
    menu(window);
    return 0;
}

