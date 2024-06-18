#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <list>
#include <Sala.hpp>
#include <Laberinto.hpp>


using namespace std;

//------------------------------------------generador de mapas--------------------------------------------------//
int main()
{
    Laberinto laberinto;
    float windowHeight = 640;
    float windowWidth = 640;
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
        for (auto &&linea : laberinto.generarBloque())
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