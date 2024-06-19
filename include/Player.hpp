#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include <iostream>

class Player : public GameObject
{
public:
    int x=0;
    int y=0;
    float moveSpeed;
    bool hasSword;
    bool hasKey;
    sf::Vector2f swordOffset;

    static const int FILAS = 20;
    static const int COLUMNAS = 20;

    char laberinto[FILAS][COLUMNAS];

    Player(const sf::Texture &texture, const sf::Vector2f &position, float speed)
        : GameObject(texture, position), moveSpeed(speed), hasSword(false), hasKey(false), swordOffset(50.f, 0.f), x(1), y(1)
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

    void moverPersonaje(char direccion)
    {
        int nuevaX = x;
        int nuevaY = y;

        if (direccion == sf::Keyboard::Left) nuevaX -= 1;
        else if (direccion == sf::Keyboard::Right) nuevaX += 1;
        else if (direccion == sf::Keyboard::Up) nuevaY -= 1;
        else if (direccion == sf::Keyboard::Down) nuevaY += 1;

        if (esMovimientoValido(nuevaX, nuevaY))
        {
            x = nuevaX;
            y = nuevaY;
            sprite.setPosition(x * sprite.getTexture()->getSize().x, y * sprite.getTexture()->getSize().y);
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !moved)
        {
            moverPersonaje(sf::Keyboard::Left);
            moved = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !moved)
        {
            moverPersonaje(sf::Keyboard::Right);
            moved = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !moved)
        {
            moverPersonaje(sf::Keyboard::Up);
            moved = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !moved)
        {
            moverPersonaje(sf::Keyboard::Down);
            moved = true;
        }
    }

    sf::FloatRect getBoundingBox() const
    {
        return sprite.getGlobalBounds();
    }
};
// class Player : public GameObject
// {
// public:
//     int x;
//     int y;
//     float moveSpeed;
//     bool hasSword;
//     bool hasKey;
//     sf::Vector2f swordOffset;

//     static const int FILAS = 20;
//     static const int COLUMNAS = 20;

//     char laberinto[FILAS][COLUMNAS];

//     Player(const sf::Texture &texture, const sf::Vector2f &position, float speed)
//         : GameObject(texture, position), moveSpeed(speed), hasSword(false), hasKey(false), swordOffset(50.f, 0.f), x(0), y(0)
//     {

//         // Inicialización del laberinto
//         char tempLaberinto[FILAS][COLUMNAS] =
//             {
//                 {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
//                 {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
//                 {'1', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '1'},
//                 {'1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '0', '1'},
//                 {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '0', '0', '1'},
//                 {'1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '1'},
//                 {'1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1'},
//                 {'1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '1', '0', '1', '0', '0', '1', '0', '0', '0', '1'},
//                 {'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '1'},
//                 {'1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '1'},
//                 {'1', '0', '1', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '0', '1'},
//                 {'1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '0', '1'},
//                 {'1', '0', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '0', '1', '0', '0', '0', '1'},
//                 {'1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '1'},
//                 {'1', '0', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1'},
//                 {'1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '1'},
//                 {'1', '0', '0', '0', '0', '1', '1', '1', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '1'},
//                 {'1', '0', '0', '0', '0', '1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1'},
//                 {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
//                 {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};
//         std::copy(&tempLaberinto[0][0], &tempLaberinto[0][0] + FILAS * COLUMNAS, &laberinto[0][0]);
//     }

//     void moverPersonaje(char direccion)
//     {
//         int nuevaX = x;
//         int nuevaY = y;
//         if (esMovimientoValido(nuevaX, nuevaY))
//         {
//             x = nuevaX;
//             y = nuevaY;
//         }
//         else
//         {
//             std::cout << "Movimiento no válido!\n";
//         }
//     }

//     bool esMovimientoValido(int nuevaX, int nuevaY)
//     {
//         if (nuevaX < 0 || nuevaX >= FILAS || nuevaY < 0 || nuevaY >= COLUMNAS)
//         {
//             return false; // Fuera de los límites del laberinto
//         }
//         if (laberinto[nuevaX][nuevaY] == '1')
//         {
//             return false; // Es una pared
//         }
//         return true;
//     }
//     void update()
//     {

//         bool moved = false;

//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sprite.getPosition().x >= 1)
//         {
//             sprite.move(-moveSpeed, 0.f);
//             x -= moveSpeed;
//             moved = true;
//         }
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !moved && sprite.getPosition().x < 640 - sprite.getTexture()->getSize().x)
//         {
//             sprite.move(moveSpeed, 0.f);
//             x += moveSpeed;
//             moved = true;
//         }
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !moved && sprite.getPosition().y >= 1)
//         {
//             sprite.move(0.f, -moveSpeed);
//             y -= moveSpeed;
//             moved = true;
//         }
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !moved && sprite.getPosition().y < 640 - sprite.getTexture()->getSize().y)
//         {
//             sprite.move(0.f, moveSpeed);
//             y += moveSpeed;
//             moved = true;
//         }
//     }

//     sf::FloatRect getBoundingBox() const
//     {
//         return sprite.getGlobalBounds();
//     }
// };