#include <SFML/Graphics.hpp>
#ifndef PARED_H
#define PARED_H

class Pared
{
public:
    bool esAccesible;
    bool esSalida;
    sf::Vector2f pos;
    sf::Texture texture;
    sf::Sprite sprite;
    Pared(std::string,float,float,bool,bool);
    bool setUpSprite(std::string);
};

#endif