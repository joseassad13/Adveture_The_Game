#pragma once
#include <SFML/Graphics.hpp>

class Objeto
{
public:
    sf::Sprite sprite;

    objetoJuego(const sf::Texture &texture, const sf::Vector2f &position, const sf::Vector2f &scale = sf::Vector2f(1.f, 1.f))
    {
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(scale);
    }

    void setPosition(const sf::Vector2f &position)
    {
        sprite.setPosition(position);
    }

    sf::Vector2f getPosition() const
    {
        return sprite.getPosition();
    }

    void move(const sf::Vector2f &offset)
    {
        sprite.move(offset);
    }
};
