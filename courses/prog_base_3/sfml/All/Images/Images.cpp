#include "Images.hpp"

Images:: Images(string file, int positionX, int positionY, int width, int height, int Radius)
{
    this->image.loadFromFile(file);
    this->texture.loadFromImage(image);
    this->sprite.setTexture(texture);
    this->sprite.setPosition(positionX, positionY);
    this->sprite.setOrigin(Vector2f(width/2, height/2));
    this->x = positionX;
    this->y = positionY;
    this->w = width;
    this->h = height;
    this->R = Radius;
}

Images:: Images(Sprite & spr, int positionX, int positionY, int width, int height, int Radius)
{
    this->sprite = spr;
    this->sprite.setPosition(positionX, positionY);
    this->sprite.setOrigin(Vector2f(width/2, height/2));
    this->x = positionX;
    this->y = positionY;
    this->w = width;
    this->h = height;
    this->R = Radius;
}

