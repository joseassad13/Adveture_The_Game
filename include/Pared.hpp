#pragma once
#include <SFML/Graphics.hpp>

class Pared
{
public:
    bool esAccesible;
    bool esSalida;
    sf::Vector2f pos;
    sf::Texture texture;
    sf::Sprite sprite;
    Pared(std::string, float, float, bool, bool);
    bool setUpSprite(std::string);
};

Pared::Pared(std::string textureName, float x, float y, bool accesible, bool salida)
{
    if (!setUpSprite(textureName))
    {
        return;
    }
    pos = sf::Vector2f(x, y);
    sprite.setPosition(pos);
    esAccesible = accesible;
    esSalida = salida;
}

bool Pared::setUpSprite(std::string textureName)
{
    if (!texture.loadFromFile(textureName))
    {
        return false;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
    return true;
}

// #pragma once
// #include <SFML/Graphics.hpp>

// class Pared
// {
// public:
//     bool esAccesible;
//     bool esSalida;
//     sf::Vector2f pos;
//     sf::Texture texture;
//     sf::Sprite sprite;
//     Pared(std::string, float, float, bool, bool);
//     bool setUpSprite(std::string);
// };

// Pared::Pared(std::string textureName, float x, float y, bool accesible, bool salida)
// {
//     if (!setUpSprite(textureName))
//     {
//         return;
//     }
//     pos = sf::Vector2f(x, y);
//     sprite.setPosition(pos);
//     esAccesible = accesible;
//     esSalida = salida;
// }

// bool Pared::setUpSprite(std::string textureName)
// {
//     if (!texture.loadFromFile(textureName))
//     {
//         return false;
//     }
//     texture.setSmooth(true);
//     sprite.setTexture(texture);
//     sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
//     return true;
// }
