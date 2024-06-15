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

    int bloquePosX = 0;
    int bloquePosY = 0;

    switch (tipo)
    {
    case 0:
        bloquePosX = 5;
        bloquePosY = 0;
        break;
    case 1:
        bloquePosX = 3;
        bloquePosY = 1;
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