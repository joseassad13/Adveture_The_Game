#include <SFML/Graphics.hpp>
#include <list>
#include <Entidad.hpp>
#include <Personaje.hpp>
#include <Dragon.hpp>
#include <Sala.hpp>
using namespace std;

int main()
{
    float windowHeight = 640;
    float windowWidth = 960;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "ADVENTURE");

    list<Personaje *> entidades;
    entidades.push_back(new Personaje());

    Sala sala = Sala();

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

        for (int i = 0; i < sala.tamanioPared; i++)
        {
            for (int j = 0; j < sala.tamanioPared; j++)
            {
                window.draw(sala.paredes[i][j]->sprite);
            }
        }

        for (auto &&e : entidades)
        {
            e->Update();
        }

        for (auto &&e : entidades)
        {
            e->Draw(window);
        }
        window.display();
    }
}