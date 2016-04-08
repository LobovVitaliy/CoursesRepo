#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>

using namespace std;
using namespace sf;

void game();
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
        // ��������� ��� ������� ����, ������� ���� ������� � ��������� �������� �����
        Event event;
        while (window.pollEvent(event))
        {
            // "������ ��������" �������: �� ��������� ����
            if (event.type == Event::Closed)
                window.close();
        }

        NewGame_S.setColor(Color::White);
        LoadGame_S.setColor(Color::White);
        SettingsGame_S.setColor(Color::White);
        QuitGame_S.setColor(Color::White);

        menuNum = 0;
        window.clear(Color(129, 181, 221)); // ����� ?

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
                game();
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
        // ��������� ��� ������� ����, ������� ���� ������� � ��������� �������� �����
        Event event;
        while (window.pollEvent(event))
        {
            // "������ ��������" �������: �� ��������� ����
            if (event.type == Event::Closed)
                window.close();
        }

        window.draw(SettingsBackground_S);
        window.draw(Settings_S);
        window.display();
    }
}

void game() {
    RenderWindow window(VideoMode::getDesktopMode(), "Menu");//, Style::Fullscreen);

    Texture Background_T, NewGame_T, LoadGame_T, SettingsGame_T, QuitGame_T;
    Background_T.loadFromFile("Background.png");

    Sprite Background_S, NewGame_S, LoadGame_S, SettingsGame_S, QuitGame_S;

    while (!Keyboard::isKeyPressed(Keyboard::Escape))
    {
        // ��������� ��� ������� ����, ������� ���� ������� � ��������� �������� �����
        Event event;
        while (window.pollEvent(event))
        {
            // "������ ��������" �������: �� ��������� ����
            if (event.type == Event::Closed)
                window.close();
        }
        window.draw(Background_S);
        window.display();
    }
}

int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "Menu");//, Style::Fullscreen);
    menu(window);
    window.close();
    return 0;
}

/*using namespace sf;

////////////////////////////////////////////////////����� ������////////////////////////
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

