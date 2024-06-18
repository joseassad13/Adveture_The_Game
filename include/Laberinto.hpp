#pragma once

#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

class Laberinto
{
private:
    std::list<std::list<sf::Sprite>> mapa1;
    sf::Texture texturaBloques;

    sf::Sprite generarBloque(int tipo)
    {
        sf::Sprite bloque;
        int bloquePosX = 0;
        int bloquePosY = 0;

        switch (tipo)
        {
        case 0: // Open space
            bloquePosX = 1;
            bloquePosY = 2;
            break;
        case 1: // Wall
            bloquePosX = 4;
            bloquePosY = 1;
            break;
        case 2: // Some other type
            bloquePosX = 0;
            bloquePosY = 3;
            break;
        default:
            break;
        }

        bloque = sf::Sprite(texturaBloques);
        int bloqueTamaño = 32;
        bloque.setTextureRect(
            sf::IntRect(
                bloquePosX * bloqueTamaño,
                bloquePosY * bloqueTamaño,
                bloqueTamaño,
                bloqueTamaño));

        return bloque;
    }

public:
    Laberinto(const std::string &filename = "./assets/salas/laberinto1.txt")
    {
        std::ifstream inputFile(filename);
        std::string line;

        if (!inputFile.is_open())
        {
            std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
            // Aquí podrías lanzar una excepción o tomar otra acción según lo necesites
            return;
        }

        if (!texturaBloques.loadFromFile("./assets/images/textura_salas.png"))
        {
            std::cerr << "No se pudo cargar la textura" << std::endl;
            // Igualmente, manejar el error de carga de textura de manera adecuada
            return;
        }

        int y = 0;
        while (std::getline(inputFile, line))
        {
            std::list<sf::Sprite> temp;
            int x = 0;
            for (char simbolo : line)
            {
                sf::Sprite bloque;
                switch (simbolo)
                {
                case '0':
                    bloque = generarBloque(0);
                    break;
                case '1':
                    bloque = generarBloque(1);
                    break;
                case '2':
                    bloque = generarBloque(2);
                    break;
                default:
                    break;
                }
                bloque.setPosition(sf::Vector2f(x * 32, y * 32));
                temp.emplace_back(bloque);
                x++;
            }
            mapa1.emplace_back(temp);
            y++;
        }

        inputFile.close();
    }

    ~Laberinto() {}

    void Draw(sf::RenderWindow &window)
    {
        for (auto &linea : mapa1)
        {
            for (auto &bloque : linea)
            {
                window.draw(bloque);
            }
        }
    }

    bool checkCollision(const sf::FloatRect &boundingBox)
    {
        for (auto &linea : mapa1)
        {
            for (auto &bloque : linea)
            {
                if (boundingBox.intersects(bloque.getGlobalBounds()))
                {
                    return true;
                }
            }
        }
        return false;
    }
};


// #pragma once
// #include <string>
// #include <list>
// #include <fstream>
// #include <iostream>
// #include <SFML/Graphics.hpp>

// using namespace std;

// class Laberinto
// {
// private:
//     int cantidadSalas;
//     list<list<sf::Sprite>> mapa1;
//     sf::Texture texturaBloques;

// public:
//     sf::Sprite generarBloque(int tipo, sf::Texture &texture)
//     {
//         sf::Sprite bloque;

//         int bloquePosX;
//         int bloquePosY;

//         switch (tipo)
//         {
//         case 0:
//             bloquePosX = 1;
//             bloquePosY = 2;
//             break;
//         case 1:
//             bloquePosX = 4;
//             bloquePosY = 1;
//             break;
//         case 2:
//             bloquePosX = 0;
//             bloquePosY = 3;
//             break;

//         default:
//             break;
//         }

//         bloque = sf::Sprite(texture);

//         int bloqueTamaño = 32;
//         bloque.setTextureRect(
//             sf::IntRect(
//                 bloquePosX * bloqueTamaño,
//                 bloquePosY * bloqueTamaño,
//                 bloqueTamaño,
//                 bloqueTamaño));

//         return bloque;
//     }

//     Laberinto(std::string filename = "./assets/salas/laberinto1.txt")
//     {
//         std::string line;

//         // Crear un objeto ifstream
//         std::ifstream inputFile(filename);

//         // Verificar si el archivo se abrió correctamente
//         if (!inputFile.is_open())
//         {
//             std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
//         }

//         if (!texturaBloques.loadFromFile("./assets/images/textura_salas.png"))
//         {
//             std::cerr << "No se pudo cargar la textura" << std::endl;
//         }

//         int y = 0;
//         while (std::getline(inputFile, line))
//         {
//             list<sf::Sprite> temp;
//             int x = 0;
//             for (auto &&simbolo : line)
//             {
//                 sf::Sprite bloque;
//                 if (simbolo == '0')
//                 {
//                     bloque = generarBloque(0, texturaBloques);
//                 }
//                 else if (simbolo == '1')
//                 {
//                     bloque = generarBloque(1, texturaBloques);
//                 }
//                 else if (simbolo == '2')
//                 {
//                     bloque = generarBloque(2, texturaBloques);
//                 }
//                 bloque.setPosition(sf::Vector2f(x * 32, y * 32));
//                 temp.emplace_back(bloque);
//                 x++;
//             }
//             mapa1.emplace_back(temp);
//             y++;
//         }

//         // Cerrar el archivo
//         inputFile.close();
//     }

//     sf::Sprite generarBloque(int tipo, sf::Texture &texture)
//     {
//         sf::Sprite bloque;
//         int bloquePosX = 0;
//         int bloquePosY = 0;

//         switch (tipo)
//         {
//         case 0: // Open space
//             bloquePosX = 1;
//             bloquePosY = 2;
//             break;
//         case 1: // Wall
//             bloquePosX = 4;
//             bloquePosY = 1;
//             break;
//         case 2: // Some other type
//             bloquePosX = 0;
//             bloquePosY = 3;
//             break;
//         default:
//             break;
//         }

//         bloque = sf::Sprite(texture);
//         int bloqueTamaño = 32;
//         bloque.setTextureRect(
//             sf::IntRect(
//                 bloquePosX * bloqueTamaño,
//                 bloquePosY * bloqueTamaño,
//                 bloqueTamaño,
//                 bloqueTamaño));

//         return bloque;
//     }

//     ~Laberinto() {}

//     void Draw(sf::RenderWindow &window)
//     {
//         for (auto &&linea : mapa1)
//         {
//             for (auto &&bloque : linea)
//             {
//                 window.draw(bloque);
//             }
//         }
//     }

//     bool checkCollision(const sf::FloatRect &boundingBox)
//     {
//         for (auto &&linea : mapa1)
//         {
//             for (auto &&bloque : linea)
//             {
//                 if (boundingBox.intersects(bloque.getGlobalBounds()))
//                 {
//                     return true;
//                 }
//             }
//         }
//         return false;
//     }
// };
