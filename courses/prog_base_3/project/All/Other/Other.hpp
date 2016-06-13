#ifndef OTHER_HPP
#define OTHER_HPP

#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

double length(int x1, int y1, int x2, int y2);
void saveHero(const char * file, int Name, int R, int x, int y);
void fileHeroCleaning(const char * file);
void heroCleaning(const char * file, int index);
bool checkPos(const char * file, int posX, int posY, int index);

#endif
