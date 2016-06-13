/*void menu(RenderWindow & window);
void game(RenderWindow & window);
void settings(RenderWindow & window);

/////// Ћј—— »√–ќ ј///////
class Player
{
public:
    float x, y, w, h, dx, dy, speed;    //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
    int dir;                            //направление (direction) движени€ игрока
    bool isMove, isSelect;
    float CurrentFrame;
    //String File;
    Image image;
    Texture texture;
    Sprite sprite;

    Player(String file, float positionX, float positionY, float width, float height)
    {
        //File = file;
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
        //sprite.setOrigin(Vector2f(originX, originY));
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

    void update(float time) //функци€ "оживлени€" объекта класса. update - обновление. принимает в себ€ врем€ SFML, вследствие чего работает бесконечно, дава€ персонажу движение.
    {
        switch (dir)        //реализуем поведение в зависимости от направлени€ (кажда€ цифра соответствует направлению)
        {
        case 0:
            dx = 0;
            dy = -speed;
            break;           //по иксу задаем нулевое значение, по игреку отрицательное. получаетс€, что персонаж идет только вверх
        case 1:
            dx = 0;
            dy = speed;
            break;          //по иксу задаем нулевое значение, по игреку положительное. получаетс€, что персонаж идет только вниз
        case 2:
            dx = -speed;
            dy = 0;
            break;          //по иксу задаем отрицательную скорость, по игреку занул€ем. получаетс€, что персонаж идет только влево
        case 3:
            dx = speed;
            dy = 0;
            break;          //по иксу задаем положительную скорость, по игреку занул€ем. получаем, что персонаж идет только вправо
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

        x += dx*time;        //наше ускорение на врем€ получаем смещение координат и как следствие движение
        y += dy*time;        //аналогично по игреку

        speed = 0;                  //занул€ем скорость, чтобы персонаж остановилс€.
        sprite.setPosition(x,y);    //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт сто€л на месте.
    }
};

class Images
{
public:             // private
    int positionX;
    int positionY;
    //int originX;
    //int originY;    // public
    //String File;
    Image image;
    Texture texture;
    Sprite sprite;

    Images(String file, int positionX = 0, int positionY = 0/*, int originX = 0, int originY = 0)    // онструктор с параметрами(формальными) дл€ класса Player. ѕри создании объекта класса мы будем задавать им€ файла, координату ’ и ”, ширину и высоту
    {
        //File = file;
        image.loadFromFile(file);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setPosition(positionX, positionY);
        //sprite.setOrigin(Vector2f(originX, originY));
    }
};

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
        window.clear(Color(129, 181, 221)); // «ачем ?

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

void game(RenderWindow & window)
{
    Images map("map.png");

    while (!Keyboard::isKeyPressed(Keyboard::Escape))
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

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

        window.display();
    }
}*/
