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



/*int main(int argc, char *argv[])
{
    ifstream fs("map1.txt", ios::in | ios::binary);

    while (fs.getline(buffer[countStr], 50))
    {
        countStr++;
    }
    fs.close();


    fstream file;
    file.open("map1.txt", ios::out);
    file << "";
    file.close();

    ofstream fout("map1.txt", std::ios_base::app);
    for(int k = 0; k < countStr; k++)
    {
        //if(k != delIndex)
            fout << buffer[k] << "\n";
    }
    fout.close();

    return 0;
}*/










/*
int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "Menu");//, Style::Fullscreen);
    window.setFramerateLimit(50);
    //menu(window);

fileHeroCleaning();

    View view(FloatRect(0, 0, 1366, 768));
    //view.zoom(3.4f);
    Images map("Images/map.png");

    list<Hero*> heros;
    list<Hero*> :: iterator it;

    for(int i = 0; i < 3; i++)
    {
        heros.push_back(new Hero("Images/hero_40x40.png", 300 + (i * 25), 300 + (i * 25), 40, 40));
    }

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

                    for (it = heros.begin(); it != heros.end(); it++)
                    {
                        (*it)->select(pos.x, pos.y);
                    }

                    pressed_rectangle = true;
                    pressed_LKM_X = pos.x;
                    pressed_LKM_Y = pos.y;
                }

                if (event.key.code == Mouse::Right)
                {
                    int i = 0;
                    for (it = heros.begin(); it != heros.end(); it++, i++)
                    {
                        (*it)->endPos(pos.x, pos.y, i);
                    }
                }
            }

            if (event.type == Event::MouseButtonReleased)
            {
                if (event.key.code == Mouse::Left)
                {
                    released_LKM_X = pos.x;
                    released_LKM_Y = pos.y;

                    for (it = heros.begin(); it != heros.end(); it++)
                    {
                        (*it)->select(pressed_LKM_X, pressed_LKM_Y, released_LKM_X, released_LKM_Y);
                    }

                    pressed_rectangle = false;
                    rectangle.setSize(Vector2f(0, 0));
                    window.display();
                }
            }
        }

        for (it = heros.begin(); it != heros.end(); it++)
        {
			(*it)->update(time);
		}

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

        for (it = heros.begin(); it != heros.end(); it++)
        {
			(*it)->draw(window);
		}

        window.draw(rectangle);
        window.display();
    }

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
