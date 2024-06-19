#pragma once
#include <SFML/Graphics.hpp>
#include <GameObject.hpp>
#include <cmath> // Necesario para std::sqrt

class Enemy : public GameObject
{
public:
    float speed;
    bool alive;
    sf::Clock respawnClock;

    Enemy(const sf::Texture &texture, const sf::Vector2f &position, float speed)
        : GameObject(texture, position, sf::Vector2f(0.3f, 0.3f)), speed(speed), alive(true)
    {
        // Establecer el rectángulo de textura inicial del sprite
        sprite.setTextureRect(sf::IntRect(64, 64, 64, 64));
    }

    void updateAnimation(int frameCount, int frameWidth, int frameHeight, sf::Clock &animationClock, int &currentFrame)
    {
        // Cambiar el marco de animación cada 0.15 segundos
        if (animationClock.getElapsedTime().asSeconds() > 0.15f)
        {
            currentFrame = (currentFrame + 1) % 2;
            sprite.setTextureRect(sf::IntRect((currentFrame * 69), 0, 69, 185));
            animationClock.restart();
        }
    }

    void updateMovement(const sf::Vector2f &targetPosition)
    {
        if (alive)
        {
            // Calcular la dirección hacia el objetivo
            sf::Vector2f direction = targetPosition - sprite.getPosition();

            // Normalizar la dirección para moverse solo en una dimensión a la vez
            if (std::abs(direction.x) > std::abs(direction.y))
            {
                direction.y = 0;
                direction.x = direction.x > 0 ? 1 : -1;
            }
            else
            {
                direction.x = 0;
                direction.y = direction.y > 0 ? 1 : -1;
            }

            sprite.move(direction * speed);
        }
    }

    void checkRespawn()
    {
        // Revivir al enemigo después de 3 segundos
        if (!alive && respawnClock.getElapsedTime().asSeconds() > 3.f)
        {
            alive = true;
            // Reposicionar al enemigo en una ubicación predeterminada (100, 100)
            sprite.setPosition(100.f, 100.f);
        }
    }

    void kill()
    {
        // Matar al enemigo y reiniciar el reloj de respawn
        alive = false;
        respawnClock.restart();
    }

    sf::FloatRect getBoundingBox() const
    {
        return sprite.getGlobalBounds();
    }
};
