#pragma once
#include <Objeto.hpp>

class Door : public Objeto
{
public:
    Door(const sf::Texture &texture, const sf::Vector2f &position)
        : objetoJuego(texture, position) {}
};