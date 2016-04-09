#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>

#include "map.h"

using namespace std;
using namespace sf;

void menu(RenderWindow & window);
void game(RenderWindow & window);
void settings(RenderWindow & window);

class Images
{
public:
    int positionX;
    int positionY;
    int originX;
    int originY;
    String File;
    Image image;
    Texture texture;
    Sprite sprite;

    Images(String F, int positionX = 0, int positionY = 0, int originX = 0, int originY = 0)    //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
    {
        File = F;
        image.loadFromFile(File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setPosition(positionX, positionY);
        sprite.setOrigin(Vector2f(originX, originY));
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
        window.clear(Color(129, 181, 221)); // Зачем ?

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
}

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

int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "Menu");//, Style::Fullscreen);
    window.setFramerateLimit(50);
    //menu(window);

    ////hero////
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

    bool pressed_mouse = false;
    bool pressed_rectagle = false;

    double x = 0;   // координата х при нажатии на лкм
    double y = 0;   // координата у при нажатии на лкм

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
                    ////выделение прямоугольником////
                    if (pressed_rectagle == false)
                    {
                        if(pos.x >= 0 && pos.y >= 0 && pos.x <= 1366 && pos.y <= 768)
                        {
                            pressed_rectagle = true;
                            x = pos.x;
                            y = pos.y;
                        }
                    }
                    ////выделение нажатием клавиши мыши////
                    if (pressed_mouse == true)
                    {
                        herosprite.setPosition(pos.x - 15, pos.y - 16);
                        herosprite.setColor(Color::White);
                        pressed_mouse = false;
                    }
                    else if (pressed_mouse == false)
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
                    {
                        pressed_rectagle = false;
                        rectangle.setSize(sf::Vector2f(0, 0));
                        window.display();
                    }
                }
            }
        }

        if (pressed_rectagle == true)
        {
            rectangle.setPosition(x, y);
            rectangle.setSize(sf::Vector2f(pos.x-x, pos.y-y));
        }

        window.clear();
        window.draw(herosprite);
        window.draw(rectangle);
        window.display();
    }

    window.close();
    return 0;
}

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
/*
    if (Mouse::isButtonPressed(sf::Mouse::Left))
        herosprite.setColor(Color::Red);
*/
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

