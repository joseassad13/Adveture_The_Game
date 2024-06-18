#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <list>
#include <Personaje.hpp>
#include <Pared.hpp>
#include <Entidad.hpp>
#include <Dragon.hpp>
#include <SFML/Audio.hpp>
#include <Personaje.hpp>
#include <Key.hpp>
#include <Game.hpp>
#include <Enemy.hpp>
#include <Puntaje.hpp>
#include <Player.hpp>

class GameObject
{
public:
    sf::Sprite sprite;

    GameObject(const sf::Texture &texture, const sf::Vector2f &position, const sf::Vector2f &scale = sf::Vector2f(1.f, 1.f))
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