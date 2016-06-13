#ifndef IMAGES_HPP
#define IMAGES_HPP

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Images
{
public:
    int x, y, w, h, R;

    Image image;
    Texture texture;
    Sprite sprite;

    Images(string file, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int Radius = 0);
    Images(Sprite & spr, int positionX = 0, int positionY = 0, int width = 0, int height = 0, int Radius = 0);
};

#endif
