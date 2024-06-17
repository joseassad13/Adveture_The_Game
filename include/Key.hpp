#pragma once 
#include <Objeto.hpp>

class Key : public Objeto
{
public:
    bool collected;

    Key(const sf::Texture &texture, const sf::Vector2f &position)
        : objetoJuego(texture, position), collected(false) {}

    void respawn()
    {
        float x = static_cast<float>(rand() % (800 - static_cast<int>(sprite.getTexture()->getSize().x)));
        float y = static_cast<float>(rand() % (600 - static_cast<int>(sprite.getTexture()->getSize().y)));
        sprite.setPosition(x, y);
        collected = false;
    }
};