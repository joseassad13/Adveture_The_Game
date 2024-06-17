#include <iostream>
#include <fstream>
#include <Dragon.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <list>
#include <Personaje.hpp>
#include<Sala.hpp>
#include <Pared.hpp>
#include <Entidad.hpp>
#include <SFML/Audio.hpp>
#include <Personaje.hpp>
using namespace std;

//------------------------------------------generador de mapas--------------------------------------------------//
int main()
{
    float windowHeight = 640;
    float windowWidth = 960;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Lector laberinto");

    
    //---------------------------------abrir pestaña mapa-----------------------------------------------------------//
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        for (auto &&linea : mapa1)
        {
            for (auto &&bloque : linea)
            {
                window.draw(bloque);
            }
        }

        window.display();
    }
    //-----------------------------------------------------------------------------------------------------------

    return 0;
}