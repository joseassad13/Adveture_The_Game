#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

    sf::Music music;
    if (!music.openFromFile("./assets/Music/slow-2021-08-16_-_8_Bit_Adventure_-_www.FesliyanStudios.com.mp3"))
    {
        // Error al cargar el archivo de música
        return -1;
    }
    music.play();

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
        if (music.getStatus() != sf::Music::Playing)
        {
            window.close();
        }
    }
}