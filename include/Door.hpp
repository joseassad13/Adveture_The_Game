#pragma once
#include <SFML/Graphics.hpp>
#include <Laberinto.hpp>

class Door : public Laberinto
{
    char simbolo;

public:
    sf::Sprite sprite;
    Door(const sf::Texture &texture, const sf::Vector2f &position)
    {
        int y = 0;
        int x = 0;
        sf::Sprite bloque;
        if (simbolo = '2')
        {
            bloque = generarBloque(2);
        }
        sprite.setPosition(sf::Vector2f(x * 32, y * 32));
    }
    sf::Vector2f getPosition() const
    {
        return sprite.getPosition();
    }
};
