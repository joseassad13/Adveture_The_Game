#include <Dragon.hpp>
#include <SFML/Audio.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 640), "Dragon");
    // window.setFramerateLimit(60);
    Dragon dragon;
    sf::Music music;
    // --------------------------- MUSICA -------------------------------
    if (!music.openFromFile("./assets/Music/Musica_Base.mp3"))
    {
        // Error al cargar el archivo de música
        return -1;
    }

    // Reproducir la música
    music.play();
    // --------------------------- MUSICA -------------------------------

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
        // Actualizar animacion
        dragon.Update();

        window.clear();
        dragon.Draw(window);
        window.display();
        if (music.getStatus() != sf::Music::Playing)
        {
            window.close();
        }
    }

    return 0;
}