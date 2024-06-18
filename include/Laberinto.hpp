#pragma once
#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Laberinto
{
private:
    int cantidadSalas;
    list<list<sf::Sprite>> mapa1;

public:
    Laberinto(std::string filename)
    {
        std::string line;

        // Crear un objeto ifstream
        std::ifstream inputFile(filename);

        // Verificar si el archivo se abrió correctamente
        if (!inputFile.is_open())
        {
            std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
        }

        sf::Texture texturaBloques;
        if (!texturaBloques.loadFromFile("./assets/images/textura_salas.png"))
        {
        }

        int y = 0;
        while (std::getline(inputFile, line))
        {
            // std::cout << line << std::endl;
            list<sf::Sprite> temp;
            int x = 0;
            for (auto &&simbolo : line)
            {
                sf::Sprite bloque;
                if (simbolo == '0')
                {
                    bloque = generarBloque(0, texturaBloques);
                }
                if (simbolo == '1')
                {
                    bloque = generarBloque(1, texturaBloques);
                }
                if (simbolo == '2')
                {
                    bloque = generarBloque(2, texturaBloques);
                }
                bloque.setPosition(sf::Vector2f(x * 32, y * 32));
                temp.emplace_back(bloque);
                x++;
            }
            mapa1.emplace_back(temp);
            y++;
        }

        // Cerrar el archivo
        inputFile.close();
    }
    sf::Sprite generarBloque(int tipo, sf::Texture &texture)
    {
        sf::Sprite bloque;

        int bloquePosX;
        int bloquePosY;

        switch (tipo)
        {
        case 0:
            bloquePosX = 1;
            bloquePosY = 2;
            break;
        case 1:
            bloquePosX = 4;
            bloquePosY = 1;
            break;
        case 2:
            bloquePosX = 0;
            bloquePosY = 3;
            break;

        default:
            break;
        }

        bloque = sf::Sprite(texture);

        int bloqueTamaño = 32;
        bloque.setTextureRect(
            sf::IntRect(
                bloquePosX * bloqueTamaño,
                bloquePosY * bloqueTamaño,
                bloqueTamaño,
                bloqueTamaño));

        return bloque;
    }
    ~Laberinto() {}
    void Draw(sf::RenderWindow& window){
        for (auto &&linea : mapa1)
        {
            for (auto &&bloque : linea)
            {
                window.draw(bloque);
            }
        }
    }
};