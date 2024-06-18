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
#include <GameObject.hpp>
#include <SFML/Audio.hpp>
#include <Personaje.hpp>
#include <Key.hpp>
#include <Game.hpp>
#include <Enemy.hpp>
#include <Puntaje.hpp>
#include <Player.hpp>

class Door : public GameObject
{
public:
    Door(const sf::Texture &texture, const sf::Vector2f &position)
        : GameObject(texture, position) {}
};