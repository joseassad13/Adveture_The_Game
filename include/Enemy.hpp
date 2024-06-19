#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include <iostream>
#include <algorithm>
#include <cmath> // Necesario para std::abs

class Enemy : public GameObject
{
public:
    int x;
    int y;
    float speed;
    bool alive;
    sf::Clock clock;        // Reloj para medir el tiempo de movimiento
    sf::Clock respawnClock; // Reloj para el respawn
    sf::Time delay;         // Tiempo de espera entre movimientos

    static const int FILAS = 20;
    static const int COLUMNAS = 20;

    char laberinto[FILAS][COLUMNAS];

    Enemy(const sf::Texture &texture, const sf::Vector2f &position, float speed)
        : GameObject(texture, position, sf::Vector2f(0.3f, 0.3f)), speed(speed), alive(true)
    {
        x = static_cast<int>(position.y / 32);
        y = static_cast<int>(position.x / 32);

        // Inicialización del laberinto
        char tempLaberinto[FILAS][COLUMNAS] =
            {
                {'1', '2', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
                {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                {'1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '0', '1'},
                {'1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '1'},
                {'1', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '0', '1'},
                {'1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                {'1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '1', '1', '0', '0', '1'},
                {'1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1', '0', '1', '0', '0', '1'},
                {'1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
                {'1', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
                {'1', '0', '0', '0', '1', '1', '1', '0', '1', '1', '1', '1', '0', '1', '1', '0', '0', '0', '0', '1'},
                {'1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                {'1', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                {'1', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1'},
                {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '1'},
                {'1', '0', '1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                {'1', '0', '1', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '1', '1', '0', '1'},
                {'1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '1'},
                {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};

        std::copy(&tempLaberinto[0][0], &tempLaberinto[0][0] + FILAS * COLUMNAS, &laberinto[0][0]);

        delay = sf::seconds(0.2f); // Establecer tiempo de espera entre movimientos

        // Establecer el rectángulo de textura inicial del sprite
        sprite.setTextureRect(sf::IntRect(64, 64, 64, 64));
    }

    bool esMovimientoValido(int nuevaX, int nuevaY)
    {
        // Verificar si los índices están dentro de los límites del laberinto
        if (nuevaX < 0 || nuevaX >= FILAS || nuevaY < 0 || nuevaY >= COLUMNAS)
        {
            return false; // Fuera de los límites del laberinto
        }
        // Verificar si la celda no es una pared
        if (laberinto[nuevaX][nuevaY] == '1')
        {
            return false; // Es una pared
        }
        return true; // Movimiento válido
    }

    void updateAnimation(int frameCount, int frameWidth, int frameHeight, sf::Clock &animationClock, int &currentFrame)
    {
        // Cambiar el marco de animación cada 0.15 segundos
        if (animationClock.getElapsedTime().asSeconds() > 0.20f)
        {
            currentFrame = (currentFrame + 1) % frameCount;
            sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            animationClock.restart();
        }
    }

    void updateMovement(const sf::Vector2f &targetPosition)
    {
        if (alive && clock.getElapsedTime() >= delay)
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

            int nuevaX = x + static_cast<int>(direction.y);
            int nuevaY = y + static_cast<int>(direction.x);

            if (esMovimientoValido(nuevaX, nuevaY))
            {
                x = nuevaX;
                y = nuevaY;
                sprite.setPosition(y * 32, x * 32);
                clock.restart();
            }
        }
    }

    void checkRespawn()
    {
        // Revivir al enemigo después de 3 segundos
        if (!alive && respawnClock.getElapsedTime().asSeconds() > 5.f)
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