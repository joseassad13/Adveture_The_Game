#pragma once 
#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <list>
#include <Pared.hpp>
#include <Entidad.hpp>
#include <Dragon.hpp>
#include <GameObject.hpp>
#include <SFML/Audio.hpp>
#include <Game.hpp>
#include <Enemy.hpp>
#include <Puntaje.hpp>
#include <Player.hpp>


class Key : public GameObject
{
public:
    bool collected;

    Key(const sf::Texture &texture, const sf::Vector2f &position)
        : GameObject(texture, position), collected(false) {}

    void respawn()
    {
        float x = static_cast<float>(rand() % (630 - static_cast<int>(sprite.getTexture()->getSize().x)));
        float y = static_cast<float>(rand() % (630 - static_cast<int>(sprite.getTexture()->getSize().y)));
        sprite.setPosition(x, y);
        collected = false;
    }
};