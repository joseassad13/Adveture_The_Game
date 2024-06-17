#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <list>
using namespace std;

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