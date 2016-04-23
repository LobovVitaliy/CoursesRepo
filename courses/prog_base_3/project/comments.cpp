/*
int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "Menu");//, Style::Fullscreen);

    Vertex line[] =
    {
        Vertex(sf::Vector2f(5, 5)),
        Vertex(sf::Vector2f(6, 6))
    };

    /*RectangleShape rectangle(sf::Vector2f(0, 0));
    rectangle.setSize(sf::Vector2f(0, 0));
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(sf::Color(250, 150, 100));*/
/*
    double x = 0;
    double y = 0;

    double dx = 0;
    double dy = 0;

    while (!Keyboard::isKeyPressed(Keyboard::Escape))
    {
        Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f pos = window.mapPixelToCoords(pixelPos);

        dx = 0;
        dy = 0;

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
                    if(pos.x >= 0 && pos.y >= 0)
                    {
                        x = pos.x;
                        y = pos.y;
                        cout<<x<<"   "<<y<<endl;
                    }
                }
            }

            cout<<"position:  "<<pos.x<<"   "<<pos.y<<endl;
            if (event.type == Event::MouseButtonReleased)//если отпустили клавишу
                if (event.key.code == Mouse::Left) //а именно левую
                {
                    if(pos.x >= 0 && pos.y >= 0)
                    {
                        dx = pos.x;// - x;
                        dy = pos.y;// - y;
                        cout<<"        "<<dx<<"   "<<dy<<endl;
                        //rectangle.setPosition(x, y);
                        //rectangle.setSize(sf::Vector2f(dx, dy));

                        line[0] = Vertex(sf::Vector2f(x, y));
                        line[1] = Vertex(sf::Vector2f(dx, dy));

                        window.draw(line, 2, Lines);
                        window.display();

                    }
                }

        }

        //window.clear();

        window.display();

        //window.draw(rectangle);
        //Sleep(100); window.clear();
    }

    window.close();
    return EXIT_SUCCESS;
}*/


/*int main()
{
    //RenderWindow window(VideoMode::getDesktopMode(), "Menu");//, Style::Fullscreen);
    window.setFramerateLimit(50);
    //menu(window);

    // create a view with the rectangular area of the 2D world to show
    //View view(FloatRect(200, 200, 300, 200));
    //view.zoom(1.0f);

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

        //hero.isSelect = false;

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
                        //hero.x = pos.x - 15;
                        //hero.y = pos.y - 16;

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

                    //if (IntRect(hero.x, hero.y, 31, 32).contains(Mouse::getPosition(window)))      тоже самое // находится ли курсор в области спрайта
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
        	distance = sqrt((tempX - hero.x)*(tempX - hero.x) + (tempY - hero.y)*(tempY - hero.y));

            /*float angle = (180 / M_PI) * atan2((tempY - hero.y), (tempX - hero.x));
            printf("angle: %.5f\n", angle);

            if (angle == 0) hero.dir = 3;
            if (angle == 90) hero.dir = 1;
            if (angle == 180) hero.dir = 2;
            if (angle == -90) hero.dir = 0;

            if (0 < angle && angle < 90) hero.dir = 7;
            if (90 < angle && angle < 180) hero.dir = 6;
            if (-90 < angle && angle < 0) hero.dir = 5;
            if (-180 < angle && angle < -90) hero.dir = 4;*//*

        	if (distance > 2){
        		hero.x += 0.1*time*(tempX - hero.x) / distance;
        		hero.y += 0.1*time*(tempY - hero.y) / distance;
        	}

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

        	else
            {
                hero.isSelect = true;           хз надо ли это теперь (и так работает)
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

        window.draw(hero.sprite);
        window.draw(rectangle);
        window.display();
    }

    window.close();
    return 0;
}
*/



/*int main()
{
    /*RenderWindow window(VideoMode::getDesktopMode(), "Menu");//, Style::Fullscreen);
    window.setFramerateLimit(50);
    //menu(window);

    // create a view with the rectangular area of the 2D world to show
    //View view(FloatRect(200, 200, 300, 200));
    //view.zoom(1.0f);

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

        //hero.isSelect = false;

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
                        //hero.x = pos.x - 15;
                        //hero.y = pos.y - 16;

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

                    //if (IntRect(hero.x, hero.y, 31, 32).contains(Mouse::getPosition(window)))      тоже самое // находится ли курсор в области спрайта
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
        	distance = sqrt((tempX - hero.x)*(tempX - hero.x) + (tempY - hero.y)*(tempY - hero.y));

            *//*float angle = (180 / M_PI) * atan2((tempY - hero.y), (tempX - hero.x));
            printf("angle: %.5f\n", angle);

            if (angle == 0) hero.dir = 3;
            if (angle == 90) hero.dir = 1;
            if (angle == 180) hero.dir = 2;
            if (angle == -90) hero.dir = 0;

            if (0 < angle && angle < 90) hero.dir = 7;
            if (90 < angle && angle < 180) hero.dir = 6;
            if (-90 < angle && angle < 0) hero.dir = 5;
            if (-180 < angle && angle < -90) hero.dir = 4;*//*

        	if (distance > 2){
        		hero.x += 0.1*time*(tempX - hero.x) / distance;
        		hero.y += 0.1*time*(tempY - hero.y) / distance;
        	}
        	else
            {
                hero.isSelect = true;
            }
        }

        hero.movement(time);
        hero.update(time);

        if (pressed_rectangle == true)
        {
            rectangle.setPosition(x, y);
            rectangle.setSize(Vector2f(pos.x-x, pos.y-y));
        }

        window.clear();
        //window.setView(view);

        window.draw(hero.sprite);
        window.draw(rectangle);
        window.display();
    }

    window.close();
    return 0;
}*/


//////MOVE HERO DONE////////////
/*
    Image hero;
    hero.loadFromFile("monsterNew.png");
    hero.createMaskFromColor(Color::White);

    Texture herotexture;
    herotexture.loadFromImage(hero);

    Sprite herosprite;
    herosprite.setTexture(herotexture);
    herosprite.setTextureRect(IntRect(0, 0, 31, 32));
    herosprite.setPosition(250,250);

    ////rectangle////
    RectangleShape rectangle(sf::Vector2f(0, 0));
    rectangle.setSize(sf::Vector2f(0, 0));
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(sf::Color(250, 150, 100));

    bool move = false;
    bool move_draw = false;
    bool pressed_rectangle = false;

    float x = 0;   // координата х при нажатии на лкм
    float y = 0;   // координата у при нажатии на лкм

    float dx = x;   // координата dx при отпускании лкм (вибран ли обьект нажатием на лкм или выдилением области)
    float dy = y;   // координата dx при нажатии лкм (вибран ли обьект нажатием на лкм или выдилением области)

    while (window.isOpen())
    {
        Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f pos = window.mapPixelToCoords(pixelPos);
        Vector2f sprite_pos = herosprite.getPosition();

        move_draw = true;

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
                    if (move == false)
                    {
                        if (pos.x >= 0 && pos.y >= 0 && pos.x <= 1366 && pos.y <= 768)
                        {
                            pressed_rectangle = true;
                            x = pos.x;
                            y = pos.y;
                            //cout<<x<<"\t"<<y<<endl;
                        }
                    }
                }
            }

            if (event.type == Event::MouseButtonReleased)
            {
                if (event.key.code == Mouse::Left)
                {
                    if (move == true)
                    {
                        herosprite.setPosition(pos.x - 15, pos.y - 16);
                        herosprite.setColor(Color::White);
                        move = false;
                        move_draw = false;
                    }

                    if (move_draw == true)
                    {
                        dx = pos.x;
                        dy = pos.y;
                        //cout<<"\t"<<dx<<"\t"<<dy<<endl;

                        pressed_rectangle = false;
                        rectangle.setSize(Vector2f(0, 0));
                        window.display();

                        if (IntRect(sprite_pos.x, sprite_pos.y, 31, 32).contains(Mouse::getPosition(window)))
                        {
                            move = true;
                            herosprite.setColor(Color::Red);
                            //puts("OK");
                        }
                        else if (((x <= sprite_pos.x + 15) && (sprite_pos.x + 15 <= dx) && (y <= sprite_pos.y + 16) && (sprite_pos.y + 16 <= dy))
                                || ((dx <= sprite_pos.x + 15) && (sprite_pos.x + 15 <= x) && (dy <= sprite_pos.y + 16) && (sprite_pos.y + 16 <= y))
                                || ((x <= sprite_pos.x + 15) && (y >= sprite_pos.y + 16) && (dx >= sprite_pos.x + 15) && (dy <= sprite_pos.y + 16))
                                || ((x >= sprite_pos.x + 15) && (y <= sprite_pos.y + 16) && (dx <= sprite_pos.x + 15) && (dy >= sprite_pos.y + 16))
                           )
                        {
                            move = true;
                            herosprite.setColor(Color::Red);
                            //puts("OKKKKKKK");
                        }
                    }
                }
            }
        }

        if (pressed_rectangle == true)
        {
            rectangle.setPosition(x, y);
            rectangle.setSize(Vector2f(pos.x-x, pos.y-y));
        }

        window.clear();
        window.draw(herosprite);
        window.draw(rectangle);
        window.display();
    }*/



///////////////////////////
/*Image hero;
hero.loadFromFile("monsterNew.png");
hero.createMaskFromColor(Color::White);

Texture herotexture;
herotexture.loadFromImage(hero);

Sprite herosprite;
herosprite.setTexture(herotexture);
herosprite.setTextureRect(IntRect(0, 0, 31, 32));
herosprite.setPosition(250,250);

////rectangle////
RectangleShape rectangle(sf::Vector2f(0, 0));
rectangle.setSize(sf::Vector2f(0, 0));
rectangle.setFillColor(Color::Transparent);
rectangle.setOutlineThickness(2);
rectangle.setOutlineColor(sf::Color(250, 150, 100));

bool move = false;
bool pressed_rectangle = false;

float x = 0;   // координата х при нажатии на лкм
float y = 0;   // координата у при нажатии на лкм

float dx = x;   // координата dx при отпускании лкм (вибран ли обьект нажатием на лкм или выдилением области)
float dy = y;   // координата dx при нажатии лкм (вибран ли обьект нажатием на лкм или выдилением области)

while (window.isOpen())
{
    Vector2i pixelPos = Mouse::getPosition(window);
    Vector2f pos = window.mapPixelToCoords(pixelPos);
    Vector2f sprite_pos = herosprite.getPosition();

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
                    pressed_rectangle = true;
                    x = pos.x;
                    y = pos.y;
                    cout<<x<<"\t"<<y<<endl;
                }

            }
        }

        if (event.type == Event::MouseButtonReleased)
        {
            if (event.key.code == Mouse::Left)
            {
                dx = pos.x;
                dy = pos.y;
                cout<<"\t"<<dx<<"\t"<<dy<<endl;

                pressed_rectangle = false;
                rectangle.setSize(Vector2f(0, 0));
                window.display();

                if (IntRect(sprite_pos.x, sprite_pos.y, 31, 32).contains(Mouse::getPosition(window)))
                {
                    move = true;
                    herosprite.setColor(Color::Red);
                    puts("OKKKKKKK");
                }

                if (((x <= sprite_pos.x + 15) && (sprite_pos.x + 15 <= dx) && (y <= sprite_pos.y + 16) && (sprite_pos.y + 16 <= dy))
                        || ((dx <= sprite_pos.x + 15) && (sprite_pos.x + 15 <= x) && (dy <= sprite_pos.y + 16) && (sprite_pos.y + 16 <= y))
                        || ((x <= sprite_pos.x + 15) && (y >= sprite_pos.y + 16) && (dx >= sprite_pos.x + 15) && (dy <= sprite_pos.y + 16))
                        || ((x >= sprite_pos.x + 15) && (y <= sprite_pos.y + 16) && (dx <= sprite_pos.x + 15) && (dy >= sprite_pos.y + 16))
                   )
                {
                    move = true;
                    herosprite.setColor(Color::Red);
                    puts("OKKKKKKK");
                }
            }
        }
    }

    if (pressed_rectangle == true)
    {
        rectangle.setPosition(x, y);
        rectangle.setSize(Vector2f(pos.x-x, pos.y-y));
    }

    window.clear();
    window.draw(herosprite);
    window.draw(rectangle);
    window.display();
}*/

///////////////////////////
/*Image hero;
hero.loadFromFile("monsterNew.png");
hero.createMaskFromColor(Color::White);

Texture herotexture;
herotexture.loadFromImage(hero);

Sprite herosprite;
herosprite.setTexture(herotexture);
herosprite.setTextureRect(IntRect(0, 0, 31, 32));
herosprite.setPosition(250,250);

////rectangle////
RectangleShape rectangle(sf::Vector2f(0, 0));
rectangle.setSize(sf::Vector2f(0, 0));
rectangle.setFillColor(Color::Transparent);
rectangle.setOutlineThickness(2);
rectangle.setOutlineColor(sf::Color(250, 150, 100));

bool move = false;
bool pressed_rectangle = false;

float x = 0;   // координата х при нажатии на лкм
float y = 0;   // координата у при нажатии на лкм

float dx = x;   // координата dx при отпускании лкм (вибран ли обьект нажатием на лкм или выдилением области)
float dy = y;   // координата dx при нажатии лкм (вибран ли обьект нажатием на лкм или выдилением области)

while (window.isOpen())
{
    Vector2i pixelPos = Mouse::getPosition(window);
    Vector2f pos = window.mapPixelToCoords(pixelPos);
    Vector2f sprite_pos = herosprite.getPosition();

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
                //if (pressed_rectagle == false)
                //{
                    //cout<<sprite_pos.x<<"\t"<<sprite_pos.y<<endl;
                    //if (((x <= sprite_pos.x + 15) && (sprite_pos.x + 15 <= dx) && (y <= sprite_pos.y + 16) && (sprite_pos.y + 16 <= dy) || IntRect(sprite_pos.x, sprite_pos.y, 31, 32).contains(Mouse::getPosition(window))))

                    //if (pressed_mouse == true)
                    /*if (IntRect(sprite_pos.x, sprite_pos.y, 31, 32).contains(Mouse::getPosition(window)))
                    {
                        herosprite.setPosition(pos.x - 15, pos.y - 16);
                        herosprite.setColor(Color::White);

                                   // pressed_mouse = false;
                    }
}*/


/*if (pressed == true && pressed_rectagle == false)
{
    herosprite.setPosition(pos.x - 15, pos.y - 16);
    herosprite.setColor(Color::White);
    pressed_mouse = false;
    pressed = false;
}
/////////
if (pressed_mouse == true)
 {

     if (((x <= sprite_pos.x + 15) && (sprite_pos.x + 15 <= dx) && (y <= sprite_pos.y + 16) && (sprite_pos.y + 16 <= dy) || IntRect(sprite_pos.x, sprite_pos.y, 31, 32).contains(Mouse::getPosition(window))))
     {
         //herosprite.setPosition(pos.x - 15, pos.y - 16);
         //herosprite.setColor(Color::White);
         //pressed_mouse = false;
         pressed = true;
     }

     /*herosprite.setPosition(pos.x - 15, pos.y - 16);
     herosprite.setColor(Color::White);
     pressed_mouse = false;
/
else////////////
{
    if (IntRect(sprite_pos.x, sprite_pos.y, 31, 32).contains(Mouse::getPosition(window)))
    {
        herosprite.setColor(Color::Red);
        pressed_mouse = true;
    }
}
////////////

if (pressed_mouse == true)
{
    herosprite.setPosition(pos.x - 15, pos.y - 16);
    herosprite.setColor(Color::White);
    pressed_mouse = false;
}
else
{
    if (IntRect(sprite_pos.x, sprite_pos.y, 31, 32).contains(Mouse::getPosition(window)))
    {
        herosprite.setColor(Color::Red);
        pressed_mouse = true;
    }
}

//////////////////
if (pos.x >= 0 && pos.y >= 0 && pos.x <= 1366 && pos.y <= 768)
{
    pressed_rectangle = true;
    x = pos.x;
    y = pos.y;
    cout<<x<<"\t"<<y<<endl;
}

}
}

if (event.type == Event::MouseButtonReleased)
{
if (event.key.code == Mouse::Left)
{
dx = pos.x;
dy = pos.y;
cout<<"\t"<<dx<<"\t"<<dy<<endl;

pressed_rectangle = false;
rectangle.setSize(Vector2f(0, 0));
window.display();

if (IntRect(sprite_pos.x, sprite_pos.y, 31, 32).contains(Mouse::getPosition(window)))
{
    move = true;
    herosprite.setColor(Color::Red);
    puts("OKKKKKKK");
}

if (((x <= sprite_pos.x + 15) && (sprite_pos.x + 15 <= dx) && (y <= sprite_pos.y + 16) && (sprite_pos.y + 16 <= dy))
        || ((dx <= sprite_pos.x + 15) && (sprite_pos.x + 15 <= x) && (dy <= sprite_pos.y + 16) && (sprite_pos.y + 16 <= y))
        || ((x <= sprite_pos.x + 15) && (y >= sprite_pos.y + 16) && (dx >= sprite_pos.x + 15) && (dy <= sprite_pos.y + 16))
        || ((x >= sprite_pos.x + 15) && (y <= sprite_pos.y + 16) && (dx <= sprite_pos.x + 15) && (dy >= sprite_pos.y + 16))
   )
{
    move = true;
    herosprite.setColor(Color::Red);
    puts("OKKKKKKK");
}
}
}
}

if (pressed_rectangle == true)
{
rectangle.setPosition(x, y);
rectangle.setSize(Vector2f(pos.x-x, pos.y-y));
}

window.clear();
window.draw(herosprite);
window.draw(rectangle);
window.display();
}*/




////zakomentil/////
/*////выделение прямоугольником////
//if (pressed_rectagle == false)
{
    if(pos.x >= 0 && pos.y >= 0 && pos.x <= 1366 && pos.y <= 768)
    {
        pressed_rectagle = true;
        x = pos.x;
        y = pos.y;
        cout<<x<<"\t"<<y<<endl;
    }
}
////выделение нажатием клавиши мыши////
//if (pressed_mouse == true)

i = pos.x;
j = pos.y;
{
    if ((x <= sprite_pos.x) && (sprite_pos.x <= dx) && (y <= sprite_pos.y) && (sprite_pos.y <= dy))
    {
        //herosprite.setPosition(pos.x - 15, pos.y - 16);
        cout<<"\t"<<"\t"<<"\t"<<pos.x - 15<<"\t"<<pos.y - 16<<endl;
        herosprite.setPosition(i - 15, j - 16);
        herosprite.setColor(Color::White);
        pressed_mouse = false;
    }
}
//else if (pressed_mouse == false)
{
    if (IntRect(sprite_pos.x, sprite_pos.y, 31, 32).contains(Mouse::getPosition(window)))
    {
        herosprite.setColor(Color::Red);
        pressed_mouse = true;
    }
}
}
}

if (event.type == Event::MouseButtonReleased)
{
if (event.key.code == Mouse::Left)
{
dx = pos.x;
dy = pos.y;
cout<<"\t"<<dx<<"\t"<<dy<<endl;

pressed_rectagle = false;
rectangle.setSize(sf::Vector2f(0, 0));
window.display();
}
}*/




////////////mouse_click_hero//////////
/*Image hero;
hero.loadFromFile("monsterNew.png");
hero.createMaskFromColor(Color::White);

Texture herotexture;
herotexture.loadFromImage(hero);

Sprite herosprite;
herosprite.setTexture(herotexture);
herosprite.setTextureRect(IntRect(0, 0, 31, 32));

bool pressed_mouse = false;

while (window.isOpen())
{
    Vector2i pixelPos = Mouse::getPosition(window);
    Vector2f pos = window.mapPixelToCoords(pixelPos);

    Event event;
    while (window.pollEvent(event))
    {
        Vector2f sprite_pos = herosprite.getPosition();

        if (event.type == Event::Closed)
        {
            window.close();
        }

        if (event.type == Event::MouseButtonPressed)
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                if (pressed_mouse == true)
                {
                    herosprite.setPosition(pos.x - 15, pos.y - 16);
                    herosprite.setColor(Color::White);
                    pressed_mouse = false;
                }
                else
                {
                    if (IntRect(sprite_pos.x, sprite_pos.y, 31, 32).contains(Mouse::getPosition(window)))
                    {
                        herosprite.setColor(Color::Red);
                        pressed_mouse = true;
                    }
                }
            }
        }
    }

	window.clear();
	window.draw(herosprite);
	window.display();
}*/

/////////////////КВАДРАТ///////////////////////////////
/*RectangleShape rectangle(sf::Vector2f(0, 0));
rectangle.setSize(sf::Vector2f(0, 0));
rectangle.setFillColor(Color::Transparent);
rectangle.setOutlineThickness(2);
rectangle.setOutlineColor(sf::Color(250, 150, 100));

bool pressed = false;

double x = 0;
double y = 0;
double dx = 0;
double dy = 0;

while (window.isOpen())
{
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
                if(pos.x >= 0 && pos.y >= 0 && pos.x <= 1366 && pos.y <= 768)
                {
                    pressed = true;
                    x = pos.x;
                    y = pos.y;
                    cout<<x<<"   "<<y<<endl;
                }
            }
        }
        cout<<"        "<<pos.x<<"   "<<pos.y<<endl;
        if (event.type == Event::MouseButtonReleased)
            if (event.key.code == Mouse::Left)
            {
                //if(pos.x >= 0 && pos.y >= 0)
                {
                    dx = pos.x;
                    dy = pos.y;
                    cout<<"        "<<dx<<"   "<<dy<<endl;

                    pressed = false;
                    rectangle.setSize(sf::Vector2f(0, 0));
                    window.display();

                }
            }
    }
    if (pressed == true)
    {
        rectangle.setPosition(x, y);
        rectangle.setSize(sf::Vector2f(pos.x-x, pos.y-y));
    }
    window.clear();
    window.draw(rectangle);
    window.display();
}*/



/////////////////ДВИЖЕНИЕ ГЕРОЯ////////////////////////
/*    Image hero;
    hero.loadFromFile("monsterNew.png");
    hero.createMaskFromColor(Color::White);

    Texture herotexture;
	herotexture.loadFromImage(hero);

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 0, 31, 32)); //получили нужный нам прямоугольник с котом
	herosprite.setPosition(250,250); //выводим спрайт в позицию x y

    Clock clock;
    float CurrentFrame = 0;

	while (window.isOpen())
	{
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			window.close();
		}

        if (Keyboard::isKeyPressed(Keyboard::W)) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 6) CurrentFrame -= 6;
			herosprite.setTextureRect(IntRect(0, 32 * int(CurrentFrame), 31, 32));
			herosprite.move(0, -0.2*time);
		}
		else
            herosprite.setTextureRect(IntRect(0, 0, 31, 32));

		if (Keyboard::isKeyPressed(Keyboard::A)) { herosprite.move(-0.2*time, 0); } //первая координата Х отрицательна =>идём влево
		if (Keyboard::isKeyPressed(Keyboard::D)) { herosprite.move(0.2*time, 0); } //первая координата Х положительна =>идём вправо
		if (Keyboard::isKeyPressed(Keyboard::S)) { herosprite.move(0, 0.5*time); } //вторая координата (У) положительна =>идём вниз (если не понятно почему именно вниз - смотрим предыдущие уроки)

		window.clear();
		window.draw(herosprite);
		window.display();
	}

*/

/*using namespace sf;

/////////////////КЛАСС ИГРОКА////////////////////////
class Player {
	/* это задел на следующие уроки,прошу не обращать внимания)
private: float w, h, dx, dy, x, y, speed;
		 int dir, playerScore, health;
		 bool life;
		 *//*
public:
	float w, h, dx, dy,x,y, speed;
	int dir, playerScore, health;
	bool life;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(Sprite F, float X, float Y, float W, float H){
		dir = 0; speed = 0; playerScore = 0; health = 100; dx=0;dy=0;
		life = true;
		//File = F;
		w = W; h = H;
		//image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(41, 33, 59));
		//texture.loadFromImage(image);
		//sprite.setTexture(texture);
		sprite = F;
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}

		x += dx*time;
		y += dy*time;
		speed = 0;
		sprite.setPosition(x, y);
		sprite.setOrigin(w / 2, h / 2);
		//interactionWithMap();
		if (health <= 0){ life = false; }

	}

	float getWidth(){//получить ширину объека
		return w;
	}
	void setWidth(float width){//установить ширину объекта
		w = width;
	}

	float getHeight(){//взять ширину объекта
		return h;
	}
	void setHeight(float height){//задать ширину объекта
		h = height;
	}

	float getplayercoordinateX(){
		return x;
	}
	float getplayercoordinateY(){
		return y;
	}
};

class SpriteManager{//это задел на следующие уроки,прошу не обращать внимания на эти изменения)
public:
	Image image;
	Texture texture;
	Sprite sprite;
	String name;
	String file;
	int widthOfSprite;
	int heightOfSprite;
	SpriteManager(String File,String Name){
		file = File;
		name = Name;
		image.loadFromFile("images/" + file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};


int main()
{

	RenderWindow window(VideoMode::getDesktopMode(), "Menu");//RenderWindow window(VideoMode(640, 480), "Lesson 17. kychka-pc.ru");
	//view.reset(FloatRect(0, 0, 640, 480));


	Image map_image;
	map_image.loadFromFile("1.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Image quest_image;
	quest_image.loadFromFile("1.png");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));
	s_quest.setScale(0.6f, 0.6f);

	SpriteManager playerSprite("1.png", "Hero");//это задел на следующие уроки,прошу не обращать внимания)

	Player p(playerSprite.sprite, 250, 250, 96.0, 96.0);

	float currentFrame = 0;
	Clock clock;
	bool isMove = false;//переменная для щелчка мыши по спрайту
	float dX = 0;//корректировка движения по х
	float dY = 0;//по у
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
		//std::cout << pixelPos.x << "\n";//смотрим на координату Х позиции курсора в консоли (она не будет больше ширины окна)
		//std::cout << pos.x << "\n";//смотрим на Х,которая преобразовалась в мировые координаты

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if (event.key.code == Mouse::Left)//а именно левая
					if (p.sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
						{
							//std::cout << "isClicked!\n";//выводим в консоль сообщение об этом
							dX = pos.x - p.sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
							dY = pos.y - p.sprite.getPosition().y;//тоже самое по игреку
							isMove = true;//можем двигать спрайт
						}
			if (event.type == Event::MouseButtonReleased)//если отпустили клавишу
				if (event.key.code == Mouse::Left) //а именно левую
					isMove = false; //то не можем двигать спрайт
					p.sprite.setColor(Color::White);//и даем ему прежний цвет
		}
		if (isMove) {//если можем двигать
			p.sprite.setColor(Color::Green);//красим спрайт в зеленый
			p.x = pos.x-dX;//двигаем спрайт по Х
			p.y = pos.y-dY;//двигаем по Y
			//p.sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у
		}


		p.update(time);
		window.clear();
		window.draw(p.sprite);
		window.display();
	}

	return 0;
}*/

