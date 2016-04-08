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

    Images(String F, int positionX = 0, int positionY = 0, int originX = 0, int originY = 0)    //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
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
        window.clear(Color(129, 181, 221)); // ����� ?
        //window.clear();

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

int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "Menu");//, Style::Fullscreen);
    //menu(window);
    /*
        if (Mouse::isButtonPressed(sf::Mouse::Left))
            herosprite.setColor(Color::Red);
    */
    Image hero;
    hero.loadFromFile("monsterNew.png");
    hero.createMaskFromColor(Color::White);

    Texture herotexture;
	herotexture.loadFromImage(hero);

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 0, 31, 32)); //�������� ������ ��� ������������� � �����
	herosprite.setPosition(250,250); //������� ������ � ������� x y

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

		if (Keyboard::isKeyPressed(Keyboard::A)) { herosprite.move(-0.2*time, 0); } //������ ���������� � ������������ =>��� �����
		if (Keyboard::isKeyPressed(Keyboard::D)) { herosprite.move(0.2*time, 0); } //������ ���������� � ������������ =>��� ������
		if (Keyboard::isKeyPressed(Keyboard::S)) { herosprite.move(0, 0.5*time); } //������ ���������� (�) ������������ =>��� ���� (���� �� ������� ������ ������ ���� - ������� ���������� �����)

		window.clear();
		window.draw(herosprite);
		window.display();
	}

    window.close();
    return 0;
}

/*using namespace sf;

/////////////////����� ������////////////////////////
class Player {
	/* ��� ����� �� ��������� �����,����� �� �������� ��������)
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

	float getWidth(){//�������� ������ ������
		return w;
	}
	void setWidth(float width){//���������� ������ �������
		w = width;
	}

	float getHeight(){//����� ������ �������
		return h;
	}
	void setHeight(float height){//������ ������ �������
		h = height;
	}

	float getplayercoordinateX(){
		return x;
	}
	float getplayercoordinateY(){
		return y;
	}
};

class SpriteManager{//��� ����� �� ��������� �����,����� �� �������� �������� �� ��� ���������)
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

	SpriteManager playerSprite("1.png", "Hero");//��� ����� �� ��������� �����,����� �� �������� ��������)

	Player p(playerSprite.sprite, 250, 250, 96.0, 96.0);

	float currentFrame = 0;
	Clock clock;
	bool isMove = false;//���������� ��� ������ ���� �� �������
	float dX = 0;//������������� �������� �� �
	float dY = 0;//�� �
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������
		Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)
		//std::cout << pixelPos.x << "\n";//������� �� ���������� � ������� ������� � ������� (��� �� ����� ������ ������ ����)
		//std::cout << pos.x << "\n";//������� �� �,������� ��������������� � ������� ����������

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
				if (event.key.code == Mouse::Left)//� ������ �����
					if (p.sprite.getGlobalBounds().contains(pos.x, pos.y))//� ��� ���� ���������� ������� �������� � ������
						{
							//std::cout << "isClicked!\n";//������� � ������� ��������� �� ����
							dX = pos.x - p.sprite.getPosition().x;//������ �������� ����� �������� ������� � �������.��� ������������� �������
							dY = pos.y - p.sprite.getPosition().y;//���� ����� �� ������
							isMove = true;//����� ������� ������
						}
			if (event.type == Event::MouseButtonReleased)//���� ��������� �������
				if (event.key.code == Mouse::Left) //� ������ �����
					isMove = false; //�� �� ����� ������� ������
					p.sprite.setColor(Color::White);//� ���� ��� ������� ����
		}
		if (isMove) {//���� ����� �������
			p.sprite.setColor(Color::Green);//������ ������ � �������
			p.x = pos.x-dX;//������� ������ �� �
			p.y = pos.y-dY;//������� �� Y
			//p.sprite.setPosition(pos.x - dX, pos.y - dY);//����� � ��� ��������,���� � ��� ���� � � �
		}


		p.update(time);
		window.clear();
		window.draw(p.sprite);
		window.display();
	}

	return 0;
}*/

