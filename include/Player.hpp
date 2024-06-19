#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include <iostream>
#include <algorithm>

class Player : public GameObject
{
public:
    int x;
    int y;
    float moveSpeed;
    bool hasSword;
    bool hasKey;
    sf::Vector2f swordOffset;

    static const int FILAS = 20;
    static const int COLUMNAS = 20;

    char laberinto[FILAS][COLUMNAS];

    Player(const sf::Texture &texture, const sf::Vector2f &position, float speed)
        : GameObject(texture, position), moveSpeed(speed), hasSword(false), hasKey(false), swordOffset(0.03f, 0.f), x(position.x / 32), y(position.y / 32)
    {
        // Inicialización del laberinto
        char tempLaberinto[FILAS][COLUMNAS] =
            {
                {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
                {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                {'1', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '1'},
                {'1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '0', '1'},
                {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '0', '0', '1'},
                {'1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '1'},
                {'1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1'},
                {'1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '1', '0', '1', '0', '0', '1', '0', '0', '0', '1'},
                {'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '1'},
                {'1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '1'},
                {'1', '0', '1', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '0', '1'},
                {'1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '0', '1'},
                {'1', '0', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '0', '1', '0', '0', '0', '1'},
                {'1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '1'},
                {'1', '0', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1'},
                {'1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '1'},
                {'1', '0', '0', '0', '0', '1', '1', '1', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '1'},
                {'1', '0', '0', '0', '0', '1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1'},
                {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};
        std::copy(&tempLaberinto[0][0], &tempLaberinto[0][0] + FILAS * COLUMNAS, &laberinto[0][0]);
    }

    void moverPersonaje(sf::Keyboard::Key direccion)
    {
        int nuevaX = x;
        int nuevaY = y;

        if (direccion == sf::Keyboard::Left) nuevaY -= 1;
        else if (direccion == sf::Keyboard::Right) nuevaY += 1;
        else if (direccion == sf::Keyboard::Up) nuevaX -= 1;
        else if (direccion == sf::Keyboard::Down) nuevaX += 1;

        if (esMovimientoValido(nuevaX, nuevaY))
        {
            x = nuevaX;
            y = nuevaY;
            sprite.setPosition(y * 32, x * 32);  // Ajuste de posición
        }
        else
        {
            std::cout << "Movimiento no válido!\n";
        }
    }

    bool esMovimientoValido(int nuevaX, int nuevaY)
    {
        if (nuevaX < 0 || nuevaX >= FILAS || nuevaY < 0 || nuevaY >= COLUMNAS)
        {
            return false; // Fuera de los límites del laberinto
        }
        if (laberinto[nuevaX][nuevaY] == '1')
        {
            return false; // Es una pared
        }
        return true;
    }

    void update()
    {
        bool moved = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && esMovimientoValido(x, y - 1))
        {
            moverPersonaje(sf::Keyboard::Left);
            moved = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && esMovimientoValido(x, y + 1))
        {
            moverPersonaje(sf::Keyboard::Right);
            moved = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && esMovimientoValido(x - 1, y))
        {
            moverPersonaje(sf::Keyboard::Up);
            moved = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && esMovimientoValido(x + 1, y))
        {
            moverPersonaje(sf::Keyboard::Down);
            moved = true;
        }
    }
};



// #pragma once
// #include <SFML/Graphics.hpp>
// #include <GameObject.hpp>

// class Player : public GameObject
// {
// public:
//     float moveSpeed;
//     bool hasSword;
//     bool hasKey;
//     sf::Vector2f swordOffset;

//     Player(const sf::Texture &texture, const sf::Vector2f &position, float speed)
//         : GameObject(texture, position), moveSpeed(speed), hasSword(false), hasKey(false), swordOffset(50.f, 0.f) {}

//     void update()
//     {
//         bool moved = false;
        
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sprite.getPosition().x >= 1)
//         {
//             sprite.move(-moveSpeed, 0.f);
//             moved = true;
//         }
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !moved && sprite.getPosition().x < 640 - sprite.getTexture()->getSize().x)
//         {
//             sprite.move(moveSpeed, 0.f);
//             moved = true;
//         }
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !moved && sprite.getPosition().y >= 1)
//         {
//             sprite.move(0.f, -moveSpeed);
//             moved = true;
//         }
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !moved && sprite.getPosition().y < 640 - sprite.getTexture()->getSize().y)
//         {
//             sprite.move(0.f, moveSpeed);
//             moved = true;
//         }
//     }

//     sf::FloatRect getBoundingBox() const
//     {
//         return sprite.getGlobalBounds();
//     }
// };
