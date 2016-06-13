#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>

#include "../Units/Enemy.hpp"
#include "../Units/Player.hpp"

#include "../Buildings/BuildingEnemy.hpp"
#include "../Buildings/BuildingPlayer.hpp"

#define MAX_COUNT_HEROS 50

using namespace std;
using namespace sf;

class Options
{
public:
    int checkOffHelp;
    int checkOffMusic;
    int numMusic;
    string fileNameMusic;

    Options();
};

void build(RenderWindow & window);
void Artificial_Intelligence(int & Step, list<Enemy*> & enemy, Images & imagePlayer, BuildingEnemy & boiler, int & checkNewEnemy, Images & scaleUpdate, Database & db);

void menu(RenderWindow & window);
void settings(RenderWindow & window, Options & options);
void game(RenderWindow & window, Options & options);

#endif
