#pragma once
#include <SFML/music.hpp>
#include <SFML/Graphics.hpp>

class Musica
{
private:
public:
    Musica(sf::Music musica);
    ~Musica();
};

Musica::Musica(sf::Music musica)
{
    if (!music.openFromFile("./assets/Music/slow-2021-08-16_-_8_Bit_Adventure_-_www.FesliyanStudios.com.mp3"))
    {
        // Error al cargar el archivo de música
        return -1;
    }

    // Reproducir la música
    music.play();
}

Musica::~Musica()
{
}
