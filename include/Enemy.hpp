#pragma once
#include <Objeto.hpp>



class Enemy : public Objeto
{
public:
    float speed;
    bool alive;
    sf::Clock respawnClock;

    Enemy(const sf::Texture &texture, const sf::Vector2f &position, float speed)
        : objetoJuego(texture, position, sf::Vector2f(0.3f, 0.3f)), speed(speed), alive(true)
    {
        sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    }

    void updateAnimation(int frameCount, int frameWidth, int frameHeight, sf::Clock &animationClock, int &currentFrame)
    {
        if (animationClock.getElapsedTime().asSeconds() > 0.2f)
        {
            currentFrame = (currentFrame + 1) % frameCount;
            sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            animationClock.restart();
        }
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