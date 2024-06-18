#pragma once
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

class Enemy : public GameObject
{
public:
    float speed;
    bool alive;
    sf::Clock respawnClock;

    Enemy(const sf::Texture &texture, const sf::Vector2f &position, float speed)
        : GameObject(texture, position, sf::Vector2f(0.3f, 0.3f)), speed(speed), alive(true)
    {
        sprite.setTextureRect(sf::IntRect(64, 64, 64, 64));
    }

    void updateAnimation(int frameCount, int frameWidth, int frameHeight, sf::Clock &animationClock, int &currentFrame)
    {
        if (animationClock.getElapsedTime().asSeconds() > 0.15f)
        {
            currentFrame = (currentFrame + 1) % 2;
            sprite.setTextureRect(sf::IntRect((currentFrame * 69), 0, 69, 185));
            animationClock.restart();
        }
        // (currentFrame * frameWidth, 45, frameWidth, frameHeight)
    }

    void updateMovement(const sf::Vector2f &targetPosition)
    {
        if (alive)
        {
            sf::Vector2f direction = targetPosition - sprite.getPosition();
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length != 0)
                direction /= length;
            sprite.move(direction * speed);
        }
    }

    void checkRespawn()
    {
        if (!alive && respawnClock.getElapsedTime().asSeconds() > 3.f)
        {
            alive = true;
            sprite.setPosition(100.f, 100.f);
        }
    }

    void kill()
    {
        alive = false;
        respawnClock.restart();
    }
};