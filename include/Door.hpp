#pragma once
#include <SFML/Graphics.hpp>
#include <GameObject.hpp>


class Door : public GameObject
{
public:
    Door(const sf::Texture &texture, const sf::Vector2f &position)
        : GameObject(texture, position) {}
};