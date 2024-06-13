#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Reproductor de musica");

    sf::Music music;
    if (!music.openFromFile("./assets/Music/slow-2021-08-16_-_8_Bit_Adventure_-_www.FesliyanStudios.com.mp3"))
    {
        // Error al cargar el archivo de música
        return -1;
    }

    // Reproducir la música
    music.play();

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
        // Dibujar elementos adicionales en la ventana si es necesario
        window.display();

        // Esperar hasta que la música termine
        if (music.getStatus() != sf::Music::Playing)
        {
            window.close();
        }
    }

    return 0;
}
